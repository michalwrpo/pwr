#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <figure.hpp>

/**
 * @class Hexagon
 *
 * @brief Class representing a hexagon, having methods to calculate its area and perimeter
 * 
 */
class Hexagon: public Figure
{
private:
    double side;

public:
    Hexagon(double side) noexcept(false);
    
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const std::string name() const noexcept(true) override;
};

#endif
