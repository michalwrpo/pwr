package com.michal.app;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

/**
 * Unit tests for Customer.
 */
public class CustomerTest {
    Customer customer = new Customer(0, "Peter", "Johnson");

    @Test
    public void testFirstName() {
        assertEquals(customer.getFirstName(), "Peter");
    }

    @Test
    public void testLastName() {
        assertEquals(customer.getLastName(), "Johnson");
    }

    @Test
    public void testName() {
        assertEquals(customer.getName(), "Peter Johnson");
    }

    @Test
    public void testID() {
        assertEquals(customer.getCustomerID(), 0);
    }
}
