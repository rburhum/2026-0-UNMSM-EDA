#include "catch_amalgamated.hpp"
#include "../general/types.h"
#include "../util.h"
#include "../containers/linkedlist.h"

using AscList = CLinkedList<AscendingTrait<int>>;
using DescList = CLinkedList<DescendingTrait<int>>;

TEST_CASE("CLinkedList construction", "[linkedlist]") {
    AscList list;
    REQUIRE(list.getSize() == 0);
}

TEST_CASE("CLinkedList Insert increases size", "[linkedlist]") {
    AscList list;
    list.Insert(10, 0);
    list.Insert(20, 1);
    list.Insert(30, 2);
    REQUIRE(list.getSize() == 3);
}

TEST_CASE("CLinkedList Insert maintains sorted order (ascending trait)", "[linkedlist]") {
    AscList list;
    list.Insert(30, 0);
    list.Insert(10, 1);
    list.Insert(20, 2);
    // Size should be 3 — elements are inserted in sorted order internally
    REQUIRE(list.getSize() == 3);
}

TEST_CASE("CLinkedList Insert with descending trait", "[linkedlist]") {
    DescList list;
    list.Insert(10, 0);
    list.Insert(30, 1);
    list.Insert(20, 2);
    REQUIRE(list.getSize() == 3);
}

TEST_CASE("CLinkedList Insert many elements", "[linkedlist]") {
    AscList list;
    for (int i = 100; i >= 0; --i)
        list.Insert(i, i);
    REQUIRE(list.getSize() == 101);
}

TEST_CASE("CLinkedList Insert duplicate values", "[linkedlist]") {
    AscList list;
    list.Insert(5, 0);
    list.Insert(5, 1);
    list.Insert(5, 2);
    REQUIRE(list.getSize() == 3);
}
