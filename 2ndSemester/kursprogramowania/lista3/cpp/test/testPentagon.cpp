#include <stdexcept>
#include <cassert>
#include <cmath>

#include <pentagon.hpp>

void testPentagon() noexcept(true);
static void testPentagonConstructorExceptions(double side) noexcept(true);
static void testPentagonConstructor() noexcept(true);

static void testPentagonConstructorExceptions(double side) noexcept(true)
{
    try
    {
        const auto val = Pentagon(side);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
}

static void testPentagonConstructor() noexcept(true)
{
    {
        testPentagonConstructorExceptions(-100);
        testPentagonConstructorExceptions(-1);
        testPentagonConstructorExceptions(0);
        testPentagonConstructorExceptions(-12345678);
    }
    {
        Pentagon testCirc = Pentagon(1);
        assert(std::fabs(testCirc.area() - 1.7204774005) < 0.00001);
        assert(std::fabs(testCirc.perimeter() - 5) < 0.00001);
        assert(testCirc.name().compare("Pentagon") == 0);
    }
    {
        Pentagon testCirc = Pentagon(5);
        assert(std::fabs(testCirc.area() - 25 * 1.7204774005) < 0.00001);
        assert(std::fabs(testCirc.perimeter() - 25) < 0.00001);
        assert(testCirc.name().compare("Pentagon") == 0);
    }
    {
        Pentagon testCirc = Pentagon(0.05);
        assert(std::fabs(testCirc.area() - 0.0025 * 1.7204774005) < 0.00001);
        assert(std::fabs(testCirc.perimeter() - 0.25) < 0.00001);
        assert(testCirc.name().compare("Pentagon") == 0);
    }
    {
        Pentagon testCirc = Pentagon(1.23);
        assert(std::fabs(testCirc.area() - 1.5129 * 1.7204774005) < 0.00001);
        assert(std::fabs(testCirc.perimeter() - 6.15) < 0.00001);
        assert(testCirc.name().compare("Pentagon") == 0);
    }
}

void testPentagon() noexcept(true)
{
    testPentagonConstructor();
}