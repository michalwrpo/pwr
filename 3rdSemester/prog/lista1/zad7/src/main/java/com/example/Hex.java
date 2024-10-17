package com.example;

import java.util.HashMap;

public final class Hex {
    private Hex() throws InstantiationError {
        throw new InstantiationError("This is a static class");
    }

    /**
     * HashMap with hex values.
     */
    private static HashMap<Character, Integer> hexValues = new HashMap<Character, Integer>();
    static {
        for (int i = 0; i < 10; i++) {
            hexValues.put((char) ('0' + i), i);
        }
        hexValues.put('a', 10);
        hexValues.put('b', 11);
        hexValues.put('c', 12);
        hexValues.put('d', 13);
        hexValues.put('e', 14);
        hexValues.put('f', 15);
    }

    /**
     * Converts hexadecimal number to decimal.
     * @param hexNumber
     * @return int
     */
    public static int toDecimal(final String hexNumber) {
        int number = 0;
        int power = 1;
        char[] hexArray = hexNumber.toLowerCase().toCharArray();

        for (int i = hexArray.length - 1; i >= 0; i--) {
            if (!hexValues.containsKey(hexArray[i])) {
                throw new IllegalArgumentException("Hexadecimal number should only be composed of digits 0-9 and letters a-f");
            }

            number += hexValues.get(hexArray[i]) * power;
            power *= 16;
        }
        return number;
    }

}
