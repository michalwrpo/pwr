#include <lifo.hpp>

LIFO::LIFO() {
    top = nullptr;
}

void LIFO::add(int value) noexcept(true) {
    Node n;
    n.value = value;
    n.next = top;
}

int LIFO::pop() noexcept(false) {
    if (top = nullptr) {
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "LIFO is empty.");
    }

    int value = top->value;

    top = top->next;

    return value;
}