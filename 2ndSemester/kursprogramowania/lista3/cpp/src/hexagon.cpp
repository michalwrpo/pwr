#include <hexagon.hpp>

#include <cmath>
#include <string>

Hexagon::Hexagon(double side) noexcept(false)
{
    if (side <= 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "side should be positive, got " + std::to_string(side));

    this->side = side;
}

double Hexagon::area() const noexcept(true) 
{
    return 2.5980762113 * this->side * this->side;
}

double Hexagon::perimeter() const noexcept(true)
{
    return 6 * this->side;
}

const std::string Hexagon::name() const noexcept(true) 
{
    return "Hexagon";
}
