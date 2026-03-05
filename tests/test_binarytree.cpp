#include "catch_amalgamated.hpp"
#include "../general/types.h"
#include "../util.h"
#include "../containers/binarytree.h"

using AscBST = CBinaryTree<TreeTraitAscending<int>>;
using DescBST = CBinaryTree<TreeTraitDescending<int>>;

TEST_CASE("CBinaryTree construction", "[binarytree]") {
    AscBST tree;
    // Construction should succeed without issues
    REQUIRE(true);
}

TEST_CASE("CBinaryTree Insert does not crash (ascending)", "[binarytree]") {
    AscBST tree;
    tree.Insert(50, 0);
    tree.Insert(30, 1);
    tree.Insert(70, 2);
    tree.Insert(20, 3);
    tree.Insert(40, 4);
    REQUIRE(true);
}

TEST_CASE("CBinaryTree Insert does not crash (descending)", "[binarytree]") {
    DescBST tree;
    tree.Insert(50, 0);
    tree.Insert(30, 1);
    tree.Insert(70, 2);
    tree.Insert(20, 3);
    tree.Insert(40, 4);
    REQUIRE(true);
}

TEST_CASE("CBinaryTree Insert many elements", "[binarytree]") {
    AscBST tree;
    for (int i = 0; i < 100; ++i)
        tree.Insert(i, i);
    REQUIRE(true);
}

TEST_CASE("CBinaryTree Insert with string type", "[binarytree]") {
    CBinaryTree<TreeTraitAscending<std::string>> tree;
    tree.Insert("hello", 0);
    tree.Insert("world", 1);
    tree.Insert("abc", 2);
    REQUIRE(true);
}
