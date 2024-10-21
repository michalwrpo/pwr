## Zad.6 

BCD - Binary Coded Decimal

127 - 0001 0010 0111
1616 - 0001 0110 0001 0110
2017 - 0010 0000 0001 0111

## Zad.7

UTF-8

`pięść` = `0x70 0x69 0xc4 0x99 0xc5 0x9b 0xc4 0x87`

`0x70` - p
`0x69` - i
`0xc4 0x99` - change characters table, returns ę
`0xc5 0x9b` - ś
`0xc4 0x87` - ć

Characters by number of bytes:
1. 0xxx xxxx
2. 110x xxxx 10xx xxxx
3. 1110 xxxx 10xx xxxx 10xx xxxx
4. 1111 0xxx 10xx xxxx 10xx xxxx 10xx xxxx

xxxx are the characters' code binary representation 

## Zad.8

Gray code / Reflected binary code (RBC)

2-bit
00 01 11 10

3-bit
000 001 011 010 110 111 101 100

4-bit
0000 0001 0011 0010 0110 0111 0101 0100 1100 1101 1111 1110 1010 1011 1001 1000

n-bit from (n-1)-bit
1. Take the list of (n-1)-bit codes as L1
2. Let L2 be reverse of L1
3. To every entry of L1 concatenate 0 at the beginning
4. To every entry of L2 concatenate 1 at the beginning
5. Concatenated list of L1 and L2 is the list of n-bit codes

> "Mówi się, że obraz to jest więcej niż 1000 słów, ale zapomina się, że to kolorowy obraz. Czarno-biały obraz to 500 do 300... 300 do 500. O! Biedronka!" ~ Błaśkiewicz