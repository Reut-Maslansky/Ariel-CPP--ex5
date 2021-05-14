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
        };

        Node *root;
        BinaryTree(const BinaryTree &copy) {}
        BinaryTree &operator=(const BinaryTree &copy) {}

    public:
        BinaryTree() {}
        void destroyRecursive(Node *n)
        {
            if (n)
            {
                destroyRecursive(n->left);
                destroyRecursive(n->right);
                delete n;
            }
        }
        ~BinaryTree()
        {
            destroyRecursive(root);
        }
        BinaryTree &add_root(T) { return *this; }
        BinaryTree &add_left(T, T) { return *this; }
        BinaryTree &add_right(T, T) { return *this; }
        friend ostream &operator<<(ostream &os, const BinaryTree &b)
        {
            return os;
        }

        /***************CLASS ITERATOR***************/

        class iterator
        {

        private:
            Node *current_node;

        public:
            iterator(Node *ptr = nullptr) : current_node(ptr) {}

            const T &operator*() const { return current_node->value; }

            const T *operator->() const { return &(current_node->value); }

            // ++i;
            iterator &operator++()
            {
                //++pointer_to_current_node;
                current_node = current_node->right;
                return *this;
            }

            // i++;
            const iterator operator++(int)
            {
                iterator tmp = *this;
                current_node = current_node->right;
                return tmp;
            }

            bool operator==(const iterator &other) const
            {
                return current_node == other.current_node;
            }

            bool operator!=(const iterator &other) const
            {
                return current_node != other.current_node;
            }
        };
        /***************END OF CLASS ITERATOR***************/

        iterator begin_preorder() const { return iterator(root); }
        iterator end_preorder() const { return iterator(root); }
        iterator begin_inorder() const { return iterator(root); }
        iterator end_inorder() const { return iterator(root); }
        iterator begin_postorder() const { return iterator(root); }
        iterator end_postorder() const { return iterator(root); }
        iterator begin() const { return begin_inorder(); }
        iterator end() const { return end_inorder(); }
    };
}