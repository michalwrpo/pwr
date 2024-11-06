package com.michal.app;

import java.util.ArrayList;

public class Customer {
    private final int customerID;
    private String firstName;
    private String lastName;
    private ArrayList<BookCopy> rentedBooks;

    public Customer(int customerID, String firstName, String lastName) {
        if (customerID < 0) {
            throw new IllegalArgumentException("customerID should be nonnegative, got " + customerID);
        }
        this.customerID = customerID;
        this.firstName = firstName;
        this.lastName = lastName;
        this.rentedBooks = new ArrayList<BookCopy>();
    }

    public int getCustomerID() {
        return customerID;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getName() {
        return firstName + " " + lastName;
    }

    public ArrayList<Integer> getRentedBooks() {
        ArrayList<Integer> bookIDs = new ArrayList<Integer>();
        for (BookCopy book : rentedBooks) {
            bookIDs.add(book.getCopyID());
        }
        return bookIDs;
    }

    public void setFirstName(String newName) {
        this.firstName = newName;
    }

    public void setLastName(String newName) {
        this.lastName = newName;
    }

    public void rentBook(BookCopy copy) {
        try {
            copy.borrowCopy(customerID);
            rentedBooks.add(copy);
        } catch (IllegalStateException e) {
            System.err.println(e.getMessage());
        }
    }

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
