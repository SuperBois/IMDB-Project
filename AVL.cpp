/*
Generic AVL Tree Implementation.
Guidelines: 1) Comparator function must be implemented in the inheriting child class.
                - Conventions:
                Return 0 if values are equal.
                Return <0 value for less than boolean result.
                Return >0 value for greater than boolean result.

            2) toString method for the object being stored must be defined for printing.

*/

#include <stack>
template <class type>
class AVL
{
    private:

    // AVL struct
    struct AVLNode
    {
        AVLNode* left;
        AVLNode* right;
        type data;
        int height;
        int balance_factor;
    };

    // Initialize root
    AVLNode* root = NULL;

    // Allocate memory for new node
    AVLNode* GetNewNode()
    {
        AVLNode* node = new AVLNode;
        node -> left = NULL;
        node -> right = NULL;
        node -> balance_factor = 0;
        node -> height = -1;
        return node;
    }

    // Delete a given node.
    void delete_node(AVLNode* node)
    {
        // De-allocate memory. Return memory back to the OS.
        delete node;

        // Point the node to null.
        node = NULL;
    }

    // Rebuild the tree after insertion and deletion updating heights and rebalancing the tree.
    void rebuild(std::stack<AVLNode*>* stk)
    {
        while (!stk -> empty() && stk -> top() != NULL)
        {
            // Update height and balance factor for each node.
            update(stk -> top());

            // Perform rotation if needed based on current node's balance factor.
            root = balance(stk -> top());

            stk -> pop();

            // Establish parent links in each step.
            if (!stk -> empty() && stk -> top() != NULL)
            {
                // Value of node is less than its parent
                if ( compare(root -> data, stk -> top() -> data) == 0 ||
                     compare(root -> data, stk -> top() -> data) < 0 )

                    stk -> top() -> left = root;
                
                // Value of node is greater
                else
                    stk -> top() -> right = root;
            }
        }
        return;
    }

    // Returns the greater of two input numbers.
    int MAX(int num1, int num2)
    {
        if (num1 > num2) return num1;
        return num2;
    }

    // Assigns height and balance factor values to each node.
    void update(AVLNode* node)
    {
        // Initialize left and right heights.
        int left_height = -1, right_height = -1;

        // If child exist, update left and right heights.
        if (node -> left != NULL) left_height = node -> left -> height; 
        if (node -> right != NULL) right_height = node -> right -> height;

        // Increment the maximum of the two heights and set it as node's own height.
        node -> height = 1 + MAX(left_height, right_height);

        // Update balance factor of the input node.
        node -> balance_factor = left_height - right_height;
    }

    // Right rotation about the given node.
    AVLNode* rightRotation(AVLNode* node)
    {
        // Right rotation steps
        AVLNode* left_child = node -> left;
        node -> left = left_child -> right;
        left_child -> right = node;

        // Update heights and balance factors after rotation.
        update(node);
        update(left_child);

        return left_child;
    }

    // Left rotation about the given node.
    AVLNode* leftRotation(AVLNode* node)
    {
        // Left rotation steps.
        AVLNode* right_child = node -> right;
        node -> right = right_child -> left;
        right_child -> left = node;

        // Update heights and balance factors after rotation.
        update(node);
        update(right_child);

        return right_child;
    }

    // Balance tree based on the balance_factor value of a given node.
    AVLNode* balance(AVLNode* node)
    {
        // CASE-I Left heavy case
        if (node -> balance_factor == 2)
        {
            // CASE-(a) LeftLeftCase
            if (node -> left -> balance_factor > 0)
                return LeftLeftCase(node);

            // CASE-(b) LeftRightCase
            return LeftRightCase(node);
        }

        // CASE-II Right heavy case
        else if (node -> balance_factor == -2)
        {
            // CASE-(a) RightRightCase
            if (node -> right -> balance_factor < 0)
                return RightRightCase(node);

            // CASE-(b) RightLeftCase
            return RightLeftCase(node);
        }
        return node;
    }

    // Perform Right rotation.
    AVLNode* LeftLeftCase(AVLNode* node)
    {
        return rightRotation(node);
    }

    // Perform Left Rotation
    AVLNode* RightRightCase(AVLNode* node)
    {
        return leftRotation(node);
    }

    // First perform left and then right rotation.
    AVLNode* LeftRightCase(AVLNode* node)
    {
        // First perform left rotation about the middle node.
        node -> left = leftRotation(node -> left);
        return LeftLeftCase(node);
    }

    // First perform right and then left rotation.
    AVLNode* RightLeftCase(AVLNode* node)
    {
        // First perform right rotation about the middle node.
        node -> right = rightRotation(node -> right);
        return RightRightCase(node);
    }
    
    // Print tree level by level horizontally.
    void print(std::string prefix, AVLNode* root, bool isLeft)
    {
        if( root ==  NULL ) return;

        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // Print the value of the node
        std::cout << root -> data.toString() << std::endl;

        // Enter the next tree level - left and right branch
        print( prefix + (isLeft ? "│   " : "    "), root -> left, true);
        print( prefix + (isLeft ? "│   " : "    "), root -> right, false);
        
    }


    public:

    // Pure virtual function to be implemented in inheriting child classes.
    virtual int compare(type obj1, type obj2) = 0;
    
    // Insert data according to BST invariant and perform rotations if required.
    // Time Complexity = 2 * log n + constant time for rotations = log n
    void insert(type data)
    {   
        // Allocate memory for new node.
        AVLNode* new_node = GetNewNode();

        // Declaring pointers 
        AVLNode* parent;
        AVLNode* current;

        // Creating a stack to keep track of visited nodes.
        std::stack<AVLNode*> stk;

        // Insert root node.
        if (root == NULL)
        {
            new_node -> data = data;
            root = new_node;
            stk.push(root);
        }

        // Insert according to BST condition.
        else
        {
            parent = NULL;
            current = root;

            stk.push(parent);

            // Find the position of node to be inserted.
            while (current != NULL)
            {
                parent = current;

                // Smaller than root values go in left subtree.
                if ( compare(data, current -> data) == 0 || 
                    compare(data, current -> data) < 0 )
                    current = current -> left;

                // Greater than root values go in right subtree.
                else
                    current = current -> right;
                
                // Push parent pointers into the stack.
                stk.push(parent);
            }

            // Insert data in appropriate position
            new_node -> data = data;

            // Establish parent link.
            if ( compare(data, parent -> data) == 0 || 
                compare(data, parent -> data) < 0 )
                parent -> left = new_node;
            else
                parent -> right = new_node;

        }
        // Update the newly inserted node height value
        update(new_node);

        // Rebuild the tree from the traversed path updating height and balance_factor in each step.
        rebuild(&stk);
    }


    // Remove a node from AVL keeping the BST invariant intact. Perform rotations where required.
    // Time Complexity = 2 * log n + constant time for rotations = log n
    void remove(type data)
    {
        // Stack for update and balance methods
        std::stack<AVLNode*> stk;

        // Locate the node to be deleted.
        AVLNode* parent = NULL;
        AVLNode* current = root;

        stk.push(parent);

        while (current != NULL)
        {
            // Element found.
            if (compare(data, current -> data) == 0)
                break;
            
            // Else keep traversing
            parent = current;
            
            if (compare(data, current -> data) < 0)
                current = current -> left;
        
            else
                current = current -> right;  
            
            // Push parent pointers into the stack.
            stk.push(parent);
        }

        // Element does not exist
        if (current == NULL)
            std::cout << "Element does not exist in the tree." << '\n';
        
        // If element to be deleted exists in the tree
        else
        {
            // CASE-I Leaf node
            if (current -> left == NULL && current -> right == NULL)
            {
                type value = current -> data;

                delete_node(current);

                // Adjust parent links
                if ( compare(value, parent -> data) == 0 || 
                    compare(value, parent -> data) < 0 )
                    parent -> left = NULL;
                else
                    parent -> right = NULL;
                
                std::cout << "Node "  << value.toString() << " (leaf node) deleted from the tree." << '\n';
            }

            // CASE-II Node has one child only.
            else if (current -> left == NULL || current -> right == NULL)
            {
                // Current immidiate left node is to be connected with parent.
                if (current -> left != NULL)
                {
                    // Current is on the left side of parent.
                    if ( compare(current -> data, parent -> data) == 0 || 
                        compare(current -> data, parent -> data) < 0 )
                        parent -> left = current -> left;
                    
                    // Current is on the right side of parent.
                    else
                        parent -> right = current -> left;
                }

                // Current immidiate right node is to be connected with parent.
                else
                {
                    // Current is on the left side of parent.
                    if ( compare(current -> data, parent -> data) == 0 || 
                        compare(current -> data, parent -> data) < 0 )
                        parent -> left = current -> right;
            
                    // Current is on the right side of parent.
                    else
                        parent -> right = current -> right;
                }
                type value = current -> data;

                // Delete the node at the end.
                delete_node(current);

                std::cout << "Node "  << value.toString() << " (one child node) deleted from the tree." << '\n';
            }

            // CASE-III Node has two children
            else
            {
                type value = current -> data;
                
                AVLNode* successsor = current -> right;
                AVLNode* parent_successor = current;

                // Find in-order successor.
                while (successsor -> left != NULL)
                {
                    parent_successor = successsor;
                    successsor = successsor -> left; 
                }
                
                // Copy over the contents from successor node.
                current -> data = successsor -> data;

                // CASE-(a) One chid exists to the right of successor node.
                if (successsor -> right != NULL)
                {
                    // Attach parent with immidiate right node.
                    parent_successor -> left = successsor -> right;

                    delete_node(successsor);
                }

                // CASE-(b) No child exists of the successor node.
                else
                {
                    delete_node(successsor);

                    // Adjust parent links
                    if ( compare(parent_successor -> data, value) == 0 || 
                        compare(parent_successor -> data, value) < 0 )
                        parent_successor -> left = NULL;
                    else
                        parent_successor -> right = NULL;
                }

                std::cout << "Node "  << value.toString() << " (two child node) deleted from the tree." << '\n';
            }

            // Rebuild Tree from the traversed path updating height and BF values in each step.
            rebuild(&stk);
        }

    }

    // Print Binary Tree Level-by-Level Horizontally.
    void print()
    {
        print("", root, false);    
    }
    
};