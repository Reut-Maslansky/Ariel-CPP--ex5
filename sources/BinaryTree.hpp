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
            Node *left;
            Node *right;
            Node(const T &v) : value(v), left(nullptr), right(nullptr) {}
            Node(const T &v, Node *l, Node *r) : value(v), left(l), right(r) {}

            ~Node()
            {
                delete left;
                delete right;
            }
            Node &operator=(const Node &other)
            {
                other.swap(*this);
                return *this;
            }
        };

        Node *root;

    public:
        /***************CLASS ITERATOR***************/

        class iteratorTree
        {

        private:
            Node *current_node;
            queue<Node *> it;

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
                    it.push(curr);
                    s.pop();

                    curr = curr->right;
                }

                it.push(nullptr);
                current_node = it.front();
                it.pop();
            }
            void init_queue_preorder()
            {
                if (current_node == nullptr)
                {
                    return;
                }
                stack<Node *> s;
                s.push(current_node);

                while (!s.empty())
                {
                    Node *node = s.top();
                    it.push(node);
                    s.pop();

                    if (node->right)
                        s.push(node->right);
                    if (node->left)
                        s.push(node->left);
                }

                it.push(nullptr);
                current_node = it.front();
                it.pop();
            }
            void init_queue_postorder()
            {
                if (current_node == nullptr)
                {
                    return;
                }

                stack<Node *> s1, s2;

                s1.push(current_node);
                Node *node;

                while (!s1.empty())
                {
                    node = s1.top();
                    s1.pop();
                    s2.push(node);

                    if (node->left)
                        s1.push(node->left);
                    if (node->right)
                        s1.push(node->right);
                }

                while (!s2.empty())
                {

                    node = s2.top();
                    it.push(node);
                    s2.pop();
                }

                it.push(nullptr);
                current_node = it.front();
                it.pop();
            }

        public:
            iteratorTree(Node *ptr = nullptr) : current_node(ptr) {}

            iteratorTree(Node *ptr, int t) : current_node(ptr)
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

            const T &operator*() const { return current_node->value; }

            const T *operator->() const { return &(current_node->value); }

            // ++i;
            iteratorTree &operator++()
            {
                if (!it.empty())
                {
                    current_node = it.front();
                    it.pop();
                }
                return *this;
            }

            // i++;
            const iteratorTree operator++(int)
            {
                iteratorTree tmp = *this;
                current_node = it.front();
                it.pop();
                return tmp;
            }

            bool operator==(const iteratorTree &other) const { return current_node == other.current_node; }

            bool operator!=(const iteratorTree &other) const { return current_node != other.current_node; }

            Node *get_node() { return current_node; }
        };
        /***************END OF CLASS ITERATOR***************/

        BinaryTree() : root(nullptr) {}
        ~BinaryTree()
        {
            delete root;
        }

        void printBT(const string &prefix, const Node *node, bool isLeft) const
        {
            if (node != nullptr)
            {
                cout << prefix;

                cout << (isLeft ? "├──" : "└──");

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

            os << "\033[35m"
               << "\nBinary Tree:\n"
               << endl;
            b.printBT(b.root);
            os << "\033[0m";
            return os;
        }

        iteratorTree begin_preorder() const { return iteratorTree(root, PREORDER); }
        iteratorTree end_preorder() const { return iteratorTree(); }
        iteratorTree begin_inorder() const { return iteratorTree(root, INORDER); }
        iteratorTree end_inorder() const { return iteratorTree(); }
        iteratorTree begin_postorder() const { return iteratorTree(root, POSTORDER); }
        iteratorTree end_postorder() const { return iteratorTree(); }
        iteratorTree begin() const { return begin_inorder(); }
        iteratorTree end() const { return iteratorTree(); }

        BinaryTree &add_root(T t)
        {
            if (root)
            {
                root = new Node{t, root->left, root->right};
            }
            else
            {
                root = new Node{t};
            }
            return *this;
        }

        BinaryTree &add_left(T p, T v)
        {
            if (root == nullptr)
            {
                throw invalid_argument("There is no root in this tree");
            }
            Node *curr = nullptr;
            for (auto i = begin_inorder(); i != end_inorder(); ++i)
            {
                if (*i == p)
                {
                    curr = i.get_node();
                    break;
                }
            }
            if (curr == nullptr)
            {
                throw invalid_argument("This node is not in the tree");
            }

            if (curr->left)
            {
                curr->left = new Node{v, curr->left->left, curr->left->right};
            }
            else
            {
                curr->left = new Node{v};
            }
            return *this;
        }

        BinaryTree &add_right(T p, T v)
        {
            if (root == nullptr)
            {
                throw invalid_argument("There is no root in this tree");
            }
            Node *curr = nullptr;
            for (auto i = begin_inorder(); i != end_inorder(); ++i)
            {
                if (*i == p)
                {
                    curr = i.get_node();
                    break;
                }
            }
            if (curr == nullptr)
            {
                throw invalid_argument("This node is not in the tree");
            }
            if (curr->right)
            {
                curr->right = new Node{v, curr->right->left, curr->right->right};
            }
            else
            {
                curr->right = new Node{v};
            }
            return *this;
        }
    };
}