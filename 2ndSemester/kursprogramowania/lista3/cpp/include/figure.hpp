#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <stdexcept>

/**
 * @class Figure 
 * 
 * @brief Abstract class representing a geometeric figure  
 */
class Figure
{
public:
    /**
     * @brief method for calculating area of the figure
     * 
     * @return double 
     */
    virtual double area() const noexcept(false) = 0;
    /**
     * @brief method for calculating perimeter of the figure
     * 
     * @return double 
     */
    virtual double perimeter() const noexcept(false) = 0;
    /**
     * @brief method returning name of the figure
     * 
     * @return const std::string 
     */
    virtual const std::string name() const noexcept(true) = 0;
    virtual ~Figure() {}
};

#endif
