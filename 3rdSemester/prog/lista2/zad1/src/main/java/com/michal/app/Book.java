package com.michal.app;

import java.util.HashMap;

/**
 * Represents a book in the library system, with information about its ID,
 * author, and title.
 */
public final class Book {
    private final int bookID;
    private final String author;
    private final String title;
    private HashMap<Integer, BookCopy> copies = new HashMap<Integer, BookCopy>();
    private int availableCopyID = 0;

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

    /**
     * Returns the library's collection of book copies.
     *
     * @return a {@code HashMap} of book copies, where keys are copy IDs and values are {@code BookCopy} objects
     */
    public HashMap<Integer, BookCopy> getCopies() {
        return copies;
    }
    
    /**
     * Returns the ID of the last book copy added to the library.
     *
     * @return the ID of the last added book copy, or -1 if no copies have been added
     */
    public int getLastCopyID() {
        return availableCopyID - 1;
    }

    /**
     * Retrieves a book copy by its ID.
     *
     * @param id the ID of the book copy to retrieve
     * @return the {@code BookCopy} with the specified ID, or {@code null} if not found
     */
    public BookCopy getCopy(int id) {
        return copies.get(id);
    }

    
    /**
     * Adds a new copy of the book.
     */
    public void addCopy() {
        copies.put(availableCopyID, new BookCopy(availableCopyID, bookID));
        availableCopyID += 1;
    }

}
