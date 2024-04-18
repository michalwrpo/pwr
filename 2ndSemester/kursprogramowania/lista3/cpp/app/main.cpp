#include <iostream>

#include <valueConverter.hpp>

#include <circle.hpp>
#include <square.hpp>
#include <rectangle.hpp>
#include <rhombus.hpp>
#include <pentagon.hpp>
#include <hexagon.hpp>

int main(const int argc, const char* const argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <arg1> <arg2> ..." << std::endl;
        return 1;
    } else if (argc != 3 && argc != 7)
    {
        std::cerr << "Arguments should be a char and 1 or 5 doubles" << std::endl;
        return 2;
    }
    
    Figure* f = nullptr;

    if (argc == 3)
    {   
        try
        {
            const double side = ValueConverter::stringToVal<double>(std::string(argv[2]));

            if (side <= 0)
            {
                std::cerr << "Invalid Argument Error: Double argument should be greater than 0" << std::endl;
                return 4;
            }

            if (*argv[1] == 'o')
            {
                f = new Circle(side);
            } else if (*argv[1] == 'p')
            {
                f = new Pentagon(side);
            } else if (*argv[1] == 's')
            {
                f = new Hexagon(side);
            } else
            {
                std::cerr << "Invalid Argument Error: When given 2 arguments, the former should be 'o', 'p' or 's'" << std::endl;
                return 6;
            }
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 3;
        }
    }
    else if (argc == 7)
    {
        try
        {
            const double side1 = ValueConverter::stringToVal<double>(std::string(argv[2]));
            const double side2 = ValueConverter::stringToVal<double>(std::string(argv[3]));
            const double side3 = ValueConverter::stringToVal<double>(std::string(argv[4]));
            const double side4 = ValueConverter::stringToVal<double>(std::string(argv[5]));
            const double angle = ValueConverter::stringToVal<double>(std::string(argv[6]));

            if (side1 <= 0 || side2 <= 0 || side3 <= 0 || side4 <= 0 || angle <= 0)
            {
                std::cerr << "Invalid Argument Error: Double argument should be greater than 0" << std::endl;
                return 4;
            } else if (angle >= 180)
            {
                std::cerr << "Invalid Argument Error: Last double argument should be smaller than 180" << std::endl;
                return 5;
            }
            
            if (*argv[1] != 'c')
            {
                std::cerr << "Invalid Argument Error: When given 5 arguments, the first should be 'c'" << std::endl;
                return 6;
            }

            if (angle != 90)
            {
                if (side1 == side2 && side2 == side3 && side3 == side4)
                {
                    f = new Rhombus(side1, angle);
                } else
                {
                    std::cerr << "Invalid Argument Error: Side lengths should be equal or angle 90 degrees" << std::endl;
                    return 8;
                }
            }
            else
            {
                if (side1 == side2 && side2 == side3 && side3 == side4)
                {
                    f = new Square(side1);
                } else if (side1 == side2 && side3 == side4)
                {
                    f = new Rectangle(side1, side3);
                } else if ((side1 == side3 && side2 == side4) || (side1 == side4 && side2 == side3))
                {
                    f = new Rectangle(side1, side2);
                } else
                {
                    std::cerr << "Invalid Argument Error: There should be at least 2 pairs of equal side lengths" << std::endl;
                    return 8;
                }
            }
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << "Invalid Argument Error: " << e.what() << std::endl;
            return 3;
        }
    }
    
    std::cout << f->name() << std::endl; 
    std::cout << "Area: " << f->area() << std::endl; 
    std::cout << "Perimeter: " << f->perimeter() << std::endl; 
    
    delete f;

    return 0;
}
