#include <rhombus.hpp>

#include <cmath>
#include <string>

Rhombus::Rhombus(double side, double angle) noexcept(false)
{
    if (side <= 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "side length should be positive, got " + std::to_string(side));

    if (angle <= 0 || angle >= 180)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "angle should be between 0 and 180 degrees, got " + std::to_string(angle));

    this->side = side;
    this->angle = angle;
}

double Rhombus::area() const noexcept(true) 
{
    return this->side * this->side * std::sin(angle * M_PI/180) ;
}

double Rhombus::perimeter() const noexcept(true)
{
    return 4 * this->side;
}

const std::string Rhombus::name() const noexcept(true) 
{
    return "Rhombus";
}
