#include <iostream>
using namespace std;

namespace ariel
{
    template <typename T>
    class BinaryTree
    {
    private:
        // inner class
        struct Node
        {
            T value;
            Node *parent;
            Node *left;
            Node *right;
            Node(const T &v, Node *parent) : value(v), parent(parent), left(nullptr), right(nullptr) {}

            ~Node()
            {
                delete left;
                delete right;
                delete parent;
            }
        };

        Node *root;
        BinaryTree(const BinaryTree &copy) {}
        BinaryTree &operator=(const BinaryTree &copy) {}

    public:
        BinaryTree() : root(nullptr) {}
        ~BinaryTree()
        {
            delete root;
        }
        
        BinaryTree &add_root(T) { return *this; }
        
        BinaryTree &add_left(T, T) { return *this; }
        
        BinaryTree &add_right(T, T) { return *this; }

        friend ostream &operator<<(ostream &os, const BinaryTree &b)
        {
            return os << "Binary Tree"<< endl;
        }

        /***************CLASS ITERATOR***************/

        class iteratorTree
        {

        private:
            Node *current_node;

        public:
            iteratorTree(Node *ptr = nullptr) : current_node(ptr){}

            const T &operator*() const { return current_node->value; }

            const T *operator->() const { return &(current_node->value); }

            // ++i;
            iteratorTree &operator++()
            {
                //++pointer_to_current_node;
                cout << "here" << endl;
                if (current_node->right)
                    current_node = current_node->right;
                else
                    current_node = nullptr;
                return *this;
            }

            // i++;
            const iteratorTree operator++(int)
            {
                iteratorTree tmp = *this;
                current_node = current_node->right;
                return tmp;
            }

            bool operator==(const iteratorTree &other) const
            {
                return current_node == other.current_node;
            }

            bool operator!=(const iteratorTree &other) const
            {
                return current_node != other.current_node;
            }
        };
        /***************END OF CLASS ITERATOR***************/

        iteratorTree begin_preorder() const { return iteratorTree(root); }
        iteratorTree end_preorder() const { return iteratorTree(root); }
        iteratorTree begin_inorder() const { return iteratorTree(root); }
        iteratorTree end_inorder() const { return iteratorTree(root); }
        iteratorTree begin_postorder() const { return iteratorTree(root); }
        iteratorTree end_postorder() const { return iteratorTree(root); }
        iteratorTree begin() const { return begin_inorder(); }
        iteratorTree end() const { return end_inorder(); }
    };
}