#include "doctest.h"
#include "BinaryTree.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

TEST_CASE("int")
{

    BinaryTree<int> tree_of_ints;
    SUBCASE("before add root")
    {

        //can't make an iterator before add root- there is no root.
        CHECK_THROWS(tree_of_ints.begin_inorder());
        CHECK_THROWS(tree_of_ints.begin_postorder());
        CHECK_THROWS(tree_of_ints.begin_preorder());
        CHECK_THROWS(tree_of_ints.end_inorder());
        CHECK_THROWS(tree_of_ints.end_postorder());
        CHECK_THROWS(tree_of_ints.end_preorder());

        //can't add left/right child before add root.
        CHECK_THROWS(tree_of_ints.add_left((rand() % 10), (rand() % 10)));
        CHECK_THROWS(tree_of_ints.add_right((rand() % 10), (rand() % 10)));
    }
    SUBCASE("add root")
    {

        for (int i = 0; i <= 10; i++)
        {
            CHECK_NOTHROW(tree_of_ints.add_root(i));
            CHECK(*(tree_of_ints.begin_inorder()) == i);
            CHECK(*(tree_of_ints.begin_postorder()) == i);
            CHECK(*(tree_of_ints.begin_preorder()) == i);
        }
    }
    SUBCASE("add left")
    {
        //now, there is one node in the tree- 10.
        CHECK_THROWS(tree_of_ints.add_left((rand() % 10), (rand() % 10)));

        for (int i = 0; i < 10; i++)
        {
            CHECK_NOTHROW(tree_of_ints.add_left(10, i));
            CHECK(*(tree_of_ints.begin_inorder()) == i);
            CHECK(*(tree_of_ints.begin_postorder()) == i);
            CHECK(*(tree_of_ints.begin_preorder()) == 10);
        }

        CHECK_NOTHROW(tree_of_ints.add_left(9, 8));

        for (int i = 8; i > 0; i--)
        {
            CHECK_NOTHROW(tree_of_ints.add_left(i, i - 1));
        }

        //└──10
        //   ├──9
        //      ├──8
        //         ├──7
        //            ├──6
        //               ├──5
        //                  ├──4
        //                     ├──3
        //                        ├──2
        //                           ├──1

        int count = 0;
        for (auto it = tree_of_ints.begin_inorder(); it != tree_of_ints.end_inorder(); ++it)
        {
            CHECK(*it == count++);
        }
        for (auto it = tree_of_ints.begin_preorder(); it != tree_of_ints.end_preorder(); ++it)
        {
            CHECK(*it == count--);
        }
        for (auto it = tree_of_ints.begin_postorder(); it != tree_of_ints.end_postorder(); ++it)
        {
            CHECK(*it == count++);
        }
    }

    SUBCASE("add right")
    {
        BinaryTree<int> tree_of_ints1;
        CHECK_NOTHROW(tree_of_ints1.add_root(10));

        //now, there is 10 node in the tree- 10.
        CHECK_THROWS(tree_of_ints1.add_right((rand() % 10), (rand() % 10)));

        for (int i = 0; i < 10; i++)
        {
            CHECK_NOTHROW(tree_of_ints1.add_right(10, i));
            CHECK(*(tree_of_ints1.begin_inorder()) == 10);
            CHECK(*(tree_of_ints1.begin_postorder()) == i);
            CHECK(*(tree_of_ints1.begin_preorder()) == 10);
        }

        CHECK_NOTHROW(tree_of_ints1.add_right(9, 8));

        for (int i = 8; i > 0; i--)
        {
            CHECK_NOTHROW(tree_of_ints1.add_right(i, i - 1));
        }

        //                           ├──1
        //                        ├──2
        //                     ├──3
        //                  ├──4
        //               ├──5
        //            ├──6
        //         ├──7
        //      ├──8
        //   ├──9
        //└──10


        int count = 0;
        for (auto it = tree_of_ints1.begin_inorder(); it != tree_of_ints1.end_inorder(); ++it)
        {
            CHECK(*it == count++);
        }
        for (auto it = tree_of_ints1.begin_preorder(); it != tree_of_ints1.end_preorder(); ++it)
        {
            CHECK(*it == count--);
        }
        for (auto it = tree_of_ints1.begin_postorder(); it != tree_of_ints1.end_postorder(); ++it)
        {
            CHECK(*it == count++);
        }
    }
}
TEST_CASE("string")
{
    BinaryTree<string> tree_of_strings;

    for (int i = 0; i < 20; i++)
        CHECK(0 == 0);
}

class Person
{
    string name;
    int age;

public:
    string get_name() { return name; }
    int get_age() { return age; }
};

TEST_CASE("new object - person")
{
    BinaryTree<Person> tree_of_persons;

    for (int i = 0; i < 20; i++)
        CHECK(0 == 0);
}