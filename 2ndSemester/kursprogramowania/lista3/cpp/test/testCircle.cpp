#include <stdexcept>
#include <cassert>
#include <cmath>

#include <circle.hpp>

void testCircle() noexcept(true);
static void testCircleConstructorExceptions(double radius) noexcept(true);
static void testCircleConstructor() noexcept(true);

static void testCircleConstructorExceptions(double radius) noexcept(true)
{
    try
    {
        const auto val = Circle(radius);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
}

static void testCircleConstructor() noexcept(true)
{
    {
        testCircleConstructorExceptions(-100);
        testCircleConstructorExceptions(-1);
        testCircleConstructorExceptions(0);
        testCircleConstructorExceptions(-12345678);
    }
    {
        Circle testCirc = Circle(1);
        assert(std::fabs(testCirc.area() - 3.1415926535) < 0.00001);
        assert(std::fabs(testCirc.perimeter() - 6.2831853071) < 0.00001);
        assert(testCirc.name().compare("Circle") == 0);
    }
    {
        Circle testCirc = Circle(5);
        assert(std::fabs(testCirc.area() - 25 * 3.1415926535) < 0.00001);
        assert(std::fabs(testCirc.perimeter() - 5 * 6.2831853071) < 0.00001);
        assert(testCirc.name().compare("Circle") == 0);
    }
    {
        Circle testCirc = Circle(0.05);
        assert(std::fabs(testCirc.area() - 0.0025 * 3.1415926535) < 0.00001);
        assert(std::fabs(testCirc.perimeter() - 0.05 * 6.2831853071) < 0.00001);
        assert(testCirc.name().compare("Circle") == 0);
    }
    {
        Circle testCirc = Circle(123);
        assert(std::fabs(testCirc.area() - 15129 * 3.1415926535) < 0.00001);
        assert(std::fabs(testCirc.perimeter() - 123 * 6.2831853071) < 0.00001);
        assert(testCirc.name().compare("Circle") == 0);
    }
}

void testCircle() noexcept(true)
{
    testCircleConstructor();
}