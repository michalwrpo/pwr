package com.michal.app;

import java.util.ArrayList;

public class Library {
    private ArrayList<Customer> customers = new ArrayList<Customer>();
    private ArrayList<Book> books = new ArrayList<Book>();
    private ArrayList<BookCopy> copies = new ArrayList<BookCopy>();

    public void addBook(String author, String title) {
        if (!books.isEmpty()) {
            books.add(new Book(getLastBookID() + 1, author, title));
        } else {
            books.add(new Book(0, author, title));
        }
    }

    public void addCopy(int bookID) {
        if (!copies.isEmpty()) {
            copies.add(new BookCopy(getLastCopyID() + 1, bookID));
        } else {
            copies.add(new BookCopy(0, bookID));
        }
    }

    public void addCustomer(String firstName, String lastName) {
        if (!customers.isEmpty()) {
            customers.add(new Customer(getLastCustomerID() + 1, firstName, lastName));
        } else {
            customers.add(new Customer(0, firstName, lastName));
        }
    }

    public ArrayList<Book> getBooks() {
        return books;
    }

    public ArrayList<BookCopy> getCopies() {
        return copies;
    }

    public ArrayList<Customer> getCustomers() {
        return customers;
    }
    
    public int getLastBookID() {
        return books.getLast().getBookID();
    }    
    public int getLastCopyID() {
        return copies.getLast().getCopyID();
    }    
    public int getLastCustomerID() {
        return customers.getLast().getCustomerID();
    }    
}
