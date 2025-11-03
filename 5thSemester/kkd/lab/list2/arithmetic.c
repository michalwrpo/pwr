#include <stdio.h>

#include "arithmetic.h"

#define EOF_SYMBOL 256
#define SYMBOL_COUNT 257

void encode(char* input_filename, char* output_filename) {
    unsigned int max = 0x3fff;
    unsigned int counts[258] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257};

    FILE *in_file = fopen(input_filename, "r");
    if (in_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", input_filename);
        return;
    }

    FILE *out_file = fopen(output_filename, "w");
    if (out_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", output_filename);
        return;
    }

    unsigned int lower_bound = 0;
    unsigned int upper_bound = 0xffff;
    unsigned int current_range;
    unsigned int underflows = 0;
    unsigned int ld1, ud1;

    int c;
    unsigned char byte = 0, len = 0;


    while ((c = fgetc(in_file)) != EOF) {        
        current_range = upper_bound - lower_bound + 1;
        upper_bound = lower_bound + ((current_range * counts[c + 1]) / counts[SYMBOL_COUNT]) - 1;
        lower_bound = lower_bound + ((current_range * counts[c]) / counts[SYMBOL_COUNT]);

        // printf("%u - %u\n", lower_bound, upper_bound);

        while (((~lower_bound) ^ upper_bound) & 0x8000 || ((lower_bound >> 14 == 1) && (upper_bound >> 14 == 2)) ) {
            ld1 = lower_bound >> 15;
            ud1 = upper_bound >> 15;

            if (ld1 == ud1) {
                byte = (byte << 1) + ld1;
                len++;

                if (len == 8) {
                    fprintf(out_file, "%c", byte);
                    len = 0;
                    byte = 0;
                }

                while (underflows) {
                    underflows--;
                    byte = (byte << 1) + (1 - ld1);
                    len++;
                    if (len == 8) {
                        fprintf(out_file, "%c", byte);
                        len = 0;
                        byte = 0;
                    }
                }                

                upper_bound = ((upper_bound << 1) & 0xffff) + 1;
                lower_bound = (lower_bound << 1) & 0xffff;
            } else {
                underflows++;

                upper_bound = (((upper_bound << 2) & 0xffff) >> 1) + (ud1 << 15) + 1;
                lower_bound = (((lower_bound << 2) & 0xffff) >> 1) + (ld1 << 15);
            }
        }
        

        for (int i = c + 1; i < 258; i++) {
            counts[i]++;
        }

        if (counts[SYMBOL_COUNT] > max) {
            for (int i = 1; i < 258; i++) {
                counts[i] /= 2;
            }

            for (int i = 1; i < 258; i++) {
                if (counts[i] <= counts[i - 1]) {
                    counts[i] = counts[i - 1] + 1;
                }
            }
        }
        
    }

    // encode an EOF
    current_range = upper_bound - lower_bound + 1;
    upper_bound = lower_bound + ((current_range * counts[EOF_SYMBOL + 1]) / counts[SYMBOL_COUNT]) - 1;
    lower_bound = lower_bound + ((current_range * counts[EOF_SYMBOL]) / counts[SYMBOL_COUNT]);

    while (((~lower_bound) ^ upper_bound) & 0x8000 || ((lower_bound >> 14 == 1) && (upper_bound >> 14 == 2)) ) {
        ld1 = lower_bound >> 15;
        ud1 = upper_bound >> 15;

        if (ld1 == ud1) {
            byte = (byte << 1) + ld1;
            len++;

            if (len == 8) {
                fprintf(out_file, "%c", byte);
                len = 0;
                byte = 0;
            }

            while (underflows) {
                underflows--;
                byte = (byte << 1) + (1 - ld1);
                len++;
                if (len == 8) {
                    fprintf(out_file, "%c", byte);
                    len = 0;
                    byte = 0;
                }
            }                

            upper_bound = ((upper_bound << 1) & 0xffff) + 1;
            lower_bound = (lower_bound << 1) & 0xffff;
        } else {
            underflows++;

            upper_bound = (((upper_bound << 2) & 0xffff) >> 1) + (ud1 << 15) + 1;
            lower_bound = (((lower_bound << 2) & 0xffff) >> 1) + (ld1 << 15);
        }
    }

    int ld2 = (lower_bound >> 14) & 1;
    byte = (byte << 1) + ld2;
    len++;
    underflows++;

    if (len == 8) {
        fprintf(out_file, "%c", byte);
        len = 0;
        byte = 0;
    }

    while (underflows) {
        underflows--;
        byte = (byte << 1) + (1 - ld2);
        len++;
        if (len == 8) {
            fprintf(out_file, "%c", byte);
            len = 0;
            byte = 0;
        }
    }

    if (len) {
        byte <<= 8 - len;
        fprintf(out_file, "%c", byte);
    }
    

    fclose(in_file);
    fclose(out_file);
}

void decode(char* input_filename, char* output_filename) {
    unsigned int max = 0x3fff;
    unsigned int counts[258] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257};

    FILE *in_file = fopen(input_filename, "r");
    if (in_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", input_filename);
        return;
    }

    FILE *out_file = fopen(output_filename, "w");
    if (out_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", output_filename);
        return;
    }

    unsigned char byte;
    unsigned int encoded_value, decoded_value;
    unsigned int lower_bound = 0;
    unsigned int upper_bound = 0xffff;
    unsigned int current_range;
    unsigned int ld1, ud1, remaining_bits = 8;
    int ch;

    int c = getc(in_file);
    if (c == EOF) {
        fprintf(stderr, "Error: input file too short for initial 16-bit value.");
        return;
    }

    encoded_value = c << 8;
    c = getc(in_file);
    if (c == EOF) {
        fprintf(stderr, "Error: input file too short for initial 16-bit value.");
        return;
    }
    
    encoded_value += c;
    
    c = getc(in_file);
    byte = (c != EOF) ? (unsigned char)c : 0; 

    while (1) {
        current_range = upper_bound - lower_bound + 1;
        decoded_value = ((encoded_value - lower_bound + 1) * counts[SYMBOL_COUNT] - 1) / current_range;

        for (ch = 0; ch < 257 && counts[ch + 1] <= decoded_value; ch++);
    
        if (ch == EOF_SYMBOL)
            break;

        fputc(ch, out_file);        

        upper_bound = lower_bound + ((current_range * counts[ch + 1]) / counts[SYMBOL_COUNT]) - 1;
        lower_bound = lower_bound + ((current_range * counts[ch]) / counts[SYMBOL_COUNT]);

        while (((~lower_bound) ^ upper_bound) & 0x8000 || ((lower_bound >> 14 == 1) && (upper_bound >> 14 == 2)) ) {
            ld1 = lower_bound >> 15;
            ud1 = upper_bound >> 15;

            if (ld1 == ud1) {
                encoded_value = ((encoded_value << 1) & 0xffff) | (byte >> 7);
                byte <<= 1;
                remaining_bits--;

                if (!remaining_bits) {
                    c = getc(in_file);
                    byte = (c != EOF) ? (unsigned char)c : 0; 
                    remaining_bits = 8;
                }

                upper_bound = ((upper_bound << 1) & 0xffff) + 1;
                lower_bound = (lower_bound << 1) & 0xffff;
            } else {
                encoded_value = (((encoded_value << 2) & 0xffff) >> 1) | (encoded_value & 0x8000) | (byte >> 7);
                byte <<= 1;
                remaining_bits--;

                if (!remaining_bits) {
                    c = getc(in_file);
                    byte = (c != EOF) ? (unsigned char)c : 0; 
                    remaining_bits = 8;
                }

                upper_bound = (((upper_bound << 2) & 0xffff) >> 1) + (ud1 << 15) + 1;
                lower_bound = (((lower_bound << 2) & 0xffff) >> 1) + (ld1 << 15);
            }
            
        }

        for (int i = ch + 1; i < 258; i++) {
            counts[i]++;
        }

        if (counts[SYMBOL_COUNT] > max) {
            for (int i = 1; i < 258; i++) {
                counts[i] /= 2;
            }

            for (int i = 1; i < 258; i++) {
                if (counts[i] <= counts[i - 1]) {
                    counts[i] = counts[i - 1] + 1;
                }
            }
        }
    }
    

    fclose(in_file);
    fclose(out_file);
}