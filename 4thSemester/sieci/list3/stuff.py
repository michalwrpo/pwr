def read_bits_from_file(filename):
    with open(filename, 'r') as f:
        content = f.read().strip()
        return ''.join(filter(lambda x: x in '01', content))


def bit_stuff(data):
    stuffed = ''
    count = 0
    for bit in data:
        stuffed += bit
        if bit == '1':
            count += 1
            if count == 5:
                stuffed += '0'  # bit stuffing
                count = 0
        else:
            count = 0
    return stuffed


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


def xor(a, b):
    return ''.join(['0' if i == j else '1' for i, j in zip(a, b)])


def mod2div(dividend, divisor):
    pick = len(divisor)
    tmp = dividend[:pick]

    while pick < len(dividend):
        if tmp[0] == '1':
            tmp = xor(divisor, tmp) + dividend[pick]
        else:
            tmp = tmp + dividend[pick]
        tmp = tmp[1:]
        pick += 1

    if tmp[0] == '1':
        tmp = xor(divisor, tmp)

    return tmp[1:]  # CRC


# CRC-16-CCITT
def encode_data(data, generator='10001000000100001'):
    # Append zeros to the data
    appended_data = data + '0'*(len(generator)-1)
    remainder = mod2div(appended_data, generator)
    return data + remainder


def verify_crc(data_with_crc, generator='10001000000100001'):
    return mod2div(data_with_crc, generator) == '0'*(len(generator)-1)


def write_frames_to_file(output_filename, bitstream):
    with open(output_filename, 'w') as f:
        for frame in bitstream:
            f.write(frame)

def add_flags(frame):
    FLAG = '01111110'
    return FLAG + frame + FLAG    

def to_frames(bits, size, generator):
    frames = []
    while len(bits) > size:
        frame = bits[:size]
        
        # CRC
        frame = encode_data(frame, generator)

        # bit stuffing
        frame = bit_stuff(frame)

        # add flags
        frame = add_flags(frame)

        frames.append(frame)
        bits = bits[size:]
    frame = encode_data(bits)
    frame = bit_stuff(frame)
    frame = add_flags(frame)
    frames.append(frame)
    
    return frames

if __name__ == '__main__':
    input_file = 'Z.txt'
    output_file = 'W.txt'
    generator = '10001000000100001'  # CRC-16-CCITT
    size = 100

    # load data
    bits = read_bits_from_file(input_file)

    frames = to_frames(bits, size, generator)

    write_frames_to_file(output_file, frames)

    print("Dane zostały sformatowane i zapisane do pliku:", output_file)

    # (Opcjonalnie) Odczytaj i sprawdź poprawność
    print("Sprawdzanie poprawności CRC z zapisanej ramki:")
    correct, incorrect = 0, 0
    with open(output_file, 'r') as f:
        raw = f.read().strip()
        if raw.startswith('01111110') and raw.endswith('01111110'):
            raw = raw.split("01111110")
            for bits in raw:
                if len(bits) == 0:
                    raw.remove(bits)

            for frame in raw:
                unstuffed = bit_unstuff(frame)
                is_valid = verify_crc(unstuffed, generator)
                if is_valid:
                    correct += 1
                else:
                    incorrect += 1
            print(f"Ramki poprawne: {correct}\nRamki niepoprawne: {incorrect}")    
        else:
            print("Niepoprawny format ramki (brak flag).")
