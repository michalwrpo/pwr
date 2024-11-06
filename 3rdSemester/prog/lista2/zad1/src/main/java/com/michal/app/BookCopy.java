package com.michal.app;

public class BookCopy {
    private final int copyID;
    private final int bookID;
    private int customerID;
    private boolean available;
    
    public BookCopy(int copyID, int bookID) {
        this.copyID = copyID;
        this.bookID = bookID;
        this.customerID = -1;
        this.available = true;
    }

    public int getCopyID() {
        return copyID;
    }

    public int getBookID() {
        return bookID;
    }

    public int getCustomerID() {
        return customerID;
    }

    public boolean getAvailable() {
        return available;
    }

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

    public void returnCopy() throws IllegalStateException {
        if (available) {
            throw new IllegalStateException("Book is already available.");
        } else {
            this.customerID = -1;
            this.available = true;
        }
    }
}
