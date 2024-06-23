/**
 * @brief class representing BST (Binary Search Tree) and contatining methods related to it
 */
public class BST<T extends Comparable<T>>
{
    protected class Node<T1 extends Comparable<T1>> 
    {
        T1 value;
        Node<T1> left = null;
        Node<T1> right = null;

        public Node(T1 value)
        {
            this.value = value;
        }
    }

    private Node<T> root;

    public BST()
    {
        root = null;
    }

    /**
     * @brief inserts a value into the BST
     * 
     * @param value to be inserted
     */
    public void insert(T value)
    {
        if (root == null)
        {
            root = new Node<T>(value);
        }
        else
        {
            treeInsert(root, value);
        }

    }

    /**
     * @brief deletes a value from the BST
     * 
     * @param value to be deleted
     */
    public void delete(T value)
    {
        deleteNode(root, value);
    }

    /**
     * @brief searches the BST for the given value
     * 
     * @param value to be found
     * @return true - if value is in BST, false - otherwise
     */
    public boolean search(T value)
    {
        return treeSearch(root, value);
    }

    /**
     * @brief turns the tree into a String
     * 
     * @return tree in a String form
     */
    public String print()
    {
        return treePrint(root, 0);
    }

    private void treeInsert(Node<T> node, T value)
    {
        if (value.compareTo(node.value) < 0) 
        {
            if (node.left == null) 
                node.left = new Node<T>(value);
            else
                treeInsert(node.left, value); 
        }
        else
        {
            if (node.right == null)
                node.right = new Node<T>(value);
            else
                treeInsert(node.right, value);    
        }
    }

    private Node<T> deleteNode(Node<T> node, T value)
    {
        if (node == null)
            return null;

        if (value.compareTo(node.value) < 0)
            node.left = deleteNode(node.left, value);
        else if (value.compareTo(node.value) > 0)
            node.right = deleteNode(node.right, value);
        else
        {
            if (node.left == null && node.right == null) 
                node = null;
            else if (node.left == null)
                node = node.right;
            else if (node.right == null)
                node = node.left;
            else
            {
                Node<T> temp = node.right;
                while (temp.left != null) 
                {
                    temp = temp.left;    
                }
                node.value = temp.value;
                node.right = deleteNode(node.right, temp.value);
            }    
        }

        return node;
    }

    private boolean treeSearch(Node<T> node, T value)
    {
        if (node == null)
            return false;

        if (value.compareTo(node.value) < 0) 
            return treeSearch(node.left, value);    
        else if (value.compareTo(node.value) > 0)
            return treeSearch(node.right, value);
        
        return true;
    }

    private String treePrint(Node<T> node, int depth)
    {
        StringBuilder sb = new StringBuilder();

        if (node != null) 
        {
            sb.append(treePrint(node.right, depth + 1));
            for (int i = 0; i < depth; i++)
            {
                sb.append("   ");
            }    
            sb.append(node.value).append("\n");
            sb.append(treePrint(node.left, depth + 1));
        }

        return sb.toString();
    }
}
