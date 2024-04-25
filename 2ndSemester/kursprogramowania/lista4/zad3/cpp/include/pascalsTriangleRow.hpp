#ifndef PASCALS_TRIANGLE_ROW_HPP
#define PASCALS_TRIANGLE_ROW_HPP

#include <vector>

/**
 *@class PascalsTriangleRow 
 * 
 *@brief class containing methods to create nth row of Pascal's triangle
 * 
 */
class PascalsTriangleRow 
{
private:
    std::vector<int> row;
public:    
    PascalsTriangleRow() = delete;

    PascalsTriangleRow(int n) noexcept(false);

    /**
     * @brief returns full nth row of Pascal's Triangle
     * 
     * @param n - should be nonnegative and smaller than 34
     * @return std::vector<int> of all binomials n over something
     */
    static std::vector<int> pascalsRow(int n) noexcept(false);

    /**
     * @brief returns n over m
     * 
     * @param m - should be nonnegative and smaller than n
     * @return int 
     */
    int mthElement(int m) noexcept(false);
};

#endif
