import { useState } from 'react';
import { useMutation } from '@tanstack/react-query';
import './Login.css';

const login = async ({ username, password }) => {
    const response = await fetch('/api/login', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ username, password }),
    });
    if (!response.ok) {
        throw new Error('Login failed');
    }
    return response.json();
};

// Helper to set cookie
function setCookie(name, value, hours = 1) {
    const expires = new Date(Date.now() + hours * 60 * 60 * 1000).toUTCString();
    document.cookie = `${name}=${encodeURIComponent(value)}; expires=${expires}; path=/`;
}

function Login({ onLogin }) {
    const [username, setUsername] = useState(() => {
        // Try to read username from cookie
        const match = document.cookie.match(/(?:^|; )username=([^;]*)/);
        return match ? decodeURIComponent(match[1]) : '';
    });
    const [password, setPassword] = useState('');
    const [successMessage, setSuccessMessage] = useState('');

    const mutation = useMutation({
        mutationFn: login,
        onSuccess: (data) => {
            setSuccessMessage('Login successful!');
            setCookie('username', username); // Store username in cookie
            if (onLogin) onLogin(data);
        },
        onError: () => {
            setSuccessMessage('Login failed');
        },
    });

    const handleSubmit = (e) => {
        e.preventDefault();
        setSuccessMessage('');
        mutation.mutate({ username, password });
    };

    return (
        <div className="login-container">
            <h2 className="login-title">Login</h2>
            <form className="login-form" onSubmit={handleSubmit}>
                <div className="login-field">
                    <label className="login-label">Username:</label>
                    <input
                        className="login-input"
                        type="text"
                        value={username}
                        onChange={e => setUsername(e.target.value)}
                        required
                    />
                </div>
                <div className="login-field">
                    <label className="login-label">Password:</label>
                    <input
                        className="login-input"
                        type="password"
                        value={password}
                        onChange={e => setPassword(e.target.value)}
                        required
                    />
                </div>
                <button
                    className="login-button"
                    type="submit"
                    disabled={mutation.isLoading}
                >
                    {mutation.isLoading ? 'Logging in...' : 'Login'}
                </button>
                {successMessage && (
                    <div
                        className={`login-message ${
                            successMessage === 'Login failed' ? 'login-error' : 'login-success'
                        }`}
                    >
                        {successMessage}
                    </div>
                )}
            </form>
        </div>
    );
}

export default Login;