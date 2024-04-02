#include <stdexcept>
#include <cassert>
#include <cmath>

#include <hexagon.hpp>

void testHexagon() noexcept(true);
static void testHexagonConstructorExceptions(double side) noexcept(true);
static void testHexagonConstructor() noexcept(true);

static void testHexagonConstructorExceptions(double side) noexcept(true)
{
    try
    {
        const auto val = Hexagon(side);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
}

static void testHexagonConstructor() noexcept(true)
{
    {
        testHexagonConstructorExceptions(-100);
        testHexagonConstructorExceptions(-1);
        testHexagonConstructorExceptions(0);
        testHexagonConstructorExceptions(-12345678);
    }
    {
        Hexagon testHex = Hexagon(1);
        assert(std::fabs(testHex.area() - 2.5980762113) < 0.00001);
        assert(std::fabs(testHex.perimeter() - 6) < 0.00001);
        assert(testHex.name().compare("Hexagon") == 0);
    }
    {
        Hexagon testHex = Hexagon(5);
        assert(std::fabs(testHex.area() - 25 * 2.5980762113) < 0.00001);
        assert(std::fabs(testHex.perimeter() - 30) < 0.00001);
        assert(testHex.name().compare("Hexagon") == 0);
    }
    {
        Hexagon testHex = Hexagon(0.05);
        assert(std::fabs(testHex.area() - 0.0025 * 2.5980762113) < 0.00001);
        assert(std::fabs(testHex.perimeter() - 0.30) < 0.00001);
        assert(testHex.name().compare("Hexagon") == 0);
    }
    {
        Hexagon testHex = Hexagon(123);
        assert(std::fabs(testHex.area() - 15129 * 2.5980762113) < 0.00001);
        assert(std::fabs(testHex.perimeter() - 738) < 0.00001);
        assert(testHex.name().compare("Hexagon") == 0);
    }
}

void testHexagon() noexcept(true)
{
    testHexagonConstructor();
}