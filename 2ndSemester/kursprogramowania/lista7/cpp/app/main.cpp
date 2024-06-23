#include <iostream>

#include <CLI.hpp>

/**
 * @brief main method used to start the whole program
 */
int main()
{
    std::cout << "Which type of tree do you want to create?" << std::endl;
    std::cout << "[i]nterger, [d]ouble, [s]tring" << std::endl;

    char treeType;
    std::cin >> treeType;

    switch (treeType)
    {
    case 'i':
    {
        CLI<int> intCLI;
        intCLI.start();
        break;
    }
    case 'd':
    {
        CLI<double> doubleCLI;
        doubleCLI.start();
        break;
    }
    case 's':
    {
        CLI<std::string> stringCLI;
        stringCLI.start();
        break;
    }
    default:
        std::cout << "Invalid type" << std::endl;
        break;
    }

    return 0;
}