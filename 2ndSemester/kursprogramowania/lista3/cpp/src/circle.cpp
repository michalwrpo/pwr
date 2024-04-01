#include <circle.hpp>

#include <cmath>
#include <string>

Circle::Circle(double radius) noexcept(false)
{
    if (radius <= 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "radius should be positive, got " + std::to_string(radius));

    this->radius = radius;
}

double Circle::area() const noexcept(true) 
{
    return M_PI * this->radius * this->radius;
}

double Circle::perimeter() const noexcept(true)
{
    return 2 * M_PI * this->radius;
}

const std::string Circle::name() const noexcept(true) 
{
    return "Circle";
}
