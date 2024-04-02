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
        Pentagon testPenta = Pentagon(1);
        assert(std::fabs(testPenta.area() - 1.7204774005) < 0.00001);
        assert(std::fabs(testPenta.perimeter() - 5) < 0.00001);
        assert(testPenta.name().compare("Pentagon") == 0);
    }
    {
        Pentagon testPenta = Pentagon(5);
        assert(std::fabs(testPenta.area() - 25 * 1.7204774005) < 0.00001);
        assert(std::fabs(testPenta.perimeter() - 25) < 0.00001);
        assert(testPenta.name().compare("Pentagon") == 0);
    }
    {
        Pentagon testPenta = Pentagon(0.05);
        assert(std::fabs(testPenta.area() - 0.0025 * 1.7204774005) < 0.00001);
        assert(std::fabs(testPenta.perimeter() - 0.25) < 0.00001);
        assert(testPenta.name().compare("Pentagon") == 0);
    }
    {
        Pentagon testPenta = Pentagon(1.23);
        assert(std::fabs(testPenta.area() - 1.5129 * 1.7204774005) < 0.00001);
        assert(std::fabs(testPenta.perimeter() - 6.15) < 0.00001);
        assert(testPenta.name().compare("Pentagon") == 0);
    }
}

void testPentagon() noexcept(true)
{
    testPentagonConstructor();
}