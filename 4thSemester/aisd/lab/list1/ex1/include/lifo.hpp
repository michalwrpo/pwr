#ifndef LIFO_HPP
#define LIFO_HPP

#include <stdexcept>

class LIFO {
    private:
        class Node {
            public:
            int value;
            Node* next;
        };
        Node* top;

    public:
        LIFO();

        void add(int value) noexcept(true);

        int pop() noexcept(false);
};

#endif