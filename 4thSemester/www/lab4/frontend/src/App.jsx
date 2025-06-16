import './App.css'
import Login from './Login'
import Register from './Register'
import Products from './Products'
import Home from './Home'
import Reviews from './Reviews'
import User from './User'
import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import { BrowserRouter as Router, Routes, Route, Link, useNavigate, useParams, useLocation } from 'react-router-dom'
import { useState } from 'react'

const queryClient = new QueryClient()

const NAV_ITEMS = [
    { name: 'Home', path: '/' },
    { name: 'Login', path: '/login' },
    { name: 'Register', path: '/register' },
    { name: 'Products', path: '/products' },
]

// Wrapper for Reviews to get productId from URL
function ReviewsWrapper(props) {
    const { productId } = useParams()
    return <Reviews {...props} productId={productId} />
}

function Navbar() {
    const [menuOpen, setMenuOpen] = useState(false)
    const location = useLocation()
    const getUsernameFromCookie = () => {
        const match = document.cookie.match(/(?:^|;\s*)username=([^;]*)/)
        return match ? decodeURIComponent(match[1]) : null
    }
    const username = getUsernameFromCookie()
    const navigate = useNavigate()

    const handleMenuToggle = () => setMenuOpen(open => !open)
    const handleNavClick = (path) => {
        setMenuOpen(false)
        navigate(path)
    }

    return (
        <nav className='navbar'>
            <div className='navbar-mobile'>
                <button
                    className='hamburger'
                    onClick={handleMenuToggle}
                    aria-label="Toggle navigation"
                >
                    <span className="bar"></span>
                    <span className="bar"></span>
                    <span className="bar"></span>
                </button>
                {username && (
                    <div
                        className='navbar-username-div'
                        onClick={() => { setMenuOpen(false); navigate('/user') }}
                    >
                        <span className="navbar-username">
                            {username}
                        </span>
                    </div>
                )}
            </div>
            <div className={`navbar-center ${menuOpen ? 'open' : ''}`}>
                {NAV_ITEMS.map(item => (
                    <Link
                        key={item.name}
                        to={item.path}
                        className={location.pathname === item.path ? 'nav-btn-active' : 'nav-btn'}
                        onClick={() => handleNavClick(item.path)}
                    >
                        {item.name}
                    </Link>
                ))}
            </div>
        </nav>
    )
}

function App() {
    return (
        <QueryClientProvider client={queryClient}>
            <Router>
                <Navbar />
                <main>
                    <Routes>
                        <Route path="/" element={<Home />} />
                        <Route path="/login" element={<Login />} />
                        <Route path="/register" element={<Register />} />
                        <Route path="/products" element={<Products />} />
                        <Route path="/products/:productId/reviews" element={<ReviewsWrapper />} />
                        <Route path="/user" element={<User />} />
                        {/* fallback route */}
                        <Route path="*" element={<Home />} />
                    </Routes>
                </main>
            </Router>
        </QueryClientProvider>
    )
}

export default App
