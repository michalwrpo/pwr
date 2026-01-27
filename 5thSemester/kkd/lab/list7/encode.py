import sys

code_generator = [
    [1, 1, 1, 0, 0, 0, 0],
    [1, 0, 0, 1, 1, 0, 0],
    [0, 1, 0, 1, 0, 1, 0],
    [1, 1, 0, 1, 0, 0, 1]
]

def encode(byte):
    outbyte = 0

    for i in range(len(code_generator)):
        bit = (byte & (1 << (7 - i))) >> (7 - i)
        for j in range(len(code_generator[i])):
            if code_generator[i][j] == 1:
                outbyte ^= bit << (7 - j)
        
    for i in range(1, 8):
        outbyte ^= (outbyte & (1 << i)) >> i

    # print(f"{outbyte:08b}")
    return outbyte


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} [in_file] [out_file]", file=sys.stderr)
        sys.exit(1)

    with open(sys.argv[1], "rb") as f1:
        with open(sys.argv[2], "wb") as f2:
            while (byte := f1.read(1)):
                b = ord(byte)
                encoded = encode(b)
                f2.write(encoded.to_bytes())
                encoded = encode((b & 0b1111) << 4)
                f2.write(encoded.to_bytes())
