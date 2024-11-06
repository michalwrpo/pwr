package com.michal.app;

/**
 * Represents a book in the library system, with information about its ID,
 * author, and title.
 */
public final class Book {
    private final int bookID;
    private final String author;
    private final String title;
    
    /**
     * Constructs a new Book with the specified ID, author, and title.
     *
     * @param bookID the unique identifier for this book
     * @param author the author of the book
     * @param title  the title of the book
     */
    public Book(int bookID, String author, String title) {
        this.bookID = bookID;
        this.author = author;
        this.title = title;
    }

    /**
     * Returns the unique ID of the book.
     *
     * @return the book ID
     */
    public int getBookID() {
        return bookID;
    }

    /**
     * Returns the author of the book.
     *
     * @return the author's name
     */
    public String getAuthor() {
        return author;
    }

    /**
     * Returns the title of the book.
     *
     * @return the book's title
     */
    public String getTitle() {
        return title;
    }
}
