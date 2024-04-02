#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include <figure.hpp>

/**
 * @class Pentagon
 *
 * @brief Class representing a pentagon, having methods to calculate its area and perimeter
 * 
 */
class Pentagon: public Figure
{
private:
    double side;

public:
    Pentagon(double side) noexcept(false);
    
    double area() const noexcept(true) override;
    double perimeter() const noexcept(true) override;
    const std::string name() const noexcept(true) override;
};

#endif
