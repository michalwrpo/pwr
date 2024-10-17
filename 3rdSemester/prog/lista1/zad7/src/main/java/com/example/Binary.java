package com.example;

public final class Binary {
    private Binary() throws InstantiationError {
        throw new InstantiationError("This is a static class");
    }

    /**
     * Converts binary to decimal.
     * @param binaryNumber
     * @return int
     */
    public static int toDecimal(final String binaryNumber) {
        int number = 0;
        int power = 1;
        char[] binaryArray = binaryNumber.toCharArray();

        for (int i = binaryArray.length - 1; i >= 0; i--) {
            char digit = binaryArray[i];
            if (digit != '0' && digit != '1') {
                throw new IllegalArgumentException("Binary number should be only composed of 1's and 0's");
            }

            number += Integer.parseInt("" + digit) * power;
            power *= 2;
        }

        return number;
    }
}
