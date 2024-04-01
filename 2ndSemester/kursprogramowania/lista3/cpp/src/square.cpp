#include <square.hpp>

#include <cmath>
#include <string>

Square::Square(double side) noexcept(false)
{
    if (side <= 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "side length should be positive, got " + std::to_string(side));

    this->side = side;
}

double Square::area() const noexcept(true) 
{
    return this->side * this->side;
}

double Square::perimeter() const noexcept(true)
{
    return 4 * this->side;
}

const std::string Square::name() const noexcept(true) 
{
    return "Square";
}
