package com.michal.app;

public final class Book {
    private final int bookID;
    private final String author;
    private final String title;
    
    public Book(int bookID, String author, String title) {
        this.bookID = bookID;
        this.author = author;
        this.title = title;
    }

    public int getBookID() {
        return bookID;
    }

    public String getAuthor() {
        return author;
    }

    public String getTitle() {
        return title;
    }
}
