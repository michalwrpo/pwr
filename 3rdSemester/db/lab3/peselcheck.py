file = open("data.txt", 'r')
data = file.read().strip().split('\n')

for i in range(len(data)):
    data[i] = data[i][1:-2].split(", ")
    for j in range(len(data[i])):
        data[i][j] = data[i][j][1:-1]

pesels = [ row[0] for row in data]

i = 0

for i in range(len(data)):
    birthdate = data[i][3]
    year = birthdate[2:4]
    month = birthdate[5:7]
    day = birthdate[8:10]
    yeardigit = birthdate[0]
    data[i][0] = str(year) + data[i][0][2:]
    if yeardigit == '2':
        data[i][0] = data[i][0][:2] + str(20 + int(month)) + data[i][0][4:]
    else:
        data[i][0] = data[i][0][:2] + str(month) + data[i][0][4:]
    data[i][0] = data[i][0][:4] + str(day) + data[i][0][6:]
    if (data[i][4] == 'K' and int(data[i][0][-2]) % 2 == 1):
        data[i][0] = data[i][0][:9] + str(int(data[i][0][-2]) + 1) + data[i][0][-1]
    if (data[i][4] == 'M' and int(data[i][0][-2]) % 2 == 0):
        data[i][0] = data[i][0][:9] + str(int(data[i][0][-2]) - 1) + data[i][0][-1]
    pesel = data[i][0]
    p1 = int(pesel[0])
    p2 = int(pesel[1])
    p3 = int(pesel[2])
    p4 = int(pesel[3])
    p5 = int(pesel[4])
    p6 = int(pesel[5])
    p7 = int(pesel[6])
    p8 = int(pesel[7])
    p9 = int(pesel[8])
    p10 = int(pesel[9])
    p11 = int(pesel[10])
    last_digit = (10 - ((p1 + 3*p2 + 7*p3 + 9*p4 + p5 + 3*p6 + 7*p7 + 9*p8 + p9 + 3*p10) % 10)) % 10
    pesel = pesel[:-1] + str(last_digit)
    data[i][0] = pesel

file = open("data.txt", 'w')


for row in data:
    file.write("(")
    for j in range(len(row) - 1):
        file.write("'" + str(row[j]) + "', ")

    file.write("'" + str(row[-1]) + "'")
    file.write("),\n")

file.close()