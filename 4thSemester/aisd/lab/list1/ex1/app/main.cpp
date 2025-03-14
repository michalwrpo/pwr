#include <iostream>

#include <fifo.hpp>
#include <lifo.hpp>

int main() {
    FIFO* fifo = new FIFO();

    for (int i = 0; i < 50; i++) {
        std::cout << "Adding " << i << " to FIFO" << std::endl;
        fifo->add(i);
    }
    
    for (int i = 0; i < 50; i++) {
        std::cout << "Removed " << fifo->pop() << " from FIFO" << std::endl;
    }

    delete fifo;
    LIFO* lifo = new LIFO();

    for (int i = 0; i < 50; i++) {
        std::cout << "Adding " << i << " to LIFO" << std::endl;
        lifo->add(i);
    }
    
    for (int i = 0; i < 50; i++) {
        std::cout << "Removed " << lifo->pop() << " from LIFO" << std::endl;
    }

    delete lifo;
}