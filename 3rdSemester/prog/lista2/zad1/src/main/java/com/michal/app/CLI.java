package com.michal.app;

import java.util.InputMismatchException;
import java.util.Scanner;

// Class responsible only for command line interface, to not add it in different classes.
/**
 * Command line interface
 */
public final class CLI {
    private CLI() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    private static void interpret(String command, Library lib, Scanner scanner) throws IllegalArgumentException {
        command = command.toLowerCase();
        String[] split = command.split("\\s+");
        if (split.length != 2) {
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
                        System.out.print("Enter customer's ID: ");
                        try {
                            int id = scanner.nextInt();
                            scanner.nextLine();
                            
                            System.out.println(lib.getCustomers().get(id).getName());
                        } catch (NullPointerException | IndexOutOfBoundsException e) {
                            System.err.println("Invalid customer ID");
                        } catch (InputMismatchException e) {
                            throw new IllegalArgumentException("Id should be an integer", e);
                        }
                        break;
                    default:
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
                        System.out.print("Enter book's ID: ");
                        try {
                            int id = scanner.nextInt();
                            scanner.nextLine();

                            System.out.println(lib.getBooks().get(id).getAuthor() + " " + lib.getBooks().get(id).getTitle());
                        } catch (NullPointerException | IndexOutOfBoundsException e) {
                            System.err.println("Invalid book ID");
                        } catch (InputMismatchException e) {
                            throw new IllegalArgumentException("Id should be an integer", e);
                        }
                        break;
                    default:
                        throw new IllegalArgumentException("Invalid command.");                
                }
                break;
            case "copy":
                switch (split[1]) {
                    case "new":
                        System.out.print("Enter book's ID: ");
                        try {
                            int bookID = scanner.nextInt();
                            scanner.nextLine();
    
                            lib.addCopy(bookID);
                            System.out.println("Added copy of " + lib.getBook(bookID).getTitle() + " with ID" + lib.getBook(bookID).getLastCopyID());
                        } catch (NullPointerException | IndexOutOfBoundsException e) {
                            System.err.println("Invalid book ID"); 
                        }catch (InputMismatchException e) {
                            throw new IllegalArgumentException("Id should be an integer", e);
                        }
                        break;
                    case "lend":
                        System.out.print("Enter book's ID: ");
                        try {
                            int bookID = scanner.nextInt();
                            scanner.nextLine();
                            System.out.print("Enter copy's ID: ");
                            int copyID = scanner.nextInt();
                            scanner.nextLine();

                            System.out.print("Enter customer's ID: ");
                            int customerID = scanner.nextInt();
                            scanner.nextLine();
    
                            lib.getCustomer(customerID).rentBook(lib.getBook(bookID).getCopy(copyID));
                        } catch (NullPointerException | IndexOutOfBoundsException e) {
                            System.err.println("Invalid book's, copy's or customer's ID");
                        } catch (InputMismatchException e) {
                            throw new IllegalArgumentException("Id should be an integer", e);
                        }
                        break;
                    case "return":
                        System.out.print("Enter book's ID: ");
                        try {
                            int book = scanner.nextInt();
                            scanner.nextLine();
                            System.out.print("Enter copy's ID: ");
                            int copy = scanner.nextInt();
                            scanner.nextLine();
                            System.out.print("Enter customer's ID: ");
                            int customer = scanner.nextInt();
                            scanner.nextLine();
    
                            lib.getCustomer(customer).returnBook(lib.getBook(book).getCopy(copy));
                        } catch (NullPointerException | IndexOutOfBoundsException e) {
                            System.err.println("Invalid book's, copy's or customer's ID");
                        } catch (InputMismatchException e) {
                            throw new IllegalArgumentException("Id should be an integer", e);
                        }
                        break;
                    default:
                        throw new IllegalArgumentException("Invalid command.");                
                }
                break;
            default:
            throw new IllegalArgumentException("Invalid command.");                
        }
    }

    /**
     * Starts CLI.
     * @param lib Library
     */
    public static void start(Library lib) {
        boolean exited = false;
        Scanner scanner = new Scanner(System.in);
        while (!exited) {
            System.out.print("LibrarySystem: ");

            if (!scanner.hasNextLine()) {
                System.out.println("No more input available. Exiting.");
                break;
            }

            String command = scanner.nextLine();

            if (command.equalsIgnoreCase("exit")) {
                exited = true;
                break;
            }

            try {
                interpret(command, lib, scanner);
            } catch (IllegalArgumentException e) {
                System.err.println(e.getMessage());
            }
        }
        scanner.close();
    }     
}
