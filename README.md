# Sparse Array & Matrix (Linked List Implementation)

This is a small C++ project that first builds a **sparse array** using a linked list, and then uses it as the foundation to implement a **sparse matrix**. These structures store only non-zero elements to save memory, using pointer-based linked lists for dynamic and efficient data representation.

## Features

- Sparse array class for storing non-zero values at specific indices
- Sparse matrix class built using sparse arrays (array of linked lists)
- Supports:
  - Setting and getting values
  - Printing full and non-zero-only versions
  - Matrix addition

## Why This Project?

This mini project was designed to explore sparse data structures using object-oriented programming in C++. It’s a good exercise for learning:

- Pointer-based data structures
- Memory efficiency in sparse data
- Linked list operations and traversal

## Example Usage

```cpp
SparseMatrix matrix(10, 10);
matrix.set_value(5, 3, 6);
matrix.set_value(7, 8, 2);

matrix.print_matrix();          // Prints full matrix
matrix.print_matrix_nonzero(); // Prints only non-zero values
