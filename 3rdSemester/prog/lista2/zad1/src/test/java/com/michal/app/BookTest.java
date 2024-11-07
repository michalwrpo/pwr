package com.michal.app;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

/**
 * Unit tests for Book.
 */
public class BookTest {
    Book book = new Book(0, "John Smith", "Book 2");
    BookCopy copy = new BookCopy(0, 0);

    @Test
    public void testTitle() {
        assertEquals(book.getTitle(), "Book 2");
    }

    @Test
    public void testAuthor() {
        assertEquals(book.getAuthor(), "John Smith");
    }

    @Test
    public void testID() {
        assertEquals(book.getBookID(), 0);
    }

    @Test
    public void testCopyID() {
        assertEquals(copy.getCopyID(), 0);
    }

    @Test
    public void testOriginalID() {
        assertEquals(copy.getBookID(), 0);
    }
}
