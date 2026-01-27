import sys

parity_check = [
    [1, 0, 1, 0, 1, 0, 1],
    [0, 1, 1, 0, 0, 1, 1],
    [0, 0, 0, 1, 1, 1, 1]
]

def decode(byte):
    outbyte = 0
    check = 0
    parity = 0
    for i in range(8):
        parity ^= (byte & (1 << i)) >> i

    for i in range(len(parity_check[0])):
        bit = (byte & (1 << (7 - i))) >> (7 - i)
        for j in range(len(parity_check)):
            if parity_check[j][i] == 1:
                check ^= bit << j

    if check > 0:
        byte ^= (1 << check)

    outbyte |= (byte & 0b00100000) >> 2
    outbyte |= (byte & 0b00001000) >> 1
    outbyte |= (byte & 0b00000100) >> 1
    outbyte |= (byte & 0b00000010) >> 1

    # if check > 0:
    #     print(f"check {check}")

    # if parity > 0:
    #     print("parity")

    if check > 0 and parity > 0:
        return outbyte, False
    return outbyte, True


if __name__ == "__main__":
    # print(decode(102))
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} [in_file] [out_file]", file=sys.stderr)
        sys.exit(1)

    half = 0
    outbyte = 0
    errors = 0

    with open(sys.argv[1], "rb") as f1:
        with open(sys.argv[2], "wb") as f2:
            while (byte := f1.read(1)):
                b = ord(byte)
                res = decode(b)
                outbyte += res[0]
                errors += 0 if res[1] else 1

                if half == 0:
                    half += 1
                    outbyte <<= 4
                else:
                    half = 0
                    f2.write(outbyte.to_bytes())
                    outbyte = 0

    print(f"Double errors: {errors}")

