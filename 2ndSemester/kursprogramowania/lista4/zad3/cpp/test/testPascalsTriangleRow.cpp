#include <pascalsTriangleRow.hpp>

#include <cassert>
#include <stdexcept>

void testPascalsTriangleRow() noexcept(true);
static void testPascalsRowExceptions(const int n) noexcept(true);
static void testPascalsRow() noexcept(true);
static void testPascalsTriangleRowExceptions(const int n) noexcept(true);
static void testMthElementExceptions(const int n, PascalsTriangleRow prow) noexcept(true);
static void testPascalsTriangleRowGenerator() noexcept(true);

static void testPascalsRowExceptions(const int n) noexcept(true)
{
    try
    {
        const auto val = PascalsTriangleRow::pascalsRow(n);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
    catch(const std::out_of_range& e)
    {
        (void)e;
        assert(true);
    }
}

static void testPascalsRow() noexcept(true)
{
    testPascalsRowExceptions(-1);
    testPascalsRowExceptions(34);
    testPascalsRowExceptions(1000);
    testPascalsRowExceptions(-123);

    assert(PascalsTriangleRow::pascalsRow(1)[0] == 1);
    assert(PascalsTriangleRow::pascalsRow(1)[1] == 1);
    assert(PascalsTriangleRow::pascalsRow(2)[1] == 2);
    assert(PascalsTriangleRow::pascalsRow(4)[2] == 6);

    assert(PascalsTriangleRow::pascalsRow(20)[20] == 1);
    assert(PascalsTriangleRow::pascalsRow(20)[19] == 20);
    assert(PascalsTriangleRow::pascalsRow(20)[18] == 190);
    assert(PascalsTriangleRow::pascalsRow(20)[2] == 190);
}


static void testPascalsTriangleRowExceptions(const int n) noexcept(true)
{
    try
    {
        const auto val = PascalsTriangleRow(n);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
    catch(const std::out_of_range& e)
    {
        (void)e;
        assert(true);
    }
}
static void testMthElementExceptions(const int n, PascalsTriangleRow prow) noexcept(true)
{
    try
    {
        const auto val = prow.mthElement(n);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
    catch(const std::out_of_range& e)
    {
        (void)e;
        assert(true);
    }
}


static void testPascalsTriangleRowGenerator() noexcept(true)
{
    {
        testPascalsTriangleRowExceptions(-1);
        testPascalsTriangleRowExceptions(35);
        testPascalsTriangleRowExceptions(100000);
        testPascalsTriangleRowExceptions(-123);
    }
    {
        PascalsTriangleRow ptest = PascalsTriangleRow(2);
        testMthElementExceptions(-1, ptest);
        testMthElementExceptions(-123, ptest);
        testMthElementExceptions(3, ptest);
        testMthElementExceptions(12345678, ptest);
    }
    {
        PascalsTriangleRow ptest = PascalsTriangleRow(10);
        testMthElementExceptions(11, ptest);
        assert(ptest.mthElement(0) == 1);
        assert(ptest.mthElement(1) == 10);
        assert(ptest.mthElement(3) == 120);
    }
    {
        PascalsTriangleRow ptest = PascalsTriangleRow(33);
        assert(ptest.mthElement(33) == 1);
        assert(ptest.mthElement(32) == 33);
        assert(ptest.mthElement(16) == 1166803110);
        assert(ptest.mthElement(0) == 1);
    }
}


void testPascalsTriangleRow() noexcept(true)
{
    testPascalsTriangleRowGenerator();
    testPascalsRow();
}

