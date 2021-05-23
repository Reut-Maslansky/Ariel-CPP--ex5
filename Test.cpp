#include "doctest.h"
#include "BinaryTree.hpp"
#include <iostream>
#include <string>

using namespace ariel;
using namespace std;

TEST_CASE("int")
{
    BinaryTree<int> tree_of_ints;
    SUBCASE("before add root")
    {
        //make an iterator before add root.
        CHECK(tree_of_ints.begin_inorder() == tree_of_ints.end_inorder());
        CHECK(tree_of_ints.begin_postorder() == tree_of_ints.end_postorder());
        CHECK(tree_of_ints.begin_preorder() == tree_of_ints.end_preorder());

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
        CHECK_NOTHROW(tree_of_ints.add_root(10));

        //There is one node in the tree- 10.
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
        for (auto it = tree_of_ints.begin_inorder(); it != tree_of_ints.end_inorder(); it++)
        {
            CHECK(*it == count++);
        }
        for (auto it = tree_of_ints.begin_preorder(); it != tree_of_ints.end_preorder(); it++)
        {
            CHECK(*it == --count);
        }
        for (auto it = tree_of_ints.begin_postorder(); it != tree_of_ints.end_postorder(); it++)
        {
            CHECK(*it == count++);
        }
    }

    SUBCASE("add right")
    {
        BinaryTree<int> tree_of_ints;
        CHECK_NOTHROW(tree_of_ints.add_root(10));

        //now, there is 10 node in the tree- 10.
        CHECK_THROWS(tree_of_ints.add_right((rand() % 10), (rand() % 10)));

        for (int i = 0; i < 10; i++)
        {
            CHECK_NOTHROW(tree_of_ints.add_right(10, i));
            CHECK(*(tree_of_ints.begin_inorder()) == 10);
            CHECK(*(tree_of_ints.begin_postorder()) == i);
            CHECK(*(tree_of_ints.begin_preorder()) == 10);
        }

        CHECK_NOTHROW(tree_of_ints.add_right(9, 8));

        for (int i = 8; i > 0; i--)
        {
            CHECK_NOTHROW(tree_of_ints.add_right(i, i - 1));
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

        int count = 10;
        for (auto it = tree_of_ints.begin_inorder(); it != tree_of_ints.end_inorder(); ++it)
        {
            CHECK(*it == count--);
        }
        count = 10;
        for (auto it = tree_of_ints.begin_preorder(); it != tree_of_ints.end_preorder(); ++it)
        {
            CHECK(*it == count--);
        }
        for (auto it = tree_of_ints.begin_postorder(); it != tree_of_ints.end_postorder(); ++it)
        {
            CHECK(*it == ++count);
        }
    }

    SUBCASE("preorder")
    {
        BinaryTree<int> tree_of_ints;
        CHECK_NOTHROW(tree_of_ints.add_root(1));
        CHECK_NOTHROW(tree_of_ints.add_left(1, 2));
        CHECK_NOTHROW(tree_of_ints.add_left(2, 3));
        CHECK_NOTHROW(tree_of_ints.add_right(2, 4));
        CHECK_NOTHROW(tree_of_ints.add_left(4, 5));
        CHECK_NOTHROW(tree_of_ints.add_right(4, 6));
        CHECK_NOTHROW(tree_of_ints.add_right(1, 7));
        CHECK_NOTHROW(tree_of_ints.add_right(7, 8));
        CHECK_NOTHROW(tree_of_ints.add_left(8, 9));

        CHECK_NOTHROW(cout << tree_of_ints);

        int count = 1;
        for (auto it = tree_of_ints.begin_preorder(); it != tree_of_ints.end_preorder(); ++it)
        {
            CHECK(*it == count++);
        }
        CHECK(count == 10);
    }
    SUBCASE("inorder")
    {
        BinaryTree<int> tree_of_ints;
        CHECK_NOTHROW(tree_of_ints.add_root(6));
        CHECK_NOTHROW(tree_of_ints.add_left(6, 2));
        CHECK_NOTHROW(tree_of_ints.add_left(2, 1));
        CHECK_NOTHROW(tree_of_ints.add_right(2, 4));
        CHECK_NOTHROW(tree_of_ints.add_left(4, 3));
        CHECK_NOTHROW(tree_of_ints.add_right(4, 5));
        CHECK_NOTHROW(tree_of_ints.add_right(6, 7));
        CHECK_NOTHROW(tree_of_ints.add_right(7, 9));
        CHECK_NOTHROW(tree_of_ints.add_left(9, 8));
        int count = 1;
        for (auto it = tree_of_ints.begin_inorder(); it != tree_of_ints.end_inorder(); ++it)
        {
            CHECK(*it == count++);
        }
        CHECK(count == 10);
    }
    SUBCASE("postorder")
    {
        BinaryTree<int> tree_of_ints;
        CHECK_NOTHROW(tree_of_ints.add_root(9));
        CHECK_NOTHROW(tree_of_ints.add_left(9, 5));
        CHECK_NOTHROW(tree_of_ints.add_left(5, 1));
        CHECK_NOTHROW(tree_of_ints.add_right(5, 4));
        CHECK_NOTHROW(tree_of_ints.add_left(4, 2));
        CHECK_NOTHROW(tree_of_ints.add_right(4, 3));
        CHECK_NOTHROW(tree_of_ints.add_right(9, 8));
        CHECK_NOTHROW(tree_of_ints.add_right(8, 7));
        CHECK_NOTHROW(tree_of_ints.add_left(7, 6));
        int count = 1;
        for (auto it = tree_of_ints.begin_postorder(); it != tree_of_ints.end_postorder(); ++it)
        {
            CHECK(*it == count++);
        }
        CHECK(count == 10);
    }
}
TEST_CASE("string")
{
    BinaryTree<string> tree_of_strings;

    SUBCASE("before add root")
    {
        //make an iterator before add root.
        CHECK(tree_of_strings.begin_inorder() == tree_of_strings.end_inorder());
        CHECK(tree_of_strings.begin_postorder() == tree_of_strings.end_postorder());
        CHECK(tree_of_strings.begin_preorder() == tree_of_strings.end_preorder());

        //can't add left/right child before add root.
        CHECK_THROWS(tree_of_strings.add_left(to_string((rand() % 10)), to_string((rand() % 10))));
        CHECK_THROWS(tree_of_strings.add_right(to_string((rand() % 10)), to_string((rand() % 10))));
    }
    SUBCASE("add root")
    {

        for (int i = 0; i <= 10; i++)
        {
            CHECK_NOTHROW(tree_of_strings.add_root(to_string(i)));
            CHECK(*(tree_of_strings.begin_inorder()) == to_string(i));
            CHECK(*(tree_of_strings.begin_postorder()) == to_string(i));
            CHECK(*(tree_of_strings.begin_preorder()) == to_string(i));
        }
    }
    SUBCASE("add left")
    {
        CHECK_NOTHROW(tree_of_strings.add_root("10"));

        //There is one node in the tree- 10.
        CHECK_THROWS(tree_of_strings.add_left(to_string((rand() % 10)), to_string((rand() % 10))));

        for (int i = 0; i < 10; i++)
        {
            CHECK_NOTHROW(tree_of_strings.add_left("10", to_string(i)));
            CHECK(*(tree_of_strings.begin_inorder()) == to_string(i));
            CHECK(*(tree_of_strings.begin_postorder()) == to_string(i));
            CHECK(*(tree_of_strings.begin_preorder()) == "10");
        }

        CHECK_NOTHROW(tree_of_strings.add_left("9", "8"));

        for (int i = 8; i > 0; i--)
        {
            CHECK_NOTHROW(tree_of_strings.add_left(to_string(i), to_string(i - 1)));
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
        for (auto it = tree_of_strings.begin_inorder(); it != tree_of_strings.end_inorder(); ++it)
        {
            CHECK(*it == to_string(count++));
        }
        for (auto it = tree_of_strings.begin_preorder(); it != tree_of_strings.end_preorder(); ++it)
        {
            CHECK(*it == to_string(--count));
        }
        for (auto it = tree_of_strings.begin_postorder(); it != tree_of_strings.end_postorder(); ++it)
        {
            CHECK(*it == to_string(count++));
        }
    }

    SUBCASE("add right")
    {
        BinaryTree<string> tree_of_strings;
        CHECK_NOTHROW(tree_of_strings.add_root("10"));

        //now, there is 10 node in the tree- 10.
        CHECK_THROWS(tree_of_strings.add_right(to_string((rand() % 10)), to_string((rand() % 10))));

        for (int i = 0; i < 10; i++)
        {
            CHECK_NOTHROW(tree_of_strings.add_right("10", to_string(i)));
            CHECK(*(tree_of_strings.begin_inorder()) == "10");
            CHECK(*(tree_of_strings.begin_postorder()) == to_string(i));
            CHECK(*(tree_of_strings.begin_preorder()) == "10");
        }

        CHECK_NOTHROW(tree_of_strings.add_right("9", "8"));

        for (int i = 8; i > 0; i--)
        {
            CHECK_NOTHROW(tree_of_strings.add_right(to_string(i), to_string(i - 1)));
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

        int count = 10;
        for (auto it = tree_of_strings.begin_inorder(); it != tree_of_strings.end_inorder(); ++it)
        {
            CHECK(*it == to_string(count--));
        }
        count = 10;
        for (auto it = tree_of_strings.begin_preorder(); it != tree_of_strings.end_preorder(); ++it)
        {
            CHECK(*it == to_string(count--));
        }
        for (auto it = tree_of_strings.begin_postorder(); it != tree_of_strings.end_postorder(); ++it)
        {
            CHECK(*it == to_string(++count));
        }
    }

    SUBCASE("preorder")
    {
        BinaryTree<string> tree_of_strings;

        CHECK_NOTHROW(tree_of_strings.add_root("1"));
        CHECK_NOTHROW(tree_of_strings.add_left("1", "2"));
        CHECK_NOTHROW(tree_of_strings.add_left("2", "3"));
        CHECK_NOTHROW(tree_of_strings.add_right("2", "4"));
        CHECK_NOTHROW(tree_of_strings.add_left("4", "5"));
        CHECK_NOTHROW(tree_of_strings.add_right("4", "6"));
        CHECK_NOTHROW(tree_of_strings.add_right("1", "7"));
        CHECK_NOTHROW(tree_of_strings.add_right("7", "8"));
        CHECK_NOTHROW(tree_of_strings.add_left("8", "9"));

        CHECK_NOTHROW(cout << tree_of_strings);

        int count = 1;
        for (auto it = tree_of_strings.begin_preorder(); it != tree_of_strings.end_preorder(); ++it)
        {
            CHECK(*it == to_string(count++));
        }
        CHECK(count == 10);
    }
    SUBCASE("inorder")
    {
        BinaryTree<string> tree_of_strings;
        CHECK_NOTHROW(tree_of_strings.add_root("6"));
        CHECK_NOTHROW(tree_of_strings.add_left("6", "2"));
        CHECK_NOTHROW(tree_of_strings.add_left("2", "1"));
        CHECK_NOTHROW(tree_of_strings.add_right("2", "4"));
        CHECK_NOTHROW(tree_of_strings.add_left("4", "3"));
        CHECK_NOTHROW(tree_of_strings.add_right("4", "5"));
        CHECK_NOTHROW(tree_of_strings.add_right("6", "7"));
        CHECK_NOTHROW(tree_of_strings.add_right("7", "9"));
        CHECK_NOTHROW(tree_of_strings.add_left("9", "8"));
        int count = 1;
        for (auto it = tree_of_strings.begin_inorder(); it != tree_of_strings.end_inorder(); ++it)
        {
            CHECK(*it == to_string(count++));
        }
        CHECK(count == 10);
    }
    SUBCASE("postorder")
    {
        BinaryTree<string> tree_of_strings;
        CHECK_NOTHROW(tree_of_strings.add_root("9"));
        CHECK_NOTHROW(tree_of_strings.add_left("9", "5"));
        CHECK_NOTHROW(tree_of_strings.add_left("5", "1"));
        CHECK_NOTHROW(tree_of_strings.add_right("5", "4"));
        CHECK_NOTHROW(tree_of_strings.add_left("4", "2"));
        CHECK_NOTHROW(tree_of_strings.add_right("4", "3"));
        CHECK_NOTHROW(tree_of_strings.add_right("9", "8"));
        CHECK_NOTHROW(tree_of_strings.add_right("8", "7"));
        CHECK_NOTHROW(tree_of_strings.add_left("7", "6"));
        int count = 1;
        for (auto it = tree_of_strings.begin_postorder(); it != tree_of_strings.end_postorder(); ++it)
        {
            CHECK(*it == to_string(count++));
        }
        CHECK(count == 10);
    }
}

class Person
{
    int age;

public:
    Person(int age) : age(age) {}
    int get_age() const { return age; }
    bool operator==(Person &other) const
    {
        return age == other.age;
    }

    friend ostream &operator<<(ostream &os, const Person &b)
    {
        return os << b.age << endl;
    }
};

TEST_CASE("new object - person")
{
    BinaryTree<Person> tree_of_persons;

    SUBCASE("before add root")
    {
        //make an iterator before add root.
        CHECK(tree_of_persons.begin_inorder() == tree_of_persons.end_inorder());
        CHECK(tree_of_persons.begin_postorder() == tree_of_persons.end_postorder());
        CHECK(tree_of_persons.begin_preorder() == tree_of_persons.end_preorder());
    }
    SUBCASE("add root")
    {

        for (int i = 0; i <= 10; i++)
        {
            CHECK_NOTHROW(tree_of_persons.add_root(Person{i}));
            CHECK((*(tree_of_persons.begin_inorder())).get_age() == i);
            CHECK((*(tree_of_persons.begin_postorder())).get_age() == i);
            CHECK((*(tree_of_persons.begin_preorder())).get_age() == i);
        }
    }
    SUBCASE("add left")
    {
        CHECK_NOTHROW(tree_of_persons.add_root(Person{10}));

        //There is one node in the tree- Person{10}.
        CHECK_THROWS(tree_of_persons.add_left(Person{(rand() % 10)}, Person{(rand() % 10)}));

        for (int i = 0; i < 10; i++)
        {
            CHECK_NOTHROW(tree_of_persons.add_left(Person{10}, Person{i}));
            CHECK((*(tree_of_persons.begin_inorder())).get_age() == i);
            CHECK((*(tree_of_persons.begin_postorder())).get_age() == i);
            CHECK((*(tree_of_persons.begin_preorder())).get_age() == 10);
        }

        CHECK_NOTHROW(tree_of_persons.add_left(Person{9}, Person{8}));

        for (int i = 8; i > 0; i--)
        {
            CHECK_NOTHROW(tree_of_persons.add_left(Person{i}, Person{i - 1}));
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
        for (auto it = tree_of_persons.begin_inorder(); it != tree_of_persons.end_inorder(); ++it)
        {
            CHECK((*it).get_age() == count++);
        }
        for (auto it = tree_of_persons.begin_preorder(); it != tree_of_persons.end_preorder(); ++it)
        {
            CHECK((*it).get_age() == --count);
        }
        for (auto it = tree_of_persons.begin_postorder(); it != tree_of_persons.end_postorder(); ++it)
        {
            CHECK((*it).get_age() == count++);
        }
    }

    SUBCASE("add right")
    {
        BinaryTree<Person> tree_of_persons;

        CHECK_NOTHROW(tree_of_persons.add_root(Person{10}));

        //There is one node in the tree- Person{10}.
        CHECK_THROWS(tree_of_persons.add_right(Person{(rand() % 10)}, Person{(rand() % 10)}));

        for (int i = 0; i < 10; i++)
        {
            CHECK_NOTHROW(tree_of_persons.add_right(Person{10}, Person{i}));
            CHECK((*(tree_of_persons.begin_inorder())).get_age() == 10);
            CHECK((*(tree_of_persons.begin_postorder())).get_age() == i);
            CHECK((*(tree_of_persons.begin_preorder())).get_age() == 10);
        }

        CHECK_NOTHROW(tree_of_persons.add_right(Person{9}, Person{8}));

        for (int i = 8; i > 0; i--)
        {
            CHECK_NOTHROW(tree_of_persons.add_right(Person{i}, Person{i - 1}));
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

        int count = 10;
        for (auto it = tree_of_persons.begin_inorder(); it != tree_of_persons.end_inorder(); ++it)
        {
            CHECK((*it).get_age() == count--);
        }
        count = 10;
        for (auto it = tree_of_persons.begin_preorder(); it != tree_of_persons.end_preorder(); ++it)
        {
            CHECK((*it).get_age() == count--);
        }
        for (auto it = tree_of_persons.begin_postorder(); it != tree_of_persons.end_postorder(); ++it)
        {
            CHECK((*it).get_age() == ++count);
        }
    }

    SUBCASE("preorder")
    {
        BinaryTree<Person> tree_of_persons;
        CHECK_NOTHROW(tree_of_persons.add_root(Person{1}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{1}, Person{2}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{2}, Person{3}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{2}, Person{4}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{4}, Person{5}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{4}, Person{6}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{1}, Person{7}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{7}, Person{8}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{8}, Person{9}));

        CHECK_NOTHROW(cout <<tree_of_persons);

        int count = 1;
        for (auto it = tree_of_persons.begin_preorder(); it != tree_of_persons.end_preorder(); ++it)
        {
            CHECK((*it).get_age() == count++);
        }
        CHECK(count == 10);
    }
    SUBCASE("inorder")
    {
        BinaryTree<Person> tree_of_persons;

        CHECK_NOTHROW(tree_of_persons.add_root(Person{6}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{6}, Person{2}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{2}, Person{1}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{2}, Person{4}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{4}, Person{3}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{4}, Person{5}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{6}, Person{7}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{7}, Person{9}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{9}, Person{8}));

        int count = 1;
        for (auto it = tree_of_persons.begin_inorder(); it != tree_of_persons.end_inorder(); ++it)
        {
            CHECK((*it).get_age() == count++);
        }
        CHECK(count == 10);
    }
    SUBCASE("postorder")
    {
        BinaryTree<Person> tree_of_persons;
        CHECK_NOTHROW(tree_of_persons.add_root(Person{9}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{9}, Person{5}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{5}, Person{1}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{5}, Person{4}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{4}, Person{2}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{4}, Person{3}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{9}, Person{8}));
        CHECK_NOTHROW(tree_of_persons.add_right(Person{8}, Person{7}));
        CHECK_NOTHROW(tree_of_persons.add_left(Person{7}, Person{6}));
        int count = 1;
        for (auto it = tree_of_persons.begin_postorder(); it != tree_of_persons.end_postorder(); ++it)
        {
            CHECK((*it).get_age() == count++);
        }
        CHECK(count == 10);
    }
}