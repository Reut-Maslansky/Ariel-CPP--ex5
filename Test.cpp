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

        for (int i = 0; i < 20; i++)
        {
            CHECK_NOTHROW(tree_of_ints.add_root(i));
            CHECK(*(tree_of_ints.begin_inorder()) == i);
            CHECK(*(tree_of_ints.begin_postorder()) == i);
            CHECK(*(tree_of_ints.begin_preorder()) == i);
            CHECK(*(tree_of_ints.end_inorder()) == i);
            CHECK(*(tree_of_ints.end_postorder()) == i);
            CHECK(*(tree_of_ints.end_preorder()) == i);
        }
    }
    SUBCASE("add left")
    {
        //now, there is one node in the tree- 19.
        CHECK_THROWS(tree_of_ints.add_left((rand() % 10), (rand() % 10)));

        for (int i = 0; i < 10; i++)
        {
            CHECK_NOTHROW(tree_of_ints.add_left(19, i));
            CHECK(*(tree_of_ints.begin_inorder()) == i);
            CHECK(*(tree_of_ints.begin_postorder()) == i);
            CHECK(*(tree_of_ints.begin_preorder()) == 19);
            CHECK(*(tree_of_ints.end_inorder()) == 19);
            CHECK(*(tree_of_ints.end_postorder()) == 19);
            CHECK(*(tree_of_ints.end_preorder()) == i);
        }

        /*

            └──19
               |──9

        */

        for(int i=0; i<10; i++){

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