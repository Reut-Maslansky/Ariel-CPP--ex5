#include <iostream>
#include <stack>
#include <queue>

using namespace std;

namespace ariel
{
    const int INORDER = 0;
    const int PREORDER = 1;
    const int POSTORDER = 2;

    template <typename T>
    class BinaryTree
    {
    private:
        // inner class
        struct Node
        {
            T value;
            // Node *parent;
            Node *left;
            Node *right;
            // Node(const T &v, Node *parent) : value(v), parent(parent), left(nullptr), right(nullptr) {}
            Node(const T &v) : value(v), left(nullptr), right(nullptr) {}

            ~Node()
            {
                delete left;
                delete right;
                // delete parent;
            }
        };

        Node *root;
        // BinaryTree(const BinaryTree &copy) {}
        // BinaryTree &operator=(const BinaryTree &copy) {}

    public:
        BinaryTree() : root(nullptr) {}
        ~BinaryTree()
        {
            delete root;
        }

        BinaryTree &add_root(T t)
        {
            // root = new Node{t, nullptr};
            root = new Node{t};
            return *this;
        }

        BinaryTree &add_left(T p, T v)
        {
            // root = new Node{v, nullptr};
            root = new Node{v};
            return *this;
        }

        BinaryTree &add_right(T p, T v)
        {
            // root = new Node{v, nullptr};
            root = new Node{v};
            return *this;
        }

        void printBT(const string &prefix, const Node *node, bool isLeft) const
        {
            if (node != nullptr)
            {
                std::cout << prefix;

                std::cout << (isLeft ? "├──" : "└──");

                // print the value of the node
                cout << node->value << endl;

                // enter the next tree level - left and right branch
                printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
                printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
            }
        }

        void printBT(const Node *node) const
        {
            printBT("", node, false);
        }

        friend ostream &operator<<(ostream &os, const BinaryTree &b)
        {

            os << "Binary Tree" << endl;
            b.printBT(b.root);
            return os;
        }

        /***************CLASS ITERATOR***************/

        class iteratorTree
        {

        private:
            Node *current_node;
            queue<Node *> in;
            queue<Node *> pre;
            queue<Node *> post;
            void init_queue_inorder()
            {
                if (current_node == nullptr)
                {
                    return;
                }
                stack<Node *> s;
                Node *curr = current_node;

                while (curr != nullptr || s.empty() == false)
                {
                    while (curr != nullptr)
                    {
                        s.push(curr);
                        curr = curr->left;
                    }

                    curr = s.top();
                    in.push(curr);
                    s.pop();

                    curr = curr->right;
                }
            }
            void init_queue_preorder()
            {
                if (current_node == nullptr)
                {
                    return;
                }
                stack<Node *> s;
                s.push(current_node);

                while (s.empty() == false)
                {
                    Node *node = s.top();
                    pre.push(node);
                    s.pop();

                    if (node->right)
                        s.push(node->right);
                    if (node->left)
                        s.push(node->left);
                }
            }
            void init_queue_postorder()
            {
                if (current_node == nullptr)
                {
                    return;
                }
                stack<Node *> s;
                Node *node = current_node;

                do
                {
                    while (node)
                    {
                        if (node->right)
                        {
                            s.push(node->right);
                        }
                        s.push(node);

                        node = node->left;
                    }

                    node = s.top();
                    s.pop();

                    if (node->right && s.top() == node->right)
                    {
                        s.pop();
                        s.push(node);
                        node = node->right;
                    }
                    else
                    {
                        post.push(node);
                        node = nullptr;
                    }
                } while (!s.empty());
            }

        public:
            iteratorTree(Node *ptr = nullptr, int t = -1) : current_node(ptr)
            {
                if (t == INORDER)
                {
                    init_queue_inorder();
                }
                if (t == PREORDER)
                {
                    init_queue_preorder();
                }
                if (t == POSTORDER)
                {
                    init_queue_postorder();
                }
            }

            const T &operator*() const
            {
                return current_node->value;
            }

            const T *operator->() const { return &(current_node->value); }

            // ++i;
            iteratorTree &operator++()
            {
                //++pointer_to_current_node;
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

        iteratorTree begin_preorder() const { return iteratorTree(root, PREORDER); }
        iteratorTree end_preorder() const { return iteratorTree(root, PREORDER); }
        iteratorTree begin_inorder() const { return iteratorTree(root, INORDER); }
        iteratorTree end_inorder() const { return iteratorTree(root, INORDER); }
        iteratorTree begin_postorder() const { return iteratorTree(root, POSTORDER); }
        iteratorTree end_postorder() const { return iteratorTree(root, POSTORDER); }
        iteratorTree begin() const { return begin_inorder(); }
        iteratorTree end() const { return end_inorder(); }
    };
}