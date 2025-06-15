import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'
import { useEffect } from 'react'

function useProducts() {
  const [products, setProducts] = useState([])
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState(null)

  useEffect(() => {
    setLoading(true)
    fetch('/api/products/')
      .then(res => {
        if (!res.ok) throw new Error('Network response was not ok ' + res.statusText)
        return res.json()
      })
      .then(data => setProducts(data))
      .catch(err => setError(err.message))
      .finally(() => setLoading(false))
  }, [])

  return { products, loading, error }
}

function ProductsList() {
  const { products, loading, error } = useProducts()

  if (loading) return <div>Loading...</div>
  if (error) return <div>Error: {error}</div>
  if (!products.length) return <div>No products found.</div>

  console.log('Products:', products)
  return "Cool"
  // return (
  //   <ul>
  //     {products.map((product, idx) => (
  //       <li key={product.id || idx}>{JSON.stringify(product)}</li>
  //     ))}
  //   </ul>
  // )
}

function App() {
  const [showProducts, setShowProducts] = useState(false);

  return (
    <>
      <div>
        <a href="https://vite.dev" target="_blank">
          <img src={viteLogo} className="logo" alt="Vite logo" />
        </a>
        <a href="https://react.dev" target="_blank">
          <img src={reactLogo} className="logo react" alt="React logo" />
        </a>
      </div>
      <h1>Vite + React</h1>
      <div className="card">
        <button onClick={() => setShowProducts(true)}>
          {showProducts ? 'Products loaded' : 'Show Products'}
        </button>
        {showProducts && <ProductsList />}
        <p>
          Edit <code>src/App.jsx</code> and save to test HMR
        </p>
      </div>
      <p className="read-the-docs">
        Click on the Vite and React logos to learn more
      </p>
    </>
  )
}


export default App
