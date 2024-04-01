#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <figure.hpp>

/**
 * @class Circle
 *
 * @brief Class representing a circle, having methods to calculate its area and perimeter
 * 
 */
class Circle: public Figure
{
private:
    double radius;

public:
    Circle(double radius) noexcept(false);
    
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const std::string name() const noexcept(true) override;
};

#endif
