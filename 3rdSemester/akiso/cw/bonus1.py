import re

#splits a number into list of digits
def split(num):
    result = []
    for i in range(len(str(num))):
        result.append(int(str(num)[i]))
    return result

#turns a number into something recognizable by other functions
def normalize(num):
    if type(num) == str:
        num.replace(' ', '')
        num = num.split(",")
        if len(num) == 1:
            num = split(num[0])
    if type(num) == list:
        result = list(map(int, num))
    elif type(num) == int:
        result = split(num)
    return result

#handled by base_to_nbase(num, 2)
def bin_to_nbin(num):
    new_num = []
    plus = 0
    plus_one = 0
    plus_two = 0
    for i in range(0, len(str(num))):
        if num[-i-1] == '1':
            if i % 2 == 0:
                plus += 1
            else:
                plus_one += 1
                plus += 1
        while plus >= 2 and plus_one >= 1:
            plus -= 2
            plus_one -= 1
        new_num.insert(0, plus % 2)
        plus_one += plus // 2
        plus_two += plus // 2
        plus_two, plus_one, plus = 0, plus_two, plus_one
    while (plus + plus_one + plus_two) != 0:
        while plus >= 2 and plus_one >= 1:
            plus -= 2
            plus_one -= 1
        new_num.insert(0, plus % 2)
        plus_one += plus // 2
        plus_two += plus // 2
        plus_two, plus_one, plus = 0, plus_two, plus_one
    return new_num

def base_to_nbase(num, base):
    if type(base) != int:
        print("Base should be a number")
        return []
    if base < 2:
        print("Base should be bigger than 1, got", base)
        return []
    new_num = []
    plus = 0
    plus_one = 0
    plus_two = 0
    for i in range(len(num)):
        if num[-i-1] != 0:
            if i % 2 == 0:
                plus += num[-i-1]
            else:
                plus_one += num[-i-1]
                plus += (base - 1) * num[-i-1]
        while plus >= base and plus_one >= 1:
            plus -= base
            plus_one -= 1
        new_num.insert(0, plus % base)
        plus_one += (base - 1) * (plus // base)
        plus_two += (plus // base)
        plus_two, plus_one, plus = 0, plus_two, plus_one
    while (plus + plus_one + plus_two) != 0:
        while plus >= base and plus_one >= 1:
            plus -= base
            plus_one -= 1
        new_num.insert(0, plus % base)
        plus_one += (base - 1) * (plus // base)
        plus_two += (plus // base)
        plus_two, plus_one, plus = 0, plus_two, plus_one
    return new_num

def convert_to_decimal(num, base):
    if type(base) != int:
        print("Base should be a number, got", base)
        return []
    if base in [-1, 0, 1]:
        print("Base being converted should be bigger than 1 or less than -1, got", base)
    result = 0
    for i in range(len(num)):
        digit = int(num[-i-1])
        if digit >= abs(base):
            print("Digits should be smaller than the base, got", digit)
            return []
        result += digit * (base**i)
    return result

def convert_decimal_to_positive_base(num, base):
    if type(base) != int:
        print("Base should be a number, got", base)
        return []
    if base < 2:
        print("Base should be at least 2, got", base)
    result = []
    while num != 0:
        result.insert(0, num % base)
        num = num // base
    return result

def convert_bases(num, base1, base2):
    if type(base1) != int or type(base2) != int:
        print("Bases should be integers, got", base1, "and", base2)
        return
    if base1 in [-1, 0, 1] or base2 in [-1, 0, 1]:
        print("Bases should be larger than 1 or smaller than -1, got", base1, "and", base2)
        return
    if type(num) == int:
        num = split(num)
    if base2 > 1:
        result = convert_decimal_to_positive_base(convert_to_decimal(num, base1), base2)
    else:
        deci = convert_to_decimal(num, base1)
        if deci < 0:
            print("Starting number has to be positive")
            return
        result = base_to_nbase(convert_decimal_to_positive_base(deci, abs(base2)), abs(base2))
    if abs(base2) <= 10:
        result = ''.join(map(str,result))
    return result
        

ended = False
while not ended:
    inpt = input("Enter a command (h for help): ")
    if inpt[0] == 'h':
        print("c - convert a number from one base to another, if base larger than decimal is used, number should consist of digits separeted by commas \nh - display this message \nq - quit")
    elif inpt[0] == 'q':
        ended = True
        break
    elif inpt[0] == 'c':
        b1 = input("Base being converted from: ")
        b2 = input("Base being converted to: ")
        number = input("Number being converted: ")
        if re.match("-?[0-9]+$", b1) and re.match("-?[0-9]+$", b2) and re.match("^[0-9, ]+", number):
            print("Result:", convert_bases(normalize(number), int(b1), int(b2)))
        else:
            print("Wrong inputs")