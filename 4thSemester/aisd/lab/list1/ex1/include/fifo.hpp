#ifndef FIFO_HPP
#define FIFO_HPP

#include <stdexcept>

class FIFO {
    private:
        class Node {
            public:
            int value;
            Node* next;
        };
        Node* first;

    public:
        FIFO();

        void add(int value) noexcept(true);

        int pop() noexcept(false);
};

#endif