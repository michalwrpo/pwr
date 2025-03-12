#include <fifo.hpp>

#include <iostream>

FIFO::FIFO() {
    first = nullptr;
}

void FIFO::add(int value) noexcept(true) {
    Node* n = new Node();
    n->value = value;
    n->next = nullptr;

    if (first == nullptr) {
        first = n;
        return;
    }

    Node* nodeptr = first;
    
    while (nodeptr->next != nullptr) {
        nodeptr = nodeptr->next;
    }
    
    nodeptr->next = n;

    nodeptr = first;
}

int FIFO::pop() noexcept(false) {
    if (first == nullptr) {
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "FIFO is empty.");
    }

    int value = first->value;

    Node* temp = first->next;

    free(first);
    
    first = temp;

    return value;
}