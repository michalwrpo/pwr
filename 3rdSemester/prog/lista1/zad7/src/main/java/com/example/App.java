package com.example;

/**
 * Main class.
 *
 */
public final class App {
    private App() throws InstantiationError {
        throw new InstantiationError("This is a static class");
    }

    /**
     * Main function.
     * @param args
     */
    public static void main(final String[] args) {
        String binaryNumber = "b1101";
        String hexNumber = "0x1f";
        System.out.println(binaryNumber + " -> " + Converter.convert(binaryNumber));
        System.out.println(hexNumber + " -> " + Converter.convert(hexNumber));
    }
}
