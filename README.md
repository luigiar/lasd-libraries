# LASD Data Structures

A C++ template library implementing dynamic data structures with manual memory management.
Developed for the Laboratorio di Algoritmi e Strutture Dati course.

##  Implemented Structures

### Exercise 1: Linear & Sets
* **Vector:** Dynamic array with automatic resizing.
* **List:** Doubly linked list.
* **SetVec:** Ordered set implemented over a Vector (Binary Search).
* **SetLst:** Ordered set implemented over a List.

### Exercise 2: Heaps & Priority Queues
* **Binary Heap:** Max-Heap implementation using implicit vector representation.
* **Priority Queue:** Heap-based structure for priority management.

##  Build & Run

Requires a C++ compiler (G++) and Make.

```bash
# Compile
make

# Run Tests
./main

# Clean
make clean
