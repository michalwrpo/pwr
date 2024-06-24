#ifndef CLI_HPP
#define CLI_HPP

#include <sstream>
#include <string>
#include <iostream>

#include <BST.hpp>
#include <valueConverter.hpp>

/**
 * @brief CLI (Command Line Interface) for the BST responsible for interacting with it through the command line
 * 
 * <T> type of elements inside the BST
 */
template <typename T>
class CLI
{
    private:
        BST<T>* tree;
        
    public:
        CLI() noexcept(true) 
        {
            tree = new BST<T>();
        }

        ~CLI()
        {
            delete tree;
        }

        /**
         * Starts the CLI interacting with tree
         * List of valid commands
         * - p - prints the tree
         * - i / a [value] - inserts value into the tree
         * - r / d [value] - removes value from the tree
         * - s / f [value] - finds if value is in the tree
         * - q - quits from CLI
         * CLI will continue running until the user chooses to quit
         */
        void start() noexcept(true)
        {
            bool quit = false;

            std::string command = "";
            std::cin.ignore();

            while (!quit)
            {
                std::cout << "Enter a command: ";
                std::getline(std::cin, command);

                if (command == "p")
                {
                    std::cout << tree->print();
                    continue;
                }

                if (command == "q")
                {
                    std::cout << "Quiting..." << std::endl;
                    quit = true;
                    continue;
                }

                std::istringstream iss(command);
                std::string operation;
                std::string strValue;

                if (!(iss >> operation >> strValue))
                {
                    std::cout << "Invalid command" << std::endl;
                    continue;
                }
                try
                {
                    T value = ValueConverter::stringToVal<T>(strValue);

                    switch (ValueConverter::stringToVal<char>(operation))
                    {
                    case 'i':
                    case 'a':
                        std::cout << "Inserting " << strValue << " into the tree" << std::endl;
                        tree->insert(value);
                        break;
                    case 'r':
                    case 'd':
                        std::cout << "Deleting " << strValue << " from the tree" << std::endl;
                        tree->remove(value);
                        break;
                    case 's':
                    case 'f':
                        std::cout << strValue << (tree->search(value) ? " is" : " is not") << " in the tree" << std::endl;
                        break;
                    default:
                        std::cout << "Invalid command" << std::endl;
                        break;
                    }   
                }
                catch(const std::invalid_argument& e)
                {
                    (void)e;
                    std::cout << "Invalid command" << std::endl;
                }
                
            }  

            tree->deleteTree();
        }

};

#endif
