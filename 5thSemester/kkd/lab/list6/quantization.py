import numpy as np

def Lloyd_Max_quantization(data: np.ndarray, num_codewords: int, max_iterations=30, epsilon=0.01):
    flat_data = data.flatten()
    
    sorted_data = np.sort(flat_data)
    init_indices = np.linspace(0, len(flat_data) - 1, num_codewords, dtype=int)
    codewords = sorted_data[init_indices].astype(np.float64)

    for _ in range(max_iterations):
        distances = np.abs(flat_data[:, np.newaxis] - codewords[np.newaxis, :])
        assignments = np.argmin(distances, axis=1)

        sums = np.bincount(assignments, weights=flat_data, minlength=num_codewords)
        counts = np.bincount(assignments, minlength=num_codewords)

        new_codewords = np.zeros_like(codewords)
        mask = counts > 0
        new_codewords[mask] = sums[mask] / counts[mask]
        
        new_codewords[~mask] = codewords[~mask]

        diff = np.linalg.norm(new_codewords - codewords)
        if diff < epsilon:
            break
        codewords = new_codewords

    return np.sort(codewords) 

def decode(lp_data: np.ndarray, hp_data: np.ndarray) -> np.ndarray:
    decoded_data = lp_data.astype(np.int16) + (hp_data.astype(np.int16) - 128) * 2
    decoded_data = np.clip(decoded_data, 0, 255).astype(np.uint8)
    return decoded_data