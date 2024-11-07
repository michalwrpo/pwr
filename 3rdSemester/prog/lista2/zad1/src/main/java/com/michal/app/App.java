package com.michal.app;

/**
 * Starts the program
 */
public final class App {
    private App() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }
    public static void main(String[] args) {
        Library library = new Library();
        CLI.start(library);
    }
}
