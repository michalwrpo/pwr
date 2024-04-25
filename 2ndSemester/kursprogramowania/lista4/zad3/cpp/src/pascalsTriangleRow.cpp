#include <pascalsTriangleRow.hpp>

#include <stdexcept>

std::vector<int> PascalsTriangleRow::pascalsRow(const int n) noexcept(false)
{
    if (n < 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter n should be nonnegative, got " + std::to_string(n));

    if (n > 33)
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter n should be smaller than 34, got " + std::to_string(n));

    std::vector<int> nthRow{1};

    for (int i = 0; i < n; i++)
    {
        nthRow.push_back(static_cast<int>(static_cast<long>(nthRow[static_cast<size_t>(i)])*static_cast<long>(n-i)/static_cast<long>(i+1)));
    }
    return nthRow;
}

PascalsTriangleRow::PascalsTriangleRow(const int n) noexcept(false)
{
    if (n < 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter n should be nonnegative, got " + std::to_string(n));

    if (n > 33)
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter n should be smaller than 34, got " + std::to_string(n));

    row = PascalsTriangleRow::pascalsRow(n);
}

int PascalsTriangleRow::mthElement(const int m) noexcept(false)
{
    if (m < 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter m should be nonnegative, got " + std::to_string(m));

    int n = static_cast<int>(this->row.size()) - 1;

    if (m > n)
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter m should be smaller or equal to n (" + std::to_string(n) + "), got " + std::to_string(m));
        
    return this->row[static_cast<size_t>(m)];
}
