package com.michal.app;

import java.util.ArrayList;

/**
 * Represents a customer in the library system, with information about their
 * ID, name, and a list of books they have rented.
 */
public class Customer {
    private final int customerID;
    private String firstName;
    private String lastName;
    private ArrayList<BookCopy> rentedBooks;

    /**
     * Constructs a new Customer with the specified ID, first name, and last name.
     *
     * @param customerID the unique identifier for this customer; must be non-negative
     * @param firstName  the customer's first name
     * @param lastName   the customer's last name
     * @throws IllegalArgumentException if {@code customerID} is negative
     */
    public Customer(int customerID, String firstName, String lastName) {
        if (customerID < 0) {
            throw new IllegalArgumentException("customerID should be nonnegative, got " + customerID);
        }
        this.customerID = customerID;
        this.firstName = firstName;
        this.lastName = lastName;
        this.rentedBooks = new ArrayList<BookCopy>();
    }

    /**
     * Returns the unique ID of the customer.
     *
     * @return the customer ID
     */
    public int getCustomerID() {
        return customerID;
    }

    /**
     * Returns the customer's first name.
     *
     * @return the first name of the customer
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Returns the customer's last name.
     *
     * @return the last name of the customer
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Returns the full name of the customer, combining first and last names.
     *
     * @return the full name of the customer in the format "firstName lastName"
     */
    public String getName() {
        return firstName + " " + lastName;
    }

    /**
     * Returns a list of IDs for the books currently rented by the customer.
     *
     * @return an {@code ArrayList<Integer>} containing the copy IDs of rented books
     */
    public ArrayList<Integer> getRentedBooks() {
        ArrayList<Integer> bookIDs = new ArrayList<Integer>();
        for (BookCopy book : rentedBooks) {
            bookIDs.add(book.getCopyID());
        }
        return bookIDs;
    }

    /**
     * Updates the customer's first name.
     *
     * @param newName the new first name to set for the customer
     */
    public void setFirstName(String newName) {
        this.firstName = newName;
    }

    /**
     * Updates the customer's last name.
     *
     * @param newName the new last name to set for the customer
     */
    public void setLastName(String newName) {
        this.lastName = newName;
    }

    /**
     * Rents a book for the customer, attempting to borrow the specified book copy.
     * If the book copy is already rented, an error message is printed.
     *
     * @param copy the {@code BookCopy} to rent
     */
    public void rentBook(BookCopy copy) {
        try {
            copy.borrowCopy(customerID);
            rentedBooks.add(copy);
        } catch (IllegalStateException e) {
            System.err.println(e.getMessage());
        }
    }

    /**
     * Returns a rented book, making the book copy available and removing it from
     * the customer's list of rented books. If the customer does not have the book,
     * an error message is printed.
     *
     * @param copy the {@code BookCopy} to return
     */
    public void returnBook(BookCopy copy) {
        if (rentedBooks.contains(copy)) {
            try {
                copy.returnCopy();
            } catch (IllegalStateException e) {
                System.err.println(e.getMessage());
            }
            rentedBooks.remove(copy);
        } else {
            System.err.println("This customer doesn't have this book!");
        }
    }
}
