#include <valueConverter.hpp>

#include <cassert>
#include <stdexcept>
#include <cmath>

void testValueConverter() noexcept(true);
static void testValueConverterNormalCases() noexcept(true);

template <typename T>
static void testValueConverterExceptions(const std::string str) noexcept(true)
{
    try
    {
        const T val = ValueConverter::stringToVal<T>(str);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;

        assert(true);
    }
    
}

static void testValueConverterNormalCases() noexcept(true)
{
    assert(ValueConverter::stringToVal<int>("123") == 123);
    assert(ValueConverter::stringToVal<int>("0") == 0);
    assert(ValueConverter::stringToVal<int>("-1") == -1);
    assert(ValueConverter::stringToVal<int>("12345678") == 12345678);

    assert(ValueConverter::stringToVal<unsigned long>("123") == 123UL);
    assert(ValueConverter::stringToVal<unsigned long>("0") == 0UL);
    assert(ValueConverter::stringToVal<unsigned long>("-123") == static_cast<unsigned long>(-123));
    assert(ValueConverter::stringToVal<unsigned long>("1234567890") == 1234567890UL);

    assert(std::fabs(ValueConverter::stringToVal<double>("123.45") - 123.45) < 0.00001);
    assert(std::fabs(ValueConverter::stringToVal<double>("0") - 0.0) < 0.00001);
    assert(std::fabs(ValueConverter::stringToVal<double>("0.14") - 0.14) < 0.00001);
    assert(std::fabs(ValueConverter::stringToVal<double>("-2.71") - -2.71) < 0.00001);
    assert(std::fabs(ValueConverter::stringToVal<double>("123456.789") - 123456.789) < 0.00001);
}

void testValueConverter() noexcept(true)
{
    testValueConverterNormalCases();

    testValueConverterExceptions<unsigned int>(std::string("ala"));
    testValueConverterExceptions<unsigned int>(std::string("Ala ma kota"));
    testValueConverterExceptions<unsigned int>(std::string("1al.a"));
    testValueConverterExceptions<unsigned int>(std::string("1a123"));

    testValueConverterExceptions<long>(std::string("ala"));
    testValueConverterExceptions<long>(std::string("a1"));
    testValueConverterExceptions<long>(std::string("1a1lasadfghjkhgfdsafsjhfdfsdafjhgjfjfkfjkfkfjjf"));
    testValueConverterExceptions<long>(std::string("1ala12321"));

    testValueConverterExceptions<double>(std::string("ala"));
    testValueConverterExceptions<double>(std::string("a.10"));
    testValueConverterExceptions<double>(std::string("a1.0"));
    testValueConverterExceptions<double>(std::string("1.ala1"));
}

