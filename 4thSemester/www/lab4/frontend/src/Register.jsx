import { useState } from 'react';
import { useMutation } from '@tanstack/react-query';
import './Login.css';

function Register() {
    const [form, setForm] = useState({
        username: '',
        password: '',
        confirmPassword: '',
    });
    const [error, setError] = useState('');
    const [success, setSuccess] = useState('');

    const handleChange = (e) => {
        setForm({ ...form, [e.target.name]: e.target.value });
        setError('');
        setSuccess('');
    };

    const registerMutation = useMutation({
        mutationFn: async ({ username, password }) => {
            const res = await fetch('/api/register', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ username, password }),
            });
            const data = await res.json();
            if (!res.ok) {
                throw new Error(data.message || 'Registration failed');
            }
            return data;
        },
        onSuccess: () => {
            setSuccess('Registration successful!');
            setForm({
                username: '',
                password: '',
                confirmPassword: '',
            });
        },
        onError: (err) => {
            setError(err.message);
        },
    });

    const handleSubmit = (e) => {
        e.preventDefault();
        if (form.password !== form.confirmPassword) {
            setError('Passwords do not match');
            return;
        }
        registerMutation.mutate({ username: form.username, password: form.password });
    };

    return (
        <div className="register-container">
            <h2 className="login-title">Register</h2>
            <form className="login-form" onSubmit={handleSubmit}>
                <div className="login-field">
                    <label className="login-label">Username:</label>
                    <input
                        className="login-input"
                        type="text"
                        name="username"
                        value={form.username}
                        onChange={handleChange}
                        required
                        autoComplete="username"
                    />
                </div>
                <div className="login-field">
                    <label className="login-label">Password:</label>
                    <input
                        className="login-input"
                        type="password"
                        name="password"
                        value={form.password}
                        onChange={handleChange}
                        required
                        autoComplete="new-password"
                    />
                </div>
                <div className="login-field">
                    <label className="login-label">Confirm Password:</label>
                    <input
                        className="login-input"
                        type="password"
                        name="confirmPassword"
                        value={form.confirmPassword}
                        onChange={handleChange}
                        required
                        autoComplete="new-password"
                    />
                </div>
                {error && <div className="login-error">{error}</div>}
                {success && <div className="login-success">{success}</div>}
                <button className="login-button" type="submit">Register</button>
            </form>
        </div>
    );
}

export default Register;
