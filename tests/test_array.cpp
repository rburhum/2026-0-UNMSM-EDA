#include "catch_amalgamated.hpp"
#include "../general/types.h"
#include "../compareFunc.h"
#include "../util.h"
#include "../containers/array.h"

using IntArray = CArray<Trait1<int>>;

TEST_CASE("CArray construction", "[array]") {
    IntArray arr(10);
    // A fresh CArray has size = m_last + 1 = 0 + 1 = 1 (quirk of the implementation)
    REQUIRE(arr.getSize() == 1);
}

TEST_CASE("CArray push_back increases size", "[array]") {
    IntArray arr(10);
    arr.push_back(42, 0);
    arr.push_back(99, 1);
    // After 2 push_backs: m_last starts at 0, first push sets m_data[0] and m_last becomes 1,
    // second push sets m_data[1] and m_last becomes 2. getSize() = m_last + 1 = 3.
    REQUIRE(arr.getSize() == 3);
}

TEST_CASE("CArray operator[] stores and retrieves values", "[array]") {
    IntArray arr(10);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    REQUIRE(arr[0] == 10);
    REQUIRE(arr[1] == 20);
    REQUIRE(arr[2] == 30);
}

TEST_CASE("CArray auto-resizes when capacity exceeded", "[array]") {
    IntArray arr(2);
    arr[0] = 1;
    arr[1] = 2;
    // Accessing beyond capacity triggers resize
    arr[5] = 50;
    REQUIRE(arr[5] == 50);
}

TEST_CASE("CArray sort with Mayor produces descending order", "[array]") {
    IntArray arr(10);
    arr.push_back(3, 0);
    arr.push_back(1, 1);
    arr.push_back(4, 2);
    arr.push_back(1, 3);
    arr.push_back(5, 4);

    arr.sort(Mayor);
    // Mayor(a,b) returns !(a==b) && !(a<b) which is a>b
    // BurbujaRecursivo pushes the "first-by-comparator" element to front
    // With Mayor: descending order
    REQUIRE(arr[0] >= arr[1]);
    REQUIRE(arr[1] >= arr[2]);
}

TEST_CASE("CArray sort with Menor produces ascending order", "[array]") {
    IntArray arr(10);
    arr.push_back(9, 0);
    arr.push_back(2, 1);
    arr.push_back(7, 2);

    arr.sort(Menor);
    REQUIRE(arr[0] <= arr[1]);
    REQUIRE(arr[1] <= arr[2]);
}

TEST_CASE("CArray forward iterator", "[array]") {
    IntArray arr(10);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    std::vector<int> collected;
    for (auto it = arr.begin(); it != arr.end(); ++it)
        collected.push_back(*it);

    REQUIRE(collected.size() == static_cast<size_t>(arr.getSize()));
    REQUIRE(collected[0] == 10);
    REQUIRE(collected[1] == 20);
    REQUIRE(collected[2] == 30);
}

TEST_CASE("CArray backward iterator", "[array]") {
    IntArray arr(10);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    std::vector<int> collected;
    for (auto it = arr.rbegin(); it != arr.rend(); ++it)
        collected.push_back(*it);

    REQUIRE(collected[0] == 30);
    REQUIRE(collected[1] == 20);
    REQUIRE(collected[2] == 10);
}

static void collectValue(int &val, std::vector<int> *out) {
    out->push_back(val);
}

TEST_CASE("CArray Foreach", "[array]") {
    IntArray arr(10);
    arr[0] = 5;
    arr[1] = 15;
    arr[2] = 25;

    std::vector<int> collected;
    arr.Foreach(collectValue, &collected);

    REQUIRE(collected.size() == static_cast<size_t>(arr.getSize()));
    REQUIRE(collected[0] == 5);
}

static bool isGreaterThan(int &val, int *threshold) {
    return val > *threshold;
}

TEST_CASE("CArray FirstThat", "[array]") {
    IntArray arr(10);
    arr[0] = 5;
    arr[1] = 15;
    arr[2] = 25;

    int threshold = 10;
    auto it = arr.FirstThat(isGreaterThan, &threshold);
    REQUIRE(*it == 15);
}
