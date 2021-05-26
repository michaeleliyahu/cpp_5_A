#include <iostream>

namespace ariel
{
    template <typename T>
    class BinaryTree
    {

        //all add function
    public:
        BinaryTree() : t_first(nullptr) {}

        BinaryTree add_root(int number)
        {
            t_first = new Node(number, t_first);
            return *this;
        }
        BinaryTree add_left(int num_first, int num_sec) { return *this; }
        BinaryTree add_right(int num_first, int num_sec) { return *this; }
        BinaryTree add_root(std::string number)
        {
            t_first = new Node(number, t_first);
            return *this;
        }
        BinaryTree add_left(std::string num_first, std::string num_sec) { return *this; }
        BinaryTree add_right(std::string num_first, std::string num_sec) { return *this; }

        //node
    private:
        struct Node
        {
            T t_value;
            Node *t_right;
            Node *t_left;
            Node(const T &val, Node *n) : t_value(val), t_right(n), t_left(n) {}
        };

        Node *t_first;

        //operator for iterator
    public:
        //preorder
        class preorder_iterator
        {
        private:
            Node *pointer_to_node;

        public:
            preorder_iterator(Node *ptr = nullptr) : pointer_to_node(ptr) {}

            preorder_iterator &operator++() { return *this; }
            bool operator!=(const preorder_iterator &rhs) { return false; }
            T &operator*() { return pointer_to_node->t_value; }
            T *operator->() { return &(pointer_to_node->t_value); }
        };

        //inorder
        class inorder_iterator
        {
        private:
            Node *pointer_to_node;

        public:
            inorder_iterator(Node *ptr = nullptr) : pointer_to_node(ptr) {}

            bool operator!=(const inorder_iterator &rhs) { return false; }
            inorder_iterator &operator++() { return *this; }
            T &operator*() { return pointer_to_node->t_value; }
            T *operator->() { return &(pointer_to_node->t_value); }
        };

        //postorder
        class postorder_iterator
        {
        private:
            Node *pointer_to_node;

        public:
            postorder_iterator(Node *ptr = nullptr) : pointer_to_node(ptr) {}

            bool operator!=(const postorder_iterator &rhs) { return false; }
            postorder_iterator &operator++() { return *this; }
            T &operator*() { return pointer_to_node->t_value; }
            T *operator->() { return &(pointer_to_node->t_value); }
        };

        //begin/end for iterator
        preorder_iterator begin_preorder() { return preorder_iterator{t_first}; }
        preorder_iterator end_preorder() { return preorder_iterator{nullptr}; }

        inorder_iterator begin_inorder() { return inorder_iterator{t_first}; }
        inorder_iterator end_inorder() { return inorder_iterator{nullptr}; }

        postorder_iterator begin_postorder() { return postorder_iterator{t_first}; }
        postorder_iterator end_postorder() { return postorder_iterator{nullptr}; }

        inorder_iterator begin() { return inorder_iterator{t_first}; }
        inorder_iterator end() { return inorder_iterator{nullptr}; }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &strm)
        {
            return os;
        }
    };
}