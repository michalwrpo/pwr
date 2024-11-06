package com.michal.app;

/**
 * Starts the program
 */
public class App {
    public static void main(String[] args) {
        Library library = new Library();
        CLI.start(library);
    }
}
