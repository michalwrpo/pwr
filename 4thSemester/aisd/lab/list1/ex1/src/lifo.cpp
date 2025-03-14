#include <lifo.hpp>

LIFO::LIFO() {
    top = nullptr;
}

LIFO::~LIFO() {
    if (top == nullptr) {
        return;
    }

    Node* cur = top;
    Node* next = top->next;
    while(cur->next != nullptr) {
        next = cur->next;
        delete(cur);
        cur = next;
    }
}

void LIFO::add(int value) noexcept(true) {
    Node* n = new Node();
    n->value = value;
    n->next = top;

    top = n;
}

int LIFO::pop() noexcept(false) {
    if (top == nullptr) {
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "LIFO is empty.");
    }

    int value = top->value;

    top = top->next;

    return value;
}
