# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Educational data structures and algorithms library for UNMSM (Universidad Nacional Mayor de San Marcos) EDA course. Written in C++17 with heavy use of templates and traits-based design.

## Build Commands

```bash
make          # Build the project (produces ./main executable)
make test     # Build and run the Catch2 test suite
make clean    # Remove object files, executables, and test artifacts
```

The compiler is g++ with `-std=c++17 -Wall -g -pthread`. Source files must be added to `SRCS` in the Makefile.

## Architecture

### Traits Pattern

All containers use a **traits-based polymorphism** pattern instead of virtual inheritance. Traits structs define `value_type`, comparison functors, and other type aliases. Containers are parameterized by these traits:

- `Trait1<T>` for `CArray`
- `AscendingTrait<T>` / `DescendingTrait<T>` for `CLinkedList` (using `std::greater`/`std::less`)
- `TreeTraitAscending<T>` / `TreeTraitDescending<T>` for `CBinaryTree`

### Global Types (`general/types.h`)

Defines project-wide type aliases: `T1` (int), `Size` (int), `ref_type` (long), `ContainerElemType` (int). Every node stores a `value_type` value and a `ref_type` reference ID.

### Container Structure (`containers/`)

- **CArray** (`array.h`) — Dynamic array with forward/backward iterators, resize, sort (uses bubble sort), `Foreach`, `FirstThat`
- **CLinkedList** (`linkedlist.h`) — Sorted singly-linked list with ordered insertion via recursive `InternalInsert`
- **CBinaryTree** (`binarytree.h`) — BST with trait-driven comparison, recursive insert (skeleton: copy/move constructors are TODO)
- **BTree** (`BTree.h` + `BTreePage.h`) — Full B-Tree implementation with Insert, Remove, Search, ForEach, FirstThat
- **CGraph** (`graph.h`) — Graph with `CNode`/`CEdge` using C++20 concepts (`NodeTraitsConcept`, `EdgeTraitsConcept`, `GraphTraitsConcept`), stored in `unordered_map`
- **CHeap** (`heap.h`), **stack** (`stack.h`), **queue** (`queue.h`), **doublelinkedlist** (`doublelinkedlist.h`) — Skeletons/stubs

### Iterator Framework

`GeneralIterator` (`containers/GeneralIterator.h`) is the base iterator. `ArrayForwardIterator` and `ArrayBackwardIterator` extend it. The `Foreach` and `FirstThat` free functions (`foreach.h`) work with any container providing `begin()`/`end()` or directly with iterator pairs. They support variadic extra arguments.

### Algorithms (`algorithms/`)

`sorting.h`/`sorting.cpp` — Recursive bubble sort (`BurbujaRecursivo`). QuickSort and MergeSort are declared but commented out.

### Demo Pattern

Each data structure has a `Demo*()` function (e.g., `DemoArray()`, `DemoBTree()`, `DemoLists()`). The active demo is selected by uncommenting in `main.cpp`. Demo functions are defined in separate `Demo*.cpp` files.

### Comparison Functions (`compareFunc.h`)

Template functions `Mayor` and `Menor` for generic comparison, used as function pointers passed to sort.

## Language Notes

- Code mixes Spanish and English (variable names, comments, function names like `intercambiar`, `Menor`, `Mayor`)
- `graph.h` uses C++20 concepts while the rest of the codebase uses C++17 features (the Makefile only sets `-std=c++17`)
