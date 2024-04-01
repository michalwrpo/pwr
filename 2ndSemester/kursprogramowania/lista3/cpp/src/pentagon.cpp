#include <pentagon.hpp>

#include <cmath>
#include <string>

Pentagon::Pentagon(double side) noexcept(false)
{
    if (side <= 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "side length should be positive, got " + std::to_string(side));

    this->side = side;
}

double Pentagon::area() const noexcept(true) 
{
    return 1.7204774005 * this->side * this->side;
}

double Pentagon::perimeter() const noexcept(true)
{
    return 5 * this->side;
}

const std::string Pentagon::name() const noexcept(true) 
{
    return "Pentagon";
}
