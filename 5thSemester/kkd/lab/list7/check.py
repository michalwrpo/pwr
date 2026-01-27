import sys

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} [file1] [file2]", file=sys.stderr)
        sys.exit(1)


    count = 0

    with open(sys.argv[1], "rb") as f1:
        with open(sys.argv[2], "rb") as f2:
            while (b1 := f1.read(1)) and (b2 := f2.read(1)):
                byte1 = ord(b1)
                byte2 = ord(b2)
                h1 = byte1 >> 4
                h2 = byte2 >> 4
                l1 = byte1 - (h1 << 4)
                l2 = byte2 - (h2 << 4)
                if (h1 != h2):
                    count += 1
                if (l1 != l2):
                    count += 1

    print(f"Different 4-bit blocks: {count}")