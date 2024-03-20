#include <iostream>

#include <valueConverter.hpp>
#include <pascalsTriangleRow.hpp>

int main(const int argc, const char* const argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <arg1> <arg2> ..." << std::endl;
        return 1; 
    }

    PascalsTriangleRow* p;

    try
    {
        const int rowNumber = ValueConverter::stringToVal<int>(std::string(argv[1]));
        p = new PascalsTriangleRow(rowNumber);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
        return 2;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "Out of Range Error: " << e.what() << std::endl;
        return 3;
    }
    

    for (size_t i = 2; i < static_cast<size_t>(argc); i++)
    {
        try
        {
            const int argNumber = ValueConverter::stringToVal<int>(std::string(argv[i]));
            const int nChooseM = p->mthElement(argNumber);

            std::cout << std::to_string(argNumber) << " -> " << std::to_string(nChooseM) << std::endl;
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << argv[i] << " -> Invalid Argument Error: " << e.what() << std::endl;
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << argv[i] << " -> Out of Range Error: " << e.what() << std::endl;
        }
        
    }

    return 0;
}