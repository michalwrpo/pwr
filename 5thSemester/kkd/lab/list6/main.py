import sys
import time
from tga import get_tga_pixel_values, quantize_and_save_image, save_image
from quantization import Lloyd_Max_quantization, decode
from filters import lowpass, highpass

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python main.py <image_path> <output_path> <bit_count>")
        sys.exit(1)

    if sys.argv[1] == "-d" and len(sys.argv) != 5:
        print("Usage mode: python main.py -d <lp_image> <hp_image> <output_path>")
        sys.exit(1)

    should_decode = False
    if sys.argv[1] == "-d":
        should_decode = True

    if not should_decode:
        image_path = sys.argv[1]
        output_path = sys.argv[2]
        bit_count = int(sys.argv[3])
        num_codewords = 2 ** bit_count

        data_vectors, original_shape = get_tga_pixel_values(image_path)
        if data_vectors is None or original_shape is None: sys.exit(1)

        print(f"Processing... (Target colors: {num_codewords})")
        start = time.time()

        red = data_vectors[:, 0].reshape(original_shape[0], original_shape[1])
        green = data_vectors[:, 1].reshape(original_shape[0], original_shape[1])
        blue = data_vectors[:, 2].reshape(original_shape[0], original_shape[1]) 

        LP_red = lowpass(red, kernel_size=3)
        LP_green = lowpass(green, kernel_size=3)
        LP_blue = lowpass(blue, kernel_size=3)

        HP_red = highpass(red, LP_red)
        HP_green = highpass(green, LP_green)
        HP_blue = highpass(blue, LP_blue)

        LP_r_cb = Lloyd_Max_quantization(LP_red, num_codewords)
        LP_g_cb = Lloyd_Max_quantization(LP_green, num_codewords)
        LP_b_cb = Lloyd_Max_quantization(LP_blue, num_codewords)

        HP_r_cb = Lloyd_Max_quantization(HP_red, num_codewords)
        HP_g_cb = Lloyd_Max_quantization(HP_green, num_codewords)
        HP_b_cb = Lloyd_Max_quantization(HP_blue, num_codewords)

        end = time.time()
        print(f"Processing Time: {end - start:.2f} seconds")

        quantize_and_save_image(LP_red, LP_green, LP_blue, 
                            LP_r_cb, LP_g_cb, LP_b_cb, 
                            original_shape, output_path + "/out_lp.tga", shift_hp=False)
                            
        quantize_and_save_image(HP_red, HP_green, HP_blue, 
                            HP_r_cb, HP_g_cb, HP_b_cb, 
                            original_shape, output_path + "/out_hp.tga", shift_hp=True)
    else:
        lp_image_path = sys.argv[2]
        hp_image_path = sys.argv[3]
        output_path = sys.argv[4]

        lp_data_vectors, lp_original_shape = get_tga_pixel_values(lp_image_path)
        hp_data_vectors, hp_original_shape = get_tga_pixel_values(hp_image_path)
        if lp_data_vectors is None or lp_original_shape is None: sys.exit(1)
        if hp_data_vectors is None or hp_original_shape is None: sys.exit(1)

        start = time.time()

        decoded_image = decode(lp_data_vectors.reshape(lp_original_shape[0], lp_original_shape[1], 3),
            hp_data_vectors.reshape(hp_original_shape[0], hp_original_shape[1], 3))

        save_image(decoded_image, output_path + "/decoded.tga")

        end = time.time()
        print(f"Decoding Time: {end - start:.2f} seconds")
