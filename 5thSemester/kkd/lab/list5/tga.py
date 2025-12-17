from PIL import Image
import numpy as np
import os
from scipy.spatial import KDTree

def get_tga_pixel_values(image_path):
    if not os.path.exists(image_path):
        print(f"Error: File not found at {image_path}")
        return None, None

    try:
        img = Image.open(image_path)
        print(f"Image successfully opened. Format: {img.format}, Mode: {img.mode}, Size: {img.size}")

        numpy_array = np.array(img)
        
        original_shape = numpy_array.shape
        
        # Flatten the array into a list of vectors (N_pixels x Channels)
        data_vectors = numpy_array.reshape(-1, original_shape[-1]).astype(np.float64)

        return data_vectors, original_shape

    except Exception as e:
        print(f"An error occurred while processing the image: {e}")
        return None, None

def quantize_and_save_image(data_vectors, codebook, original_shape, output_path):
    tree = KDTree(codebook)
    _, assignment = tree.query(data_vectors)

    quantized_data = codebook[assignment]
    
    quantized_image_array = quantized_data.reshape(original_shape)
    
    quantized_image_array = quantized_image_array.astype(np.uint8)
    
    try:
        quantized_img = Image.fromarray(quantized_image_array)
        quantized_img.save(output_path, format='TGA')
        print(f"Successfully saved quantized image to: {output_path}")
        print(f"Quantized Image Size: {quantized_img.size}, Mode: {quantized_img.mode}")
    except Exception as e:
        print(f"Error saving image: {e}")

    return quantized_data