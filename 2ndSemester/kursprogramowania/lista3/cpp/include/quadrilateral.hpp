#ifndef QUADRILATERAL_HPP
#define QUADRILATERAL_HPP

#include <stdexcept>

#include <figure.hpp>

/**
 * @class Quadrilateral
 * 
 * @brief Abstract class representing a quadrilateral 
 */
class Quadrilateral : public Figure
{
public:
    virtual ~Quadrilateral() override {}
};

#endif
