package com.michal.app;

import java.util.HashMap;

/**
 * Represents a library system that manages a collection of books, book copies, and customers.
 * The library allows adding new books, book copies, and customers, as well as retrieving 
 * information about each entity.
 */
public class Library {
    private HashMap<Integer, Book> books = new HashMap<Integer, Book>();
    private HashMap<Integer, Customer> customers = new HashMap<Integer, Customer>();

    private int availableBookID = 0;
    private int availableCustomerID = 0;

    // Library keeps track of books, so it is responsible for creating them.
    /**
     * Adds a new book to the library's collection with a unique ID, author, and title.
     *
     * @param author the author of the book
     * @param title  the title of the book
     */
    public void addBook(String author, String title) {
        books.put(availableBookID, new Book(availableBookID, author, title));
        availableBookID += 1;
    }

    // Library keeps track of customers, so it is responsible for creating them.
    /**
     * Adds a new customer to the library's system with a unique ID, first name, and last name.
     *
     * @param firstName the first name of the customer
     * @param lastName  the last name of the customer
     */
    public void addCustomer(String firstName, String lastName) {
        customers.put(availableCustomerID, new Customer(availableCustomerID, firstName, lastName));
        availableCustomerID += 1;
    }

    /**
     * Returns the library's collection of books.
     *
     * @return a {@code HashMap} of books, where keys are book IDs and values are {@code Book} objects
     */
    public HashMap<Integer, Book> getBooks() {
        return books;
    }

    /**
     * Returns the library's collection of customers.
     *
     * @return a {@code HashMap} of customers, where keys are customer IDs and values are {@code Customer} objects
     */
    public HashMap<Integer, Customer> getCustomers() {
        return customers;
    }

    /**
     * Returns the ID of the last book added to the library.
     *
     * @return the ID of the last added book, or -1 if no books have been added
     */
    public int getLastBookID() {
        return availableBookID - 1;
    }

    /**
     * Returns the ID of the last customer added to the library.
     *
     * @return the ID of the last added customer, or -1 if no customers have been added
     */
    public int getLastCustomerID() {
        return availableCustomerID - 1;
    }

    /**
     * Retrieves a book by its ID.
     *
     * @param id the ID of the book to retrieve
     * @return the {@code Book} with the specified ID, or {@code null} if not found
     */
    public Book getBook(int id) {
        return books.get(id);
    }

    /**
     * Retrieves a customer by their ID.
     *
     * @param id the ID of the customer to retrieve
     * @return the {@code Customer} with the specified ID, or {@code null} if not found
     */
    public Customer getCustomer(int id) {
        return customers.get(id);
    }

    // Book deals with copies so Library outsource the task.
    /**
     * Adds a new copy of an existing book to the library's collection.
     *
     * @param bookID the ID of the book for which the copy is created
     */
    public void addCopy(int bookID) {
        books.get(bookID).addCopy();
    }
}
