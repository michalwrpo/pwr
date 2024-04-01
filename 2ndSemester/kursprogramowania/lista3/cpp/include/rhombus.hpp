#ifndef RHOMBUS_HPP
#define RHOMBUS_HPP

#include <quadrilateral.hpp>

/**
 * @class Rhombus
 *
 * @brief Class representing a rhombus, having methods to calculate its area and perimeter
 * 
 */
class Rhombus: public Quadrilateral
{
private:
    double side;
    double angle;

public:
    Rhombus(double side, double angle) noexcept(false);
    
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const std::string name() const noexcept(true) override;
};

#endif
