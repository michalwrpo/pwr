#include <rectangle.hpp>

#include <cmath>
#include <string>

Rectangle::Rectangle(double side1, double side2) noexcept(false)
{
    if (side1 <= 0 || side2 <= 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "side lengths should be positive, got " + std::to_string(side1) + " and " + std::to_string(side2));

    this->side1 = side1;
    this->side2 = side2;
}

double Rectangle::area() const noexcept(true) 
{
    return this->side1 * this->side2;
}

double Rectangle::perimeter() const noexcept(true)
{
    return 2 * this->side1 + 2 * this->side2;
}

const std::string Rectangle::name() const noexcept(true) 
{
    return "Rectangle";
}
