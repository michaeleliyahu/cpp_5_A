#include "doctest.h"
#include "BinaryTree.hpp"
#include <set>
#include <sstream>
using namespace ariel;
using namespace std;

const int ROOT = 1;
const int FIR_LEFT = 2;
const int FIR_RIGHT = 5;
const int RIGHT_CHILD_LEFT = 4;
const int LEFT_CHILD_LEFT = 3;
const int DOUBLE = 2;
const int VAL = 0;

/*

case 1: check all add function
        -based on that begin function works right
        -the first subcase check begin function also

case 2: check all operator
        (based on that add function works right)

case 3: check iterator  
        (based on that add and operator work right)      

*/

TEST_CASE("case 1:  add root/right/left")
{
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(ROOT)
        .add_left(ROOT, FIR_LEFT)
        .add_right(ROOT, FIR_RIGHT)
        .add_right(FIR_LEFT, RIGHT_CHILD_LEFT);
    //       1
    //      / \
    //     2   5
    //      \
    //       4

    //after build tree, check is value
    SUBCASE("first value(this test can field also becuse begin function)")
    {
        auto first_pre = tree_of_ints.begin_preorder(); //preorder take the root first (1)
        CHECK_EQ(*first_pre, ROOT);

        auto first_in = tree_of_ints.begin_inorder(); // inorder take extremely left value (2)
        CHECK_EQ(*first_in, FIR_LEFT);

        auto first_post = tree_of_ints.begin_postorder(); // postorder take from extremely left is right child (4)
        CHECK_EQ(*first_post, RIGHT_CHILD_LEFT);
    }

    //change the value in tree and check if it changed currect
    SUBCASE("change value")
    {
        tree_of_ints.add_right(FIR_LEFT, RIGHT_CHILD_LEFT * DOUBLE); //change 4->8
        //       1
        //      / \
        //     2   5
        //      \
        //       8
        auto first_post = tree_of_ints.begin_postorder(); // postorder take from extremely left is right child (8)
        CHECK_EQ(*first_post, RIGHT_CHILD_LEFT * DOUBLE);

        tree_of_ints.add_right(ROOT, FIR_LEFT * DOUBLE); //change 2->4
        auto first_in = tree_of_ints.begin_inorder();    // inorder take extremely left value (4)
        CHECK_EQ(*first_in, FIR_LEFT * DOUBLE);

        tree_of_ints.add_root(ROOT * DOUBLE);
        auto first_pre = tree_of_ints.begin_preorder(); //preorder take the root first (2)
        CHECK_EQ(*first_pre, ROOT * DOUBLE);
    }
}

//check operator for preorder/ inorder / postorder /defult
TEST_CASE("check operator for int")
{
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(ROOT)
        .add_left(ROOT, FIR_LEFT)
        .add_right(ROOT, FIR_RIGHT);

    //       1
    //      / \
    //     2   5

    SUBCASE("check operator preorder")
    {
        auto it_tree = tree_of_ints.begin_preorder();

        CHECK_EQ(*it_tree, ROOT); //*

        CHECK(*it_tree != VAL); //!=

        ++it_tree;
        CHECK_EQ(*it_tree, FIR_LEFT); //++
    }
    SUBCASE("check operator inorder")
    {
        auto it_tree = tree_of_ints.begin_inorder();

        CHECK_EQ(*it_tree, FIR_LEFT); //*

        CHECK(*it_tree != VAL); //!=

        ++it_tree;
        CHECK_EQ(*it_tree, ROOT); //++
    }
    SUBCASE("check operator postorder")
    {
        auto it_tree = tree_of_ints.begin_postorder();

        CHECK_EQ(*it_tree, FIR_LEFT); //*

        CHECK(*it_tree != VAL); //!=

        ++it_tree;
        CHECK_EQ(*it_tree, FIR_RIGHT); //++
    }
    SUBCASE("check operator defult")
    {
        auto it_tree = tree_of_ints.begin();

        CHECK_EQ(*it_tree, FIR_LEFT); //*

        CHECK(*it_tree != VAL); //!=

        ++it_tree;
        CHECK_EQ(*it_tree, ROOT); //++
    }
}

//check iterator for each one of preorder/inorder/postorder/defult
TEST_CASE("check iterator fot int")
{
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(ROOT)
        .add_left(ROOT, FIR_LEFT)
        .add_left(FIR_LEFT, LEFT_CHILD_LEFT)
        .add_right(FIR_LEFT, RIGHT_CHILD_LEFT)
        .add_right(ROOT, FIR_RIGHT);

    //       1
    //      / \
    //     2   5
    //    / \
    //   3   4

    //root(1)->left(2)->left(3)->right(4)->right(5)
    SUBCASE("preorder")
    {
        set<int> temp = {1, 2, 3, 4, 5};
        auto it_temp = temp.begin();
        for (auto it_tree = tree_of_ints.begin_preorder(); it_tree != tree_of_ints.end_preorder(); ++it_tree)
        {
            CHECK_EQ(*it_tree, *it_temp);
            it_temp++;

        } // check: 1 2 3 4 5
    }
    //left(3)->root(2)->right(4)->root(1)->right(5)
    SUBCASE("inorder")
    {
        set<int> temp = {4, 2, 5, 1, 3};
        auto it_temp = temp.begin();
        for (auto it_tree = tree_of_ints.begin_inorder(); it_tree != tree_of_ints.end_inorder(); ++it_tree)
        {
            CHECK_EQ(*it_tree, *it_temp);
            it_temp++;

        } // check: 3 2 4 1 5
    }
    //left(3)->right(4)->root(2)->right(5)->root(1)
    SUBCASE("postorder")
    {
        set<int> temp = {4, 5, 2, 3, 1};
        auto it_temp = temp.begin();
        for (auto it_tree = tree_of_ints.begin_postorder(); it_tree != tree_of_ints.end_postorder(); ++it_tree)
        {
            CHECK_EQ(*it_tree, *it_temp);
            it_temp++;
        } // check: 3 4 2 5 1
    }
}
//check operator for preorder/ inorder / postorder /defult
TEST_CASE("check operator for string")
{
    BinaryTree<string> tree_of_strings;
    tree_of_strings.add_root("1")
        .add_left("1", "2")
        .add_right("1", "5");

    //       1
    //      / \
    //     2   5

    SUBCASE("check operator preorder")
    {
        auto it_tree = tree_of_strings.begin_preorder();

        CHECK_EQ(*it_tree, "1"); //*

        CHECK(*it_tree != "0"); //!=

        CHECK_EQ(it_tree->size(), 1); //->
        ++it_tree;
        CHECK_EQ(*it_tree, "2"); //++
    }
    SUBCASE("check operator inorder")
    {
        auto it_tree = tree_of_strings.begin_inorder();

        CHECK_EQ(*it_tree, "2"); //*

        CHECK(*it_tree != "0"); //!=

        CHECK_EQ(it_tree->size(), 1); //->

        ++it_tree;
        CHECK_EQ(*it_tree, "1"); //++
    }
    SUBCASE("check operator postorder")
    {
        auto it_tree = tree_of_strings.begin_postorder();

        CHECK_EQ(*it_tree, "2"); //*

        CHECK(*it_tree != "0"); //!=

        CHECK_EQ(it_tree->size(), 1); //->

        ++it_tree;
        CHECK_EQ(*it_tree, "5"); //++
    }
    SUBCASE("check operator defult")
    {
        auto it_tree = tree_of_strings.begin();

        CHECK_EQ(*it_tree, "2"); //*

        CHECK(*it_tree != "0"); //!=

        CHECK_EQ(it_tree->size(), 1); //->

        ++it_tree;
        CHECK_EQ(*it_tree, "1"); //++
    }
}

//check iterator for each one of preorder/inorder/postorder/defult
TEST_CASE("check iterator fot string")
{
    BinaryTree<string> tree_of_strings;
    tree_of_strings.add_root("1")
        .add_left("1", "2")
        .add_left("2", "3")
        .add_right("2", "4")
        .add_right("1", "5");

    //       1
    //      / \
    //     2   5
    //    / \
    //   3   4

    //root(1)->left(2)->left(3)->right(4)->right(5)
    SUBCASE("preorder")
    {
        set<string> temp = {"1", "2", "3", "4", "5"};
        auto it_temp = temp.begin();
        for (auto it_tree = tree_of_strings.begin_preorder(); it_tree != tree_of_strings.end_preorder(); ++it_tree)
        {
            CHECK_EQ(*it_tree, *it_temp);
            it_temp++;

        } // check: 1 2 3 4 5
    }

    //left(3)->root(2)->right(4)->root(1)->right(5)
    SUBCASE("inorder")
    {
        set<string> temp = {"3", "2", "4", "1", "5"};
        auto it_temp = temp.begin();
        for (auto it_tree = tree_of_strings.begin_inorder(); it_tree != tree_of_strings.end_inorder(); ++it_tree)
        {
            CHECK_EQ(*it_tree, *it_temp);
            it_temp++;
        } // check: 3 2 4 1 5
    }

    //left(3)->right(4)->root(2)->right(5)->root(1)
    SUBCASE("postorder")
    {
        set<string> temp = {"3", "4", "2", "5", "1"};
        auto it_temp = temp.begin();
        for (auto it_tree = tree_of_strings.begin_postorder(); it_tree != tree_of_strings.end_postorder(); ++it_tree)
        {
            CHECK_EQ(*it_tree, *it_temp);
            it_temp++;
        } // check: 3 4 2 5 1
    }
}
TEST_CASE("check operator stream for string")
{
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(ROOT)
        .add_left(ROOT, FIR_LEFT)
        .add_right(ROOT, FIR_RIGHT);

    //       1
    //      / \
    //     2   5

    auto it_temp = tree_of_ints.begin();
    stringstream first;
    stringstream sec;
    first << *it_temp;
    CHECK(first.str() == "2");

    ++it_temp;
    sec << *it_temp;
    CHECK(sec.str() == "1");
}