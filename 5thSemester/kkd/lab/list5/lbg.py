import numpy as np
from scipy.spatial import KDTree

def approx_to_8bit(colors):
    return np.clip(np.round(colors), 0, 255).astype(np.uint8)

def lbg_quantization(data, num_codewords, max_iterations=10, epsilon=0.01):
    _, D = data.shape
    
    codebook = np.mean(data, axis=0).reshape(1, D)

    while codebook.shape[0] < num_codewords:
        new_codebook = []
        for c in codebook:
            c_plus = c * (1 + epsilon)
            c_minus = c * (1 - epsilon)
            new_codebook.append(c_plus)
            new_codebook.append(c_minus)
            
        codebook = np.array(new_codebook)
        
        K = codebook.shape[0]

        old_distortion = 2**30

        for _ in range(max_iterations):
            tree = KDTree(codebook)
            
            # Find the nearest neighbor (codeword) for every data vector
            # 'assignment' will be an array of indices [0, K-1]
            _, assignment = tree.query(data)
                        
            new_codebook = np.zeros_like(codebook)
            
            for k in range(K):
                # Select all data vectors assigned to the k-th cluster
                cluster_vectors = data[assignment == k]
                
                if len(cluster_vectors) > 0:
                    new_codebook[k] = np.mean(cluster_vectors, axis=0)
                else:
                    new_codebook[k] = codebook[k]

            distortion = np.mean((data - new_codebook[assignment]) ** 2)
            if abs(old_distortion - distortion) < epsilon:
                break

            old_distortion = distortion

            codebook = new_codebook
                        
    print(f"\nLBG finished. Final codebook size: {codebook.shape[0]}")

    codebook = approx_to_8bit(codebook)

    return codebook
