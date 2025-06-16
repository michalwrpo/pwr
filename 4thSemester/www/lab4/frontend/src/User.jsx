import './User.css';
import { useQuery } from '@tanstack/react-query';
import { useState } from 'react';

async function fetchUser() {
    const accessToken = document.cookie
        .split('; ')
        .find(row => row.startsWith('access_token='))
        ?.split('=')[1];

    const res = await fetch('/api/users/me', {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            ...(accessToken && { 'Authorization': `Bearer ${accessToken}` }),
        },
        credentials: 'include',
    });
    if (!res.ok) {
        throw new Error('Failed to fetch user data');
    }
    return res.json();
}

async function fetchAllUsers() {
    const accessToken = document.cookie
        .split('; ')
        .find(row => row.startsWith('access_token='))
        ?.split('=')[1];

    const res = await fetch('/api/users/', {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            ...(accessToken && { 'Authorization': `Bearer ${accessToken}` }),
        },
        credentials: 'include',
    });
    if (!res.ok) {
        throw new Error('Failed to fetch users list');
    }
    return res.json();
}

function User() {
    const { data: user, error, isLoading } = useQuery({
        queryKey: ['user'],
        queryFn: fetchUser,
    });

    const [showCreateForm, setShowCreateForm] = useState(false);
    const [newUsername, setNewUsername] = useState('');
    const [newPassword, setNewPassword] = useState('');
    const [createError, setCreateError] = useState('');
    const [creating, setCreating] = useState(false);

    const {
        data: users,
        error: usersError,
        isLoading: usersLoading,
    } = useQuery({
        queryKey: ['allUsers'],
        queryFn: fetchAllUsers,
        enabled: !!user && user.type === 'admin',
    });

    const usersList = Array.isArray(users) ? users : users?.users;

    if (isLoading) {
        return <div className="user-loading">Loading...</div>;
    }

    if (error) {
        return <div className="user-error">Error: {error.message}</div>;
    }

    const handleRemoveUser = async (userId) => {
        if (!window.confirm('Are you sure you want to remove this user?')) return;
        const accessToken = document.cookie
            .split('; ')
            .find(row => row.startsWith('access_token='))
            ?.split('=')[1];

        const res = await fetch(`/api/users/${userId}`, {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json',
                ...(accessToken && { 'Authorization': `Bearer ${accessToken}` }),
            },
            credentials: 'include',
        });

        if (!res.ok) {
            alert('Failed to remove user');
        } else {
            // Optionally refetch users
            window.location.reload();
        }
    };

    const handleCreateUser = async (e) => {
        e.preventDefault();
        setCreateError('');
        setCreating(true);
        const accessToken = document.cookie
            .split('; ')
            .find(row => row.startsWith('access_token='))
            ?.split('=')[1];

        const res = await fetch('/api/users/', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                ...(accessToken && { 'Authorization': `Bearer ${accessToken}` }),
            },
            credentials: 'include',
            body: JSON.stringify({
                username: newUsername,
                password: newPassword,
            }),
        });

        setCreating(false);

        if (!res.ok) {
            const err = await res.json().catch(() => ({}));
            setCreateError(err.message || 'Failed to create user');
        } else {
            setShowCreateForm(false);
            setNewUsername('');
            setNewPassword('');
            window.location.reload();
        }
    };

    return (
        <div className="user-container">
            <h2 className="user-title">User Info</h2>
            <p className="user-info"><strong>ID:</strong> {user.id}</p>
            <p className="user-info"><strong>Username:</strong> {user.username}</p>
            <p className="user-info"><strong>User Type:</strong> {user.type}</p>

            {user.type === 'admin' && (
                <div className="admin-users-section">
                    <h3 className="admin-users-title">All Users</h3>
                    <button
                        className="create-user-btn"
                        onClick={() => setShowCreateForm(v => !v)}
                        style={{ marginBottom: '1em' }}
                    >
                        {showCreateForm ? 'Cancel' : 'Create User'}
                    </button>
                    {showCreateForm && (
                        <form className="create-user-form" onSubmit={handleCreateUser} style={{ marginBottom: '1em' }}>
                            <input
                                type="text"
                                placeholder="Username"
                                value={newUsername}
                                onChange={e => setNewUsername(e.target.value)}
                                required
                                disabled={creating}
                            />
                            <input
                                type="password"
                                placeholder="Password"
                                value={newPassword}
                                onChange={e => setNewPassword(e.target.value)}
                                required
                                disabled={creating}
                            />
                            <button type="submit" disabled={creating}>
                                {creating ? 'Creating...' : 'Create'}
                            </button>
                            {createError && <div className="create-user-error">{createError}</div>}
                        </form>
                    )}
                    {usersLoading && <div className="admin-users-loading">Loading users...</div>}
                    {usersError && <div className="admin-users-error">Error: {usersError.message}</div>}
                    {usersList && (
                        <div className="admin-users-list">
                            {usersList.map(u => (
                                <div key={u.id} className="admin-user-item">
                                    <span className="admin-user-id">{u.id}</span> - <span className="admin-user-username">{u.username}</span> (<span className="admin-user-type">{u.type}</span>)
                                    {u.id !== user.id && (
                                        <button
                                            className="remove-user-btn"
                                            onClick={() => handleRemoveUser(u.id)}
                                            style={{ marginLeft: '1em' }}
                                        >
                                            X
                                        </button>
                                    )}
                                </div>
                            ))}
                        </div>
                    )}
                </div>
            )}
        </div>
    );
}

export default User;
