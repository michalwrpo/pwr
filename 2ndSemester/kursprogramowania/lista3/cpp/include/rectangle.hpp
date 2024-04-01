#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <quadrilateral.hpp>

/**
 * @class Rectangle
 *
 * @brief Class representing a rectangle, having methods to calculate its area and perimeter
 * 
 */
class Rectangle: public Quadrilateral
{
private:
    double side1;
    double side2;

public:
    Rectangle(double side1, double side2) noexcept(false);
    
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const std::string name() const noexcept(true) override;
};

#endif
