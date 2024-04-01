#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <quadrilateral.hpp>

/**
 * @class Square
 *
 * @brief Class representing a square, having methods to calculate its area and perimeter
 * 
 */
class Square: public Quadrilateral
{
private:
    double side;

public:
    Square(double side) noexcept(false);
    
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const std::string name() const noexcept(true) override;
};

#endif
