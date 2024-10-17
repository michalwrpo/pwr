package com.example;

public final class Converter {
    private Converter() throws InstantiationError {
        throw new InstantiationError("This is a static class");
    }

    public static int convert(String number) {
        number = number.toLowerCase();
        if ("b".equals(number.substring(0, 1))) {
            return Binary.toDecimal(number.substring(1));
        } else if ("0x".equals(number.substring(0, 2))) {
            return Hex.toDecimal(number.substring(2));
        } else {
            throw new IllegalArgumentException("Number should be binary (begins with 'b') or hexadecimal (begins with '0x')");
        }
    }
}
