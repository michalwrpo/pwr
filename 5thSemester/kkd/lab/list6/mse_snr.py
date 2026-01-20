import numpy as np
import sys
from tga import get_tga_pixel_values

def calculate_mse_and_snr(original_data, quantized_data):
    original_data = original_data.astype(np.float64)
    quantized_data = quantized_data.astype(np.float64)
    
    error_signal = original_data - quantized_data
    
    N_total = original_data.size 
    
    mse = np.sum(error_signal**2) / N_total
    
    signal_power = np.sum(original_data**2)
    
    noise_power = np.sum(error_signal**2)
    
    if noise_power == 0:
        snr = np.inf
    else:
        snr = 10 * np.log10(signal_power / noise_power)
        
    return mse, snr

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python mse_snr.py <original_image_path> <quantized_image_path>")
        sys.exit(1)

    original_image_path = sys.argv[1]
    quantized_image_path = sys.argv[2]

    original_data, _ = get_tga_pixel_values(original_image_path)
    quantized_data, _ = get_tga_pixel_values(quantized_image_path)

    if original_data is None or quantized_data is None:
        sys.exit(1)

    mse, snr = calculate_mse_and_snr(original_data, quantized_data)

    print(f"MSE: {mse:.4f}")
    print(f"SNR: {snr:.2f} dB")