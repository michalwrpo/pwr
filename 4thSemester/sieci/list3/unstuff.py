def xor(a, b):
    return ''.join(['0' if i == j else '1' for i, j in zip(a, b)])


def mod2div(dividend, divisor):
    pick = len(divisor)
    tmp = dividend[:pick]

    while pick < len(dividend):
        if tmp[0] == '1':
            tmp = xor(divisor, tmp) + dividend[pick]
        else:
            tmp = xor('0'*pick, tmp) + dividend[pick]
        tmp = tmp[1:]
        pick += 1

    if tmp[0] == '1':
        tmp = xor(divisor, tmp)
    else:
        tmp = xor('0'*pick, tmp)

    return tmp[1:]  # CRC result


def verify_crc(data_with_crc, generator='10001000000100001'):
    return mod2div(data_with_crc, generator) == '0'*(len(generator)-1)


def bit_unstuff(data):
    unstuffed = ''
    count = 0
    i = 0
    while i < len(data):
        bit = data[i]
        unstuffed += bit
        if bit == '1':
            count += 1
            if count == 5:
                i += 1  # skip stuffed '0'
                count = 0
        else:
            count = 0
        i += 1
    return unstuffed


def extract_frame(data):
    FLAG = '01111110'
    if data.startswith(FLAG) and data.endswith(FLAG):
        return data[len(FLAG):-len(FLAG)]
    else:
        raise ValueError("Nieprawidłowa ramka: brak poprawnych flag.")


if __name__ == '__main__':
    input_file = 'W.txt'
    output_file = 'Z_odtworzony.txt'
    generator = '10001000000100001'  # CRC-16-CCITT

    # 1. Wczytaj zawartość pliku W
    with open(input_file, 'r') as f:
        raw_frame = f.read().strip()

    try:
        # 2. Usuń flagi
        stuffed_data = extract_frame(raw_frame)

        # 3. Wykonaj de-stuffing
        unstuffed_data = bit_unstuff(stuffed_data)

        # 4. Sprawdź poprawność CRC
        if verify_crc(unstuffed_data, generator):
            # 5. Usuń CRC i zapisz dane
            original_data = unstuffed_data[:-len(generator)+1]
            with open(output_file, 'w') as out:
                out.write(original_data)
            print("Dane poprawne, zapisano do:", output_file)
        else:
            print("Błąd CRC: dane uszkodzone.")
    except ValueError as ve:
        print("Błąd:", ve)
