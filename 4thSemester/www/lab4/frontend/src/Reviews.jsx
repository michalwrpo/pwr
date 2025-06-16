import './Reviews.css';
import { useQuery, useMutation, useQueryClient } from '@tanstack/react-query';
import { useState } from 'react';

function Reviews({ productId }) {
    const queryClient = useQueryClient();
    const [rating, setRating] = useState('');
    const [submitError, setSubmitError] = useState(null);

    const {
        data: products,
        isLoading: productsLoading,
        isError: productsError,
    } = useQuery({
        queryKey: ['products'],
        queryFn: async () => {
            const res = await fetch('/api/products/');
            if (!res.ok) throw new Error('Network response was not ok');
            return res.json();
        },
    });

    const {
        data: reviews,
        isLoading: reviewsLoading,
        isError: reviewsError,
    } = useQuery({
        queryKey: ['reviews', productId],
        queryFn: async () => {
            const res = await fetch(`/api/products/${productId}/reviews`);
            if (!res.ok) throw new Error('Network response was not ok');
            return res.json();
        },
        enabled: !!productId,
    });

    const mutation = useMutation({
        mutationFn: async (newReview) => {
            // Get access_token from cookies
            const match = document.cookie.match(/(?:^|;\s*)access_token=([^;]*)/);
            const accessToken = match ? decodeURIComponent(match[1]) : null;

            let res = await fetch(`/api/products/${productId}/reviews`, {
                method: 'POST',
                headers: { 
                    'Content-Type': 'application/json',
                    ...(accessToken ? { 'Authorization': `Bearer ${accessToken}` } : {})
                },
                body: JSON.stringify(newReview),
            });

            if (res.status === 400) {
                // Try PATCH if POST returns 400
                res = await fetch(`/api/products/${productId}/reviews`, {
                    method: 'PUT',
                    headers: { 
                        'Content-Type': 'application/json',
                        ...(accessToken ? { 'Authorization': `Bearer ${accessToken}` } : {})
                    },
                    body: JSON.stringify(newReview),
                });
            }

            if (!res.ok) {
                const err = await res.text();
                throw new Error(err || 'Failed to add review');
            }
            return res.json();
        },
        onSuccess: () => {
            queryClient.invalidateQueries(['reviews', productId]);
            setRating('');
            setSubmitError(null);
        },
        onError: (error) => {
            try {
                const parsed = JSON.parse(error.message);
                setSubmitError(parsed.message || error.message);
            } catch {
                setSubmitError(error.message);
            }
        },
    });

    const productsList = Array.isArray(products) ? products : (products && Array.isArray(products.products) ? products.products : []);
    const product = productsList?.find(p => String(p.id) === String(productId));

    const productLoading = productsLoading;
    const productError = productsError;

    if (reviewsLoading || productLoading) return <div>Loading reviews...</div>;
    if (reviewsError || productError) return <div>Error loading reviews. {reviewsError}</div>;

    const reviewsList = Array.isArray(reviews) ? reviews : (reviews && Array.isArray(reviews.reviews) ? reviews.reviews : []);

    const usernameMatch = document.cookie.match(/(?:^|;\s*)username=([^;]*)/);
    const username = usernameMatch ? decodeURIComponent(usernameMatch[1]) : null;

    const handleSubmit = (e) => {
        e.preventDefault();
        const num = Number(rating);
        if (!Number.isInteger(num) || num < 1 || num > 10) {
            setSubmitError('Rating must be an integer between 1 and 10.');
            return;
        }
        mutation.mutate({ rating: num });
    };

    const handleRemoveReview = async () => {
        const match = document.cookie.match(/(?:^|;\s*)access_token=([^;]*)/);
        const accessToken = match ? decodeURIComponent(match[1]) : null;
        try {
            const res = await fetch(`/api/products/${productId}/reviews`, {
                method: 'DELETE',
                headers: {
                    'Content-Type': 'application/json',
                    ...(accessToken ? { 'Authorization': `Bearer ${accessToken}` } : {})
                },
                body: JSON.stringify({ username }),
            });
            if (!res.ok) {
                const err = await res.text();
                throw new Error(err || 'Failed to remove review');
            }
            queryClient.invalidateQueries(['reviews', productId]);
        } catch (err) {
            setSubmitError(err.message);
        }
    };

    return (
        <div className="reviews-container">
            <h2 className="reviews-title">Reviews for {product?.name || 'Product'}</h2>
            <form className="add-review-form" onSubmit={handleSubmit}>
                <label>
                    Add your rating (1-10):{' '}
                    <input
                        type="number"
                        min="1"
                        max="10"
                        value={rating}
                        onChange={e => setRating(e.target.value)}
                        required
                    />
                </label>
                <button type="submit" disabled={mutation.isLoading}>Submit</button>
            </form>
            {submitError && <div className="review-error">{submitError}</div>}
            {reviews && reviewsList.length > 0 ? (
                <div className="reviews-list">
                    {reviewsList.map((review, idx) => (
                        <div key={idx} className="review-item">
                            <div className="review-content">
                                <span className="review-username"><strong>{review.username}</strong></span>
                                <span className="review-rating">{review.rating}/10</span>
                            </div>
                            {username && review.username === username && (
                                <button
                                    className="remove-review-btn"
                                    onClick={handleRemoveReview}
                                    style={{ marginLeft: 8 }}
                                >
                                    X
                                </button>
                            )}
                        </div>
                    ))}
                </div>
            ) : (
                <p className="no-reviews">No reviews yet.</p>
            )}
        </div>
    );
}

export default Reviews;