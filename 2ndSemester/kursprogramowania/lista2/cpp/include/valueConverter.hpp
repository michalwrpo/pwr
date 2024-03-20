#ifndef VALUE_CONVERTER_HPP
#define VALUE_CONVERTER_HPP

#include <string>
#include <sstream>
#include <stdexcept>

/**
 * @class ValueConverter by Kukos
 * 
 * @brief ValueConverter is a static class used to convert string to primitive types like int, unsigned, long, double ...
 * 
 */
class ValueConverter
{
public:
    // class is full static so delete constructor
    ValueConverter() = delete;
    ~ValueConverter() = delete;

    /**
     * @brief funciton is converting the string to the value of type T
     *        If the conversion cannot be done, the std::invalid_argument is raised
     * 
     * @tparam T - type of value to be converted from string
     * @param str - string with value to convert
     * @return converted value from string to type T
     */
    template <typename T>
    static T stringToVal(const std::string& str) noexcept(false)
    {
        T val = {};
        char c = {};

        std::stringstream ss(str);
        ss >> val;

        if (ss.fail() || ss.get(c))
        {
            throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "Cannot convert: " + str + " to a desired type.");
        }

        return val;
    }
};

#endif
