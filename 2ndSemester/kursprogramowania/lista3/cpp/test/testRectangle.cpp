#include <stdexcept>
#include <cassert>
#include <cmath>

#include <rectangle.hpp>

void testRectangle() noexcept(true);
static void testRectangleConstructorExceptions(double side1, double side2) noexcept(true);
static void testRectangleConstructor() noexcept(true);

static void testRectangleConstructorExceptions(double side1, double side2) noexcept(true)
{
    try
    {
        const auto val = Rectangle(side1, side2);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
}

static void testRectangleConstructor() noexcept(true)
{
    {
        testRectangleConstructorExceptions(-100, 100);
        testRectangleConstructorExceptions(123, -123);
        testRectangleConstructorExceptions(-1, -1);
        testRectangleConstructorExceptions(0, 1);
        testRectangleConstructorExceptions(100, 0);
        testRectangleConstructorExceptions(-12345678, -12345678);

    }
    {
        Rectangle testRect = Rectangle(1, 1);
        assert(std::fabs(testRect.area() - 1) < 0.00001);
        assert(std::fabs(testRect.perimeter() - 4) < 0.00001);
        assert(testRect.name().compare("Rectangle") == 0);
    }
    {
        Rectangle testRect = Rectangle(5, 4);
        assert(std::fabs(testRect.area() - 20) < 0.00001);
        assert(std::fabs(testRect.perimeter() - 18) < 0.00001);
        assert(testRect.name().compare("Rectangle") == 0);
    }
    {
        Rectangle testRect = Rectangle(0.05, 0.2);
        assert(std::fabs(testRect.area() - 0.01) < 0.00001);
        assert(std::fabs(testRect.perimeter() - 0.5) < 0.00001);
        assert(testRect.name().compare("Rectangle") == 0);
    }
    {
        Rectangle testRect = Rectangle(240, 0.13);
        assert(std::fabs(testRect.area() - 31.2) < 0.00001);
        assert(std::fabs(testRect.perimeter() - 480.26) < 0.00001);
        assert(testRect.name().compare("Rectangle") == 0);
    }
}

void testRectangle() noexcept(true)
{
    testRectangleConstructor();
}