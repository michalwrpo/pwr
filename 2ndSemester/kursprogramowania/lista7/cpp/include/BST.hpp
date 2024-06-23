#ifndef BST_HPP
#define BST_HPP

#include <string>
#include <sstream>

/**
 * @brief class representing BST (Binary Search Tree) and contatining methods related to it
 */
template <typename T>
class BST
{
    protected:
        template <typename T1>
        class Node
        {
            public:
                T1 value;

                Node<T1>* left;
                Node<T1>* right;

                Node(T1 value) noexcept(true) 
                {
                    this->value = value;
                    this->left = nullptr;
                    this->right = nullptr;
                }
        };

    private:
        Node<T>* root;

        void treeInsert(Node<T>* node, T value) noexcept(true)
        {
            if (value < node->value)
            {
                if (node->left == nullptr)
                    node->left = new Node<T>(value);
                else
                    treeInsert(node->left, value);
            }
            else
            {
                if (node->right == nullptr)
                    node->right = new Node<T>(value);
                else
                    treeInsert(node->right, value);
            }
        }

        Node<T>* deleteNode(Node<T>* node, T value) noexcept(true)
        {
            if (node == nullptr)
                return nullptr;
            
            if (value < node->value)
                node->left = deleteNode(node->left, value);
            else if (value > node->value)
                node->right = deleteNode(node->right, value);
            else
            {
                if (node->left == nullptr)
                {
                    Node<T> *temp = node;
                    node = node->right;
                    delete temp;
                }
                else if (node->right == nullptr)
                {
                    Node<T> *temp = node;
                    node = node->left;
                    delete temp;
                }
                else
                {
                    Node<T>* temp = node->right;
                    Node<T>* tempParent = node;
                    while (temp->left != nullptr)
                    {
                        tempParent = temp;
                        temp = temp->left;
                    }
                    node->value = temp->value;

                    if (tempParent->left == temp)
                        tempParent->left = temp->right;
                    else
                        tempParent->right = temp->right;
                    
                    delete temp;
                }
            }
            
            return node;
        }

        bool treeSearch(Node<T>* node, T value) noexcept(true)
        {
            if (node == nullptr)
                return false;

            if (value < node->value)
                return treeSearch(node->left, value);
            else if (value > node->value)
                return treeSearch(node->right, value);

            return true;
        }

        std::string treePrint(Node<T>* node, int depth) noexcept(true)
        {
            std::stringstream ss;

            if (node != nullptr)
            {
            ss << treePrint(node->right, depth + 1);
            for (int i = 0; i < depth; i++)
            {
                ss << "   ";
            }
            ss << node->value << "\n";
            ss << treePrint(node->left, depth + 1);
            }
            
            return ss.str();
        }

    public:
        BST() noexcept(true)
        {
            this->root = nullptr;
        }

        /**
         * @brief inserts a value into the BST
         * 
         * @param value to be inserted
         */
        void insert(T value) noexcept(true)
        {
            if (root == nullptr)
                root = new Node<T>(value);
            else
                treeInsert(root, value);
        }

        /**
         * @brief deletes a value from the BST
         * 
         * @param value to be deleted
         */
        void remove(T value) noexcept(true)
        {
            deleteNode(root, value);
        }

        /**
         * @brief searches the BST for the given value
         * 
         * @param value to be found
         * @return true - if value is in BST, false - otherwise
         */
        bool search(T value) noexcept(true)
        {
            return treeSearch(root, value);
        }

        /**
         * @brief turns the tree into a String
         * 
         * @return tree in a String form
         */
        std::string print() noexcept(true)
        {
            return treePrint(root, 0);
        }
};


#endif
