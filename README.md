# EDA — Estructuras de Datos y Algoritmos (UNMSM) 2026-0

Biblioteca educativa de estructuras de datos y algoritmos en C++17 para el curso de EDA de la Universidad Nacional Mayor de San Marcos.

## Requisitos previos

- **g++** con soporte para C++17
- **make**
- Linux o macOS (también funciona en WSL)

## Compilar y ejecutar

```bash
make              # Compila el proyecto (produce ./main)
./main            # Ejecuta la demo activa
```

## Tests

Los tests usan [Catch2 v3](https://github.com/catchorg/Catch2) (incluido en el repositorio, no requiere instalación adicional).

```bash
make test                        # Compila y ejecuta todos los tests
./tests/test_runner -v           # Modo verbose
./tests/test_runner "[sorting]"  # Solo tests de sorting
./tests/test_runner "[btree]"    # Solo tests de BTree
```

## Limpiar

```bash
make clean    # Elimina archivos objeto, ejecutable y test runner
```

## Estructura del proyecto

```
.
├── main.cpp                   # Punto de entrada, selecciona la demo activa
├── Makefile                   # Build system
├── general/
│   └── types.h                # Aliases de tipos globales (Size, ref_type, etc.)
├── containers/
│   ├── array.h                # CArray — arreglo dinámico con iteradores
│   ├── linkedlist.h           # CLinkedList — lista enlazada con inserción ordenada
│   ├── binarytree.h           # CBinaryTree — árbol binario de búsqueda
│   ├── BTree.h + BTreePage.h  # BTree — árbol B completo
│   ├── graph.h                # CGraph — grafo con nodos y aristas
│   ├── GeneralIterator.h      # Iterador base para contenedores
│   ├── heap.h                 # CHeap (esqueleto)
│   ├── stack.h                # Stack (esqueleto)
│   ├── queue.h                # Queue (esqueleto)
│   └── doublelinkedlist.h     # Lista doblemente enlazada (esqueleto)
├── algorithms/
│   └── sorting.h / sorting.cpp # BurbujaRecursivo (bubble sort recursivo)
├── foreach.h                  # Foreach y FirstThat genéricos
├── compareFunc.h              # Funciones de comparación Mayor y Menor
├── tests/
│   ├── catch_amalgamated.*    # Framework Catch2 v3 (amalgamado)
│   ├── test_sorting.cpp       # Tests de algoritmos de ordenamiento
│   ├── test_array.cpp         # Tests de CArray
│   ├── test_btree.cpp         # Tests de BTree
│   ├── test_linkedlist.cpp    # Tests de CLinkedList
│   └── test_binarytree.cpp    # Tests de CBinaryTree
└── Demo*.cpp                  # Funciones de demostración por estructura
```

## Patrón de diseño: Traits

En lugar de herencia virtual, todos los contenedores usan **polimorfismo basado en traits**. Un struct de traits define los tipos y functores que el contenedor necesita:

```cpp
// Ejemplo: traits para lista enlazada ascendente
template <typename T>
struct AscendingTrait : public ListTrait<T, std::greater<T>> {};

// El contenedor se parametriza con el trait
CLinkedList<AscendingTrait<int>> lista;
```

Cada contenedor lee del trait:
- `value_type` — el tipo de dato almacenado
- Functores de comparación (`Func`, `CompareFunc`) — controlan el orden

Traits disponibles:
| Contenedor | Traits |
|---|---|
| `CArray` | `Trait1<T>` |
| `CLinkedList` | `AscendingTrait<T>`, `DescendingTrait<T>` |
| `CBinaryTree` | `TreeTraitAscending<T>`, `TreeTraitDescending<T>` |

## Referencia rápida de contenedores

### CArray
Arreglo dinámico con redimensionamiento automático, iteradores forward/backward, `sort()`, `Foreach()` y `FirstThat()`.

### CLinkedList
Lista enlazada simple con inserción ordenada recursiva (`InternalInsert`).

### CBinaryTree
Árbol binario de búsqueda con comparación configurable vía traits. El truco `comp(val, node->GetValue())` retorna 0 o 1, indexando directamente `m_pChild[path]` para elegir hijo izquierdo o derecho.

### BTree
Árbol B completo con Insert, Remove, Search, ForEach y FirstThat. Soporta redistribución, split y merge.

### CGraph
Grafo con nodos y aristas usando C++20 concepts.
