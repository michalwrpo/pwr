package com.michal.app;

import java.util.Scanner;

public final class CLI {
    private void interpret(String command, Library lib) throws IllegalArgumentException {
        Scanner scanner = new Scanner(System.in);
        command = command.toLowerCase();
        String[] split = command.split("\\s+");
        if (split.length != 2) {
            scanner.close();
            throw new IllegalArgumentException("Invalid command");
        }
        switch (split[0]) {
            case "customer":
                switch (split[1]) {
                    case "new":
                        System.out.print("Enter customer's first name: ");
                        String firstName = scanner.nextLine();
                        System.out.print("Enter customer's last name: ");
                        String lastName = scanner.nextLine();

                        lib.addCustomer(firstName, lastName);
                        System.out.println("Added customer: ID" + lib.getLastCustomerID() + " " + firstName + " " + lastName);
                        break;
                    case "show":
                        System.out.println("Enter customer's ID");
                        int id = scanner.nextInt();
                        try {
                            System.out.println(lib.getCustomers().get(id).getName());
                        } catch (IndexOutOfBoundsException e) {
                            System.err.println("Invalid customer ID");
                        }
                    default:
                        scanner.close();
                        throw new IllegalArgumentException("Invalid command.");
                }
                break;
            case "book": 
                switch (split[1]) {
                    case "new":
                        System.out.print("Enter book's author: ");
                        String author = scanner.nextLine();
                        System.out.print("Enter book's title: ");
                        String title = scanner.nextLine();

                        lib.addBook(author, title);
                        System.out.println("Added book: ID" + lib.getLastBookID() + " " + author + " " + title);
                        break;
                    case "show":
                        System.out.println("Enter book's ID");
                        int id = scanner.nextInt();
                        try {
                            System.out.println(lib.getBooks().get(id).getAuthor() + " " + lib.getBooks().get(id).getTitle());
                        } catch (IndexOutOfBoundsException e) {
                            System.err.println("Invalid book ID");
                        }
                    default:
                        scanner.close();
                        throw new IllegalArgumentException("Invalid command.");                
                    }
                break;
            case "copy":
                switch (split[1]) {
                    case "new":
                        System.out.print("Enter book's ID: ");
                        int id = scanner.nextInt();

                        lib.addCopy(id);
                        System.out.println("Added copy of " + lib.getBooks().get(id).getTitle() + " with ID" + lib.getLastCopyID());
                        break;
                    case "show":
                        
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        scanner.close();
    }

    public void start(Library lib) {
        boolean exited = false;
        Scanner scanner = new Scanner(System.in);
        while (!exited) {
            String command = scanner.nextLine();
            interpret(command, lib);
        }
        scanner.close();
    }     
}
