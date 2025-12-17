import sys
import time

from tga import get_tga_pixel_values, quantize_and_save_image
from lbg import lbg_quantization
from mse_snr import calculate_mse_and_snr

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python main.py <image_path> <output_path> <bit_count>")
        sys.exit(1)

    image_path = sys.argv[1]
    output_path = sys.argv[2]
    bit_count = int(sys.argv[3])
    num_codewords = 2 ** bit_count

    data_vectors, original_shape = get_tga_pixel_values(image_path)
    if data_vectors is None:
        print("Failed to load image data.")
        sys.exit(1)

    start = time.time()

    codebook = lbg_quantization(data_vectors, num_codewords)

    end = time.time()

    print(f"LBG Quantization Time: {end - start:.2f} seconds\n")

    quantized_data_vectors = quantize_and_save_image(data_vectors, codebook, original_shape, output_path)

    if quantized_data_vectors is not None:
        mse, snr = calculate_mse_and_snr(data_vectors, quantized_data_vectors)

        print("\n--- Quantization Metrics ---")
        print(f"Mean Squared Error (MSE): {mse:.4f}")
        print(f"Signal-to-Noise Ratio (SNR): {snr:.2f} dB")
