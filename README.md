# Knowledge Graph in C

An in-memory knowledge graph and query engine implemented in C as an academic project for the **Algorithms Design** course at the Faculty of Automatic Control and Computers, National University of Science and Technology POLITEHNICA Bucharest (2025-2026).

The application loads entities and weighted relationships from CSV files, represents them as a directed graph, indexes entities by name, and processes graph queries from a FIFO queue.

## Highlights

- Directed, weighted graph represented with adjacency lists
- Dynamically allocated entities, graph nodes, edges, queues, and heap storage
- Binary Search Tree index for entity lookup by name
- Breadth-First Search for reachability and path reconstruction
- Dijkstra's algorithm with a custom binary min-heap
- Five supported query types: `EXISTS`, `EDGE`, `NEIGHBORS`, `PATH`, and `DIJKSTRA`
- Modular C11 implementation with separate interfaces and source files
- Four-stage public test suite compiled with warnings treated as errors

## Supported queries

| Query | Purpose | Main technique |
|---|---|---|
| `EXISTS <entity>` | Checks whether an entity exists | BST lookup |
| `EDGE <source> <destination>` | Checks for a direct relationship | BST lookup and adjacency-list scan |
| `NEIGHBORS <entity>` | Lists direct outgoing neighbors | Adjacency-list traversal |
| `PATH <source> <destination>` | Finds a path with the fewest edges | BFS and parent reconstruction |
| `DIJKSTRA <source> <destination>` | Finds a minimum-cost path | Dijkstra and binary min-heap |

## Data structures

| Component | Implementation | Role |
|---|---|---|
| Graph | Dynamic array of nodes with linked adjacency lists | Stores entities and directed weighted relationships |
| Entity index | Unbalanced Binary Search Tree | Locates graph nodes by entity name |
| Query queue | Linked FIFO queue | Preserves query input order |
| BFS queue | Dynamic integer array with head and tail indices | Traverses the graph level by level |
| Dijkstra frontier | Dynamic binary min-heap | Extracts the node with the lowest known distance |

## Repository structure

```text
.
├── include/            # Public interfaces for each module
├── resources/          # Original academic project specification
├── src/                # C implementations
├── tests/public/       # Public inputs, expected outputs, and test harnesses
├── LICENSE             # MIT license retained from the starter repository
├── Makefile
└── README.md
```

## Build and run

Requirements:

- A C11-compatible compiler such as GCC or Clang
- GNU Make
- A POSIX-compatible environment such as Linux, macOS, or WSL

Build the command-line application:

```bash
make build/student_kg
```

Run it with entity, relationship, and query files:

```bash
./build/student_kg \
  tests/public/pas4/entitati.csv \
  tests/public/pas4/relatii.csv \
  tests/public/pas4/interogari.txt
```

Optional debug output can be enabled with `--debug`:

```bash
./build/student_kg <entities.csv> <relationships.csv> <queries.txt> --debug
```

## Testing

Run all four public test stages:

```bash
make public-test
```

Expected result:

```text
[OK] public_pas1
[OK] public_pas2
[OK] public_pas3
[OK] public_pas4
```

The build uses `-Wall -Wextra -Werror`, so compiler warnings fail the build.

## Complexity

Let `n` be the number of graph nodes, `m` the number of directed edges, and `deg(x)` the out-degree of node `x`.

| Operation | Time complexity | Auxiliary space |
|---|---:|---:|
| `EXISTS x` | Average `O(log n)`, worst `O(n)` | `O(1)` excluding BST storage |
| `EDGE x y` | Average `O(log n + deg(x))` | `O(1)` |
| `NEIGHBORS x` | Average `O(log n + deg(x))` | `O(1)` excluding output |
| `PATH x y` | `O(n + m)` | `O(n)` |
| `DIJKSTRA x y` | `O(mn + n log n)` worst case in the current implementation | `O(n)` |

The BST is intentionally unbalanced, as allowed by the assignment. The min-heap supports logarithmic insertion and extraction; its current `decrease-key` operation first locates a node through a linear heap scan.

## Project provenance and contribution

This repository originated from a professor-provided GitHub Classroom starter project distributed under the MIT License. The starter included the module interfaces, application entry point and file-ingestion pipeline, Makefile, public test harnesses, sample data, and project specification.

**My implementation work:**

- Completed the entity lifecycle and type-conversion operations in `src/entity.c`
- Implemented the directed weighted graph and adjacency-list operations in `src/graph.c`
- Implemented BST insertion, search, traversal, and cleanup in `src/bst.c`
- Implemented the linked FIFO query queue in `src/queue.c`
- Implemented the dynamic binary min-heap in `src/heap.c`
- Implemented query parsing, BFS path finding, Dijkstra shortest paths, and query dispatching in `src/query.c`
- Added the implementation documentation and complexity analysis

This distinction is stated explicitly so the repository accurately represents both the supplied academic scaffold and my own work.

## License

The original MIT License and copyright notice are retained in [`LICENSE`](LICENSE).
