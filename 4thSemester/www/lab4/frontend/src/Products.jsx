import './Products.css';
import { useQuery } from '@tanstack/react-query'
import { useNavigate } from 'react-router-dom';
import { useState, useEffect } from 'react'; 

function useProducts() {
  const { data: products = [], isLoading: loading, error, refetch } = useQuery({
    queryKey: ['products'],
    queryFn: async () => {
      const res = await fetch('/api/products/')
      if (!res.ok) throw new Error('Network response was not ok ' + res.statusText)
      return res.json()
    }
  })

  return { products, loading, error, refetch }
}


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

async function handleDeleteProduct(e, product, refetch) {
    e.stopPropagation();
    if (window.confirm('Are you sure you want to delete this product?')) {
        try {
            const accessToken = document.cookie
                .split('; ')
                .find(row => row.startsWith('access_token='))
                ?.split('=')[1];
            const res = await fetch(`/api/products/${product.id}`, {
                method: 'DELETE',
                headers: {
                    'Content-Type': 'application/json',
                    ...(accessToken && { 'Authorization': `Bearer ${accessToken}` }),
                },
            });
            if (!res.ok) {
                const errorData = await res.json().catch(() => ({}));
                throw new Error(errorData.message || 'Failed to delete product');
            }
            await refetch();
        } catch (err) {
            alert(err.message);
        }
    }
}

function ProductModal({ formData, handleChange, handleSubmit, formError, editProduct, onCancel }) {
    return (
        <div className="modal-backdrop">
            <div className="modal">
                <h3>{editProduct ? 'Edit Product' : 'Create Product'}</h3>
                <form onSubmit={handleSubmit}>
                    <input
                        name="name"
                        placeholder="Name"
                        value={formData.name}
                        onChange={handleChange}
                        required
                    /><br />
                    <textarea
                        name="description"
                        placeholder="Description"
                        value={formData.description}
                        onChange={handleChange}
                        required
                    /><br />
                    <input
                        name="price"
                        type="number"
                        step="0.01"
                        placeholder="Price"
                        value={formData.price}
                        onChange={handleChange}
                        required
                    /><br />
                    {formError && <div className="form-error">{formError}</div>}
                    <button type="submit">{editProduct ? 'Save' : 'Create'}</button>
                    <button type="button" onClick={onCancel}>Cancel</button>
                </form>
            </div>
        </div>
    )
}

function Products() {
const { products, loading, error, refetch } = useProducts();
    const navigate = useNavigate();

    const [user, setUser] = useState(null);
    const [showModal, setShowModal] = useState(false);
    const [editProduct, setEditProduct] = useState(null);
    const [formData, setFormData] = useState({ name: '', description: '', price: '' });
    const [formError, setFormError] = useState('');

    // Fetch user info on mount
    useEffect(() => {
        fetchUser()
            .then(setUser)
            .catch(() => setUser(null));
    }, []);

    if (loading) return <div>Loading...</div>;
    if (error) return <div>Error: {error.message || error.toString()}</div>;

    // Handle both possible shapes: products or products.products
    const productsList = Array.isArray(products)
        ? products
        : (products && Array.isArray(products.products) ? products.products : []);

    if (!productsList.length) return <div>No products found.</div>;

    

    // Handle form changes
    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData((prev) => ({ ...prev, [name]: value }));
    };

    // Handle create/edit submit
    const handleSubmit = async (e) => {
        e.preventDefault();
        setFormError('');
        try {
            const method = editProduct ? 'PUT' : 'POST';
            const url = editProduct ? `/api/products/${editProduct.id}` : '/api/products/';
            const accessToken = document.cookie
                .split('; ')
                .find(row => row.startsWith('access_token='))
                ?.split('=')[1];

            const res = await fetch(url, {
                method,
                headers: {
                    'Content-Type': 'application/json',
                    ...(accessToken && { 'Authorization': `Bearer ${accessToken}` }),
                },
                body: JSON.stringify({
                    name: formData.name,
                    description: formData.description,
                    price: parseInt(formData.price),
                }),
            });
            if (!res.ok) {
                const errorData = await res.json().catch(() => ({}));
                throw new Error(errorData.message || 'Failed to save product');
            }
            await refetch() // re-fetch products list
            setShowModal(false);
            setEditProduct(null);
            setFormData({ name: '', description: '', price: '' });
            window.location.reload(); // quick refresh, or use react-query refetch
        } catch (err) {
            setFormError(err.message);
        }
    };

    // Open modal for create or edit
    const openModal = (product = null) => {
        setEditProduct(product);
        setFormData(product ? {
            name: product.name,
            description: product.description,
            price: Math.round(product.price * 100),
        } : { name: '', description: '', price: '' });
        setShowModal(true);
        setFormError('');
    };

    return (
        <div className="products-container">
            <h2 className="products-title">Products</h2>
            {user && user.type === 'admin' && (
                <div>
                    <button className="create-product-btn" onClick={() => openModal()}>Create Product</button>
                </div>
            )}
            {showModal && (
                <ProductModal
                    formData={formData}
                    handleChange={handleChange}
                    handleSubmit={handleSubmit}
                    formError={formError}
                    editProduct={editProduct}
                    onCancel={() => setShowModal(false)}
                />
            )}
            <div className="products-list">
                {productsList.map((product) => (
                    <div
                        key={product.id}
                        className="product-item"
                        style={{ cursor: 'pointer', position: 'relative' }}
                        onClick={() => navigate(`/products/${product.id}/reviews`)}
                    >
                        <strong className="product-name">{product.name}</strong><br />
                        <span className="product-description">
                            {product.description ? product.description : 'No description available.'}
                        </span><br />
                        <span className="product-price">Price: ${product.price}</span>
                        {user && user.type === 'admin' && (
                            <>
                                <button
                                    className="edit-product-btn"
                                    onClick={(e) => {
                                        e.stopPropagation();
                                        openModal(product);
                                    }}
                                >
                                    Edit
                                </button>
                                <button
                                    className="delete-product-btn"
                                    onClick={(e) => handleDeleteProduct(e, product, refetch)}
                                >
                                    Delete
                                </button>
                            </>
                        )}
                    </div>
                ))}
            </div>
        </div>
    );
}

export default Products;
