import sys
import random

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} [probability] [input file] [output file]", file=sys.stderr)
        sys.exit(1)

    p = float(sys.argv[1])

    outfile = open(sys.argv[3], "wb")

    with open(sys.argv[2], "rb") as f:
        while (byte := f.read(1)):
            out_byte = ord(byte)
            for i in range(8):
                if (random.random() < p):
                    out_byte ^= 1 << i
            outfile.write(out_byte.to_bytes())

    outfile.close()
