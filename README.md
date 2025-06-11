# Sparse Matrix (Linked List Implementation)

This is a small C++ program that constructs a **sparse matrix** using **linked lists** for efficient memory usage. Instead of holding the complete matrix, it holds only non-zero elements with a doubly linked list data structure. Rows and individual row entries are dynamically allocated and linked, demonstrating an implicit, pointer-based approach to sparse data representation.

## Features

- Sparse matrix class with support for setting, getting, and printing values  
- Efficient memory representation using linked lists  
- Basic operations:
  - Element insertion
  - Matrix printing (full and non-zero only)
  - Matrix addition  

## Why This Project?

This mini project was created to explore the logic behind sparse matrix structures using object-oriented programming and linked data structures in C++. It’s suitable for learning:

- Pointer manipulation
- Memory-efficient data structures
- Linked list traversal and operations

## Example Usage

```cpp
SparseMatrix matrix(10, 10);
matrix.set_value(5, 3, 6);
matrix.set_value(7, 8, 2);

matrix.print_matrix();          // Prints full matrix
matrix.print_matrix_nonzero(); // Prints only non-zero values
