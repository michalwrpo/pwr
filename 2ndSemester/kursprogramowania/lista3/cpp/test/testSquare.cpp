#include <stdexcept>
#include <cassert>
#include <cmath>

#include <square.hpp>

void testSquare() noexcept(true);
static void testSquareConstructorExceptions(double side) noexcept(true);
static void testSquareConstructor() noexcept(true);

static void testSquareConstructorExceptions(double side) noexcept(true)
{
    try
    {
        const auto val = Square(side);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
}

static void testSquareConstructor() noexcept(true)
{
    {
        testSquareConstructorExceptions(-100);
        testSquareConstructorExceptions(-1);
        testSquareConstructorExceptions(0);
        testSquareConstructorExceptions(-12345678);
    }
    {
        Square testSqr = Square(1);
        assert(std::fabs(testSqr.area() - 1) < 0.00001);
        assert(std::fabs(testSqr.perimeter() - 4) < 0.00001);
        assert(testSqr.name().compare("Square") == 0);
    }
    {
        Square testSqr = Square(5);
        assert(std::fabs(testSqr.area() - 25) < 0.00001);
        assert(std::fabs(testSqr.perimeter() - 20) < 0.00001);
        assert(testSqr.name().compare("Square") == 0);
    }
    {
        Square testSqr = Square(0.05);
        assert(std::fabs(testSqr.area() - 0.0025) < 0.00001);
        assert(std::fabs(testSqr.perimeter() - 0.2) < 0.00001);
        assert(testSqr.name().compare("Square") == 0);
    }
    {
        Square testSqr = Square(123);
        assert(std::fabs(testSqr.area() - 15129) < 0.00001);
        assert(std::fabs(testSqr.perimeter() - 492) < 0.00001);
        assert(testSqr.name().compare("Square") == 0);
    }
}

void testSquare() noexcept(true)
{
    testSquareConstructor();
}