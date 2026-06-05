#include "order.hpp"

#include <array>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

std::ostream& operator<<(std::ostream& out, Compare v) {
    switch (v) {
    case Compare::Incomparable: return out << "incomparable";
    case Compare::Equal:        return out << "equal";
    case Compare::Greater:      return out << "greater";
    case Compare::Less:         return out << "less";
    }
}

