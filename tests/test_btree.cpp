#include "catch_amalgamated.hpp"
#include "../containers/BTree.h"

TEST_CASE("BTree construction", "[btree]") {
    BTree<int> tree(3);
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.height() == 1);
    REQUIRE(tree.GetOrder() == 3);
}

TEST_CASE("BTree Insert and Search", "[btree]") {
    BTree<int> tree(3);
    REQUIRE(tree.Insert(10, 100));
    REQUIRE(tree.Insert(20, 200));
    REQUIRE(tree.Insert(30, 300));

    REQUIRE(tree.size() == 3);
    REQUIRE(tree.Search(10) == 100);
    REQUIRE(tree.Search(20) == 200);
    REQUIRE(tree.Search(30) == 300);
}

TEST_CASE("BTree Search returns -1 for missing key", "[btree]") {
    BTree<int> tree(3);
    tree.Insert(10, 100);
    REQUIRE(tree.Search(999) == -1);
}

TEST_CASE("BTree rejects duplicate keys", "[btree]") {
    BTree<int> tree(3, true); // unique=true
    REQUIRE(tree.Insert(10, 100));
    REQUIRE_FALSE(tree.Insert(10, 200));
    REQUIRE(tree.size() == 1);
}

TEST_CASE("BTree height grows with many insertions", "[btree]") {
    BTree<int> tree(3);
    long initial_height = tree.height();
    for (int i = 0; i < 100; ++i)
        tree.Insert(i, i * 10);
    REQUIRE(tree.size() == 100);
    REQUIRE(tree.height() > initial_height);
}

TEST_CASE("BTree Remove", "[btree]") {
    BTree<int> tree(3);
    tree.Insert(10, 100);
    tree.Insert(20, 200);
    tree.Insert(30, 300);

    REQUIRE(tree.Remove(20, 200));
    REQUIRE(tree.size() == 2);
    REQUIRE(tree.Search(20) == -1);
    REQUIRE(tree.Search(10) == 100);
    REQUIRE(tree.Search(30) == 300);
}

TEST_CASE("BTree Remove existing keys only", "[btree]") {
    BTree<int> tree(3);
    for (int i = 0; i < 20; ++i)
        tree.Insert(i, i * 10);
    REQUIRE(tree.size() == 20);
    REQUIRE(tree.Remove(10, 100));
    REQUIRE(tree.size() == 19);
    REQUIRE(tree.Search(10) == -1);
}

TEST_CASE("BTree with string keys", "[btree]") {
    BTree<std::string> tree(3);
    tree.Insert("banana", 1);
    tree.Insert("apple", 2);
    tree.Insert("cherry", 3);

    REQUIRE(tree.size() == 3);
    REQUIRE(tree.Search("apple") == 2);
    REQUIRE(tree.Search("banana") == 1);
    REQUIRE(tree.Search("cherry") == 3);
}

TEST_CASE("BTree bulk insert and search", "[btree]") {
    BTree<int> tree(3);
    for (int i = 0; i < 50; ++i)
        tree.Insert(i, i * 100);

    for (int i = 0; i < 50; ++i)
        REQUIRE(tree.Search(i) == i * 100);
}

TEST_CASE("BTree bulk remove", "[btree]") {
    BTree<int> tree(3);
    for (int i = 0; i < 30; ++i)
        tree.Insert(i, i);

    for (int i = 0; i < 30; i += 2)
        REQUIRE(tree.Remove(i, i));

    REQUIRE(tree.size() == 15);
    for (int i = 1; i < 30; i += 2)
        REQUIRE(tree.Search(i) == i);
}
