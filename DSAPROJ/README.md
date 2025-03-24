# Grid Search Algorithms
# Author: Alex Brooks
## Overview

The **Grid Search Algorithms** project implements several path-finding algorithms on a 2D grid:
- **Breadth-First Search (BFS)**
- **Depth-First Search (DFS)**
- **Iterative Deepening Depth-First Search (IDDFS)**

The grid is represented as a 2D vector of integers where a cell with the value `0` is free and a cell with the value `1` is forbidden. The project features an interactive menu that allows you to:
- Set grid dimensions.
- Define the start and goal states.
- Mark forbidden squares.
- Run one of the search algorithms to find a path from the start to the goal.
- Display the grid and the resulting path.

## Features

- **BFS**: Finds the shortest path (in terms of number of moves) on the grid.
- **DFS**: Explores the grid deeply before backtracking.
- **IDDFS**: Iteratively deepens the search, combining the benefits of DFS with breadth-wise progression.
- Interactive console menu for configuring and executing the search.
- Visualization of the grid and the computed path.

## Files

- `main.cpp`  
  Contains the main interactive menu and overall program logic.
  
- `BFSSearch.hpp` & `BFSSearch.cpp`  
  Declaration and implementation of the Breadth-First Search (BFS) algorithm.
  
- `DFSSearch.hpp` & `DFSSearch.cpp`  
  Declaration and implementation of the Depth-First Search (DFS) algorithm.
  
- `IDDFSSearch.hpp` & `IDDFSSearch.cpp`  
  Declaration and implementation of the Iterative Deepening Depth-First Search (IDDFS) algorithm.
  
- `README.md`  
  This file, providing an overview and instructions for the project.

## Prerequisites

- A C++ compiler supporting C++11 (e.g., GCC, Clang, MSVC).
- (Optional) [Doxygen](https://www.doxygen.nl/index.html) for generating documentation.

## Compilation

To compile the project from the command line, use make Project


