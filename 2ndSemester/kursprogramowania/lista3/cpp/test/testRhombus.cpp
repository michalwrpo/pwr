#include <stdexcept>
#include <cassert>
#include <cmath>

#include <rhombus.hpp>

void testRhombus() noexcept(true);
static void testRhombusConstructorExceptions(double side, double angle) noexcept(true);
static void testRhombusConstructor() noexcept(true);

static void testRhombusConstructorExceptions(double side, double angle) noexcept(true)
{
    try
    {
        const auto val = Rhombus(side, angle);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
}

static void testRhombusConstructor() noexcept(true)
{
    {
        testRhombusConstructorExceptions(-100, 100);
        testRhombusConstructorExceptions(123, -123);
        testRhombusConstructorExceptions(-1, -1);
        testRhombusConstructorExceptions(0, 1);
        testRhombusConstructorExceptions(100, 0);
        testRhombusConstructorExceptions(12345678, 12345678);

    }
    {
        Rhombus testRho = Rhombus(1, 90);
        assert(std::fabs(testRho.area() - 1) < 0.00001);
        assert(std::fabs(testRho.perimeter() - 4) < 0.00001);
        assert(testRho.name().compare("Rhombus") == 0);
    }
    {
        Rhombus testRho = Rhombus(5, 30);
        assert(std::fabs(testRho.area() - 12.5) < 0.00001);
        assert(std::fabs(testRho.perimeter() - 20) < 0.00001);
        assert(testRho.name().compare("Rhombus") == 0);
    }
    {
        Rhombus testRho = Rhombus(0.05, 60);
        assert(std::fabs(testRho.area() - 0.00216506) < 0.00001);
        assert(std::fabs(testRho.perimeter() - 0.2) < 0.00001);
        assert(testRho.name().compare("Rhombus") == 0);
    }
    {
        Rhombus testRho = Rhombus(1.23, 22);
        assert(std::fabs(testRho.area() - 0.566742) < 0.00001);
        assert(std::fabs(testRho.perimeter() - 4.92) < 0.00001);
        assert(testRho.name().compare("Rhombus") == 0);
    }
}

void testRhombus() noexcept(true)
{
    testRhombusConstructor();
}