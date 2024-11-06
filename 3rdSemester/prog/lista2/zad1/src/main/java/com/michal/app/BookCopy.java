package com.michal.app;

/**
 * Represents a copy of a book in a library system, with information about its
 * availability, the associated book ID, and the customer currently borrowing it.
 */
public class BookCopy {
    private final int copyID;
    private final int bookID;
    private int customerID;
    private boolean available;
    
    /**
     * Constructs a new BookCopy with the specified copy ID and book ID.
     * The new book copy is marked as available, with no customer assigned.
     *
     * @param copyID the unique identifier for this book copy
     * @param bookID the identifier for the book that this copy represents
     */
    public BookCopy(int copyID, int bookID) {
        this.copyID = copyID;
        this.bookID = bookID;
        this.customerID = -1;
        this.available = true;
    }

    /**
     * Returns the unique ID of this book copy.
     *
     * @return the copy ID of the book
     */
    public int getCopyID() {
        return copyID;
    }

    /**
     * Returns the ID of the book that this copy represents.
     *
     * @return the book ID associated with this copy
     */
    public int getBookID() {
        return bookID;
    }

    /**
     * Returns the ID of the customer who has borrowed this book copy.
     * If the book is available, returns -1.
     *
     * @return the customer ID if the book is borrowed, or -1 if available
     */
    public int getCustomerID() {
        return customerID;
    }

    /**
     * Checks if the book copy is currently available.
     *
     * @return {@code true} if the book copy is available, {@code false} otherwise
     */
    public boolean getAvailable() {
        return available;
    }

    /**
     * Borrows the book copy, setting it as unavailable and assigning the specified
     * customer ID to it.
     *
     * @param customerID the ID of the customer borrowing this book copy; must be non-negative
     * @throws IllegalArgumentException if {@code customerID} is negative
     * @throws IllegalStateException if the book copy is already borrowed
     */
    public void borrowCopy(int customerID) throws IllegalArgumentException, IllegalStateException {
        if (available && customerID >= 0) {
            this.customerID = customerID;
            this.available = false;
        } else if (!available) {
            throw new IllegalStateException("Book copy is not available.");
        } else {
            throw new IllegalArgumentException("customerID should be nonnegative, got " + customerID);
        }
    }

    /**
     * Returns the book copy, making it available and clearing the customer ID.
     *
     * @throws IllegalStateException if the book copy is already available
     */
    public void returnCopy() throws IllegalStateException {
        if (available) {
            throw new IllegalStateException("Book is already available.");
        } else {
            this.customerID = -1;
            this.available = true;
        }
    }
}
