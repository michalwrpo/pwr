from PIL import Image
import numpy as np
import os

def get_tga_pixel_values(image_path):
    if not os.path.exists(image_path):
        print(f"Error: File not found at {image_path}")
        return None, None
    try:
        img = Image.open(image_path)

        if img.mode != 'RGB':
            img = img.convert('RGB')
            
        numpy_array = np.array(img)
        original_shape = numpy_array.shape
        data_vectors = numpy_array.reshape(-1, original_shape[-1]).astype(np.float64)
        return data_vectors, original_shape
    except Exception as e:
        print(f"Error processing image: {e}")
        return None, None

def save_image(image_array, output_path):
    try:
        img_data = np.clip(image_array, 0, 255).astype(np.uint8)
        img = Image.fromarray(img_data.astype(np.uint8))
        img.save(output_path, format='TGA')
        print(f"Image saved successfully at {output_path}")
    except Exception as e:
        print(f"Failed to save image: {e}")

def apply_quantization(data, codebook):
    flat_data = data.flatten()
    
    distances = np.abs(flat_data[:, np.newaxis] - codebook[np.newaxis, :])
    nearest_indices = np.argmin(distances, axis=1)
    
    quantized_flat = codebook[nearest_indices]
    
    return quantized_flat.reshape(data.shape)

def quantize_and_save_image(r, g, b, r_cb, g_cb, b_cb, original_shape, output_path, shift_hp=False):
    q_r = apply_quantization(r, r_cb)
    q_g = apply_quantization(g, g_cb)
    q_b = apply_quantization(b, b_cb)

    quantized_img = np.stack([q_r, q_g, q_b], axis=2)

    if shift_hp:
        quantized_img = (quantized_img / 2) + 128

    save_image(quantized_img, output_path)

