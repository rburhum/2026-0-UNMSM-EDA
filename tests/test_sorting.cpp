#include "catch_amalgamated.hpp"
#include "../general/types.h"
#include "../compareFunc.h"
#include "../util.h"
#include "../algorithms/sorting.h"

TEST_CASE("BurbujaRecursivo sorts integers ascending with Menor", "[sorting]") {
    int arr[] = {5, 3, 8, 1, 2};
    BurbujaRecursivo(arr, 5, Menor<int>);
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 3);
    REQUIRE(arr[3] == 5);
    REQUIRE(arr[4] == 8);
}

TEST_CASE("BurbujaRecursivo sorts integers descending with Mayor", "[sorting]") {
    int arr[] = {5, 3, 8, 1, 2};
    BurbujaRecursivo(arr, 5, Mayor<int>);
    REQUIRE(arr[0] == 8);
    REQUIRE(arr[1] == 5);
    REQUIRE(arr[2] == 3);
    REQUIRE(arr[3] == 2);
    REQUIRE(arr[4] == 1);
}

TEST_CASE("BurbujaRecursivo handles single element", "[sorting]") {
    int arr[] = {42};
    BurbujaRecursivo(arr, 1, Menor<int>);
    REQUIRE(arr[0] == 42);
}

TEST_CASE("BurbujaRecursivo handles empty array", "[sorting]") {
    int arr[] = {0}; // dummy, n=0
    BurbujaRecursivo(arr, 0, Menor<int>);
    REQUIRE(arr[0] == 0); // untouched
}

TEST_CASE("BurbujaRecursivo sorts strings", "[sorting]") {
    std::string arr[] = {"banana", "apple", "cherry"};
    BurbujaRecursivo(arr, 3, Menor<std::string>);
    REQUIRE(arr[0] == "apple");
    REQUIRE(arr[1] == "banana");
    REQUIRE(arr[2] == "cherry");
}

TEST_CASE("BurbujaRecursivo handles already sorted array", "[sorting]") {
    int arr[] = {1, 2, 3, 4, 5};
    BurbujaRecursivo(arr, 5, Menor<int>);
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[4] == 5);
}

TEST_CASE("BurbujaRecursivo handles reverse sorted array", "[sorting]") {
    int arr[] = {5, 4, 3, 2, 1};
    BurbujaRecursivo(arr, 5, Menor<int>);
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[4] == 5);
}
