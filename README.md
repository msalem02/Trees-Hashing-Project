# Trees and Hashing Project  
### Advanced Data Structures Implementation and Applications in C / C++

---

## 1. Overview

The **Trees and Hashing Project** focuses on the design and implementation of **non-linear data structures**, specifically **Binary Trees**, **Binary Search Trees (BSTs)**, and **Hash Tables**.  
It demonstrates efficient data organization and retrieval mechanisms, essential for optimizing time and space complexity in advanced computational systems.

This project serves as a comprehensive academic and practical resource for understanding hierarchical data structures, hashing algorithms, and their applications in real-world computing tasks such as indexing, searching, and symbol table management.

---

## 2. Objectives

- Implement **Binary Tree**, **Binary Search Tree**, and **Hash Table** structures from scratch.  
- Understand the theory and practice of **tree traversal**, **balancing**, and **hash collision handling**.  
- Perform key operations: **insertion**, **deletion**, **search**, **traversal**, and **balancing**.  
- Explore **hashing techniques** (e.g., division method, multiplication method).  
- Implement **collision resolution** strategies (open addressing, chaining).  
- Provide a clear modular structure for code readability and extensibility.

---

## 3. Project Structure

```
Trees-Hashing-Project/
│
├── src/
│   ├── binary_tree.c / .cpp          # Basic binary tree creation and traversal
│   ├── bst.c / .cpp                  # Binary Search Tree implementation
│   ├── hashing.c / .cpp              # Hash table implementation
│   ├── utils.c / .cpp                # Helper and utility functions
│   ├── menu.c / .cpp                 # CLI and user interface
│   └── main.c / main.cpp             # Main driver program
│
├── include/
│   ├── tree.h                        # Structure definitions and function prototypes
│   ├── bst.h
│   ├── hashing.h
│   ├── utils.h
│   └── menu.h
│
├── tests/
│   ├── test_bst.txt
│   ├── test_hash.txt
│   └── run_tests.sh
│
├── Makefile / CMakeLists.txt         # Build automation
├── input.txt                         # Sample command input file
├── output.txt                        # Example program output
└── README.md
```

---

## 4. Core Data Structures

### 4.1 Binary Tree Node
```c
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
```

### 4.2 Hash Table Node (Chaining)
```c
struct HashNode {
    int key;
    int value;
    struct HashNode* next;
};
```

---

## 5. Implemented Operations

### Binary Tree / BST Operations
| Operation | Description | Time Complexity |
|------------|--------------|-----------------|
| Insert() | Inserts new node based on value | O(log n) avg / O(n) worst |
| Delete() | Removes specified node | O(log n) avg / O(n) worst |
| Search() | Finds node by key | O(log n) avg / O(n) worst |
| Traversals() | Preorder, Inorder, Postorder, Level-order | O(n) |
| Height() | Returns tree height | O(n) |
| CountNodes() | Returns total nodes | O(n) |
| FindMin/FindMax() | Retrieves smallest/largest key | O(log n) |

### Hash Table Operations
| Operation | Description | Time Complexity |
|------------|--------------|-----------------|
| Insert() | Insert key-value pair | O(1) avg |
| Search() | Retrieve value by key | O(1) avg |
| Delete() | Remove key-value pair | O(1) avg |
| Display() | Print all entries | O(n) |
| HashFunction() | Computes hash index | O(1) |

---

## 6. Hashing Techniques

### Division Method
```c
index = key % table_size;
```

### Multiplication Method
```c
index = floor(table_size * (key * A % 1));  // A = constant between 0 and 1
```

### Collision Resolution
- **Chaining:** Linked lists at each bucket.  
- **Open Addressing:** Linear or quadratic probing.  
- **Double Hashing:** Secondary hash for offset computation.

---

## 7. Traversal Algorithms

### 7.1 Preorder (Root → Left → Right)
Used for creating prefix expressions.

### 7.2 Inorder (Left → Root → Right)
Produces sorted output for BST.

### 7.3 Postorder (Left → Right → Root)
Used for deleting the tree or postfix evaluation.

### 7.4 Level Order (Breadth-First Traversal)
Utilizes a queue for layer-wise processing.

---

## 8. Sample Menu (Interactive CLI)

```
========= TREE & HASHING MENU =========
1. Insert into Binary Tree
2. Insert into BST
3. Delete from BST
4. Search in BST
5. Traverse Tree (Pre/In/Post/Level)
6. Create Hash Table
7. Insert Key into Hash Table
8. Search Key in Hash Table
9. Display Hash Table
10. Exit
=======================================
Enter your choice:
```

**Example Execution:**
```
Enter your choice: 2
Enter value: 15
Node inserted successfully in BST.

Enter your choice: 5
Inorder Traversal: 5 10 15 20 30
```

---

## 9. Input/Output Examples

### Input (input.txt)
```
INSERT_TREE 10
INSERT_TREE 5
INSERT_TREE 20
INORDER
CREATE_HASH 10
INSERT_HASH 101 500
INSERT_HASH 102 600
DISPLAY_HASH
```

### Output (output.txt)
```
Binary Tree Inorder: 5 10 20
Hash Table:
[1] -> (101, 500)
[2] -> (102, 600)
```

---

## 10. Algorithmic Insights

| Concept | Description |
|----------|-------------|
| Recursive traversal | Core logic for depth-first tree operations |
| Dynamic allocation | Efficient node creation at runtime |
| Hashing | Converts key to table index for constant-time lookup |
| Collision handling | Ensures unique placement without data loss |
| Balancing (future work) | Keeps tree height minimal for performance |

---

## 11. Build & Run Instructions

### Using GCC
```bash
gcc src/*.c -o trees_hash_app
./trees_hash_app
```

### Using Makefile
```bash
make
./trees_hash_app
```

### Using CMake
```bash
mkdir build
cd build
cmake ..
make
./trees_hash_app
```

---

## 12. Testing

- Automated test suite in `tests/` directory.  
- Manual test commands supported via interactive menu.  
- Validates insert, search, and traversal consistency.  

Example:
```bash
./trees_hash_app < tests/test_bst.txt
```

---

## 13. Error Handling

- Prevents insertion of duplicate BST keys.  
- Handles hash collisions gracefully (chaining / open addressing).  
- Detects null pointers and memory allocation errors.  
- Ensures safe deletion and memory deallocation.  

---

## 14. Educational Insights

This project reinforces fundamental principles of data organization and algorithm optimization. Students learn to:

- Compare linear vs. non-linear structures.  
- Apply recursive logic to tree-based algorithms.  
- Understand hashing’s impact on time complexity.  
- Implement practical solutions for memory management.  

---

## 15. Future Enhancements

- Implement **AVL** or **Red-Black Tree** balancing.  
- Add **generic key-value template** (C++).  
- Expand hashing to support **string keys** and **custom hash functions**.  
- Integrate file-based persistence.  
- Build visualization for tree and hash operations.  

---

## 16. Author

Mohammed Salem  
Email: salemmohamad926@gmail.com  
LinkedIn: https://www.linkedin.com/in/msalem02  
GitHub: https://github.com/msalem02  

---

## 17. License

This project is licensed under the **MIT License**.  
You may use, modify, and distribute this project freely with attribution.  

---

## 18. Acknowledgements

- Birzeit University — Department of Computer Engineering  
- Data Structures course instructors and teaching assistants  
- Peers and open-source community resources for algorithmic references  

---

## 19. Version History

| Version | Date | Description |
|----------|------|-------------|
| 1.0 | March 2024 | Basic tree and hash structure setup |
| 1.1 | April 2024 | Added traversal and collision handling |
| 1.2 | May 2024 | Integrated BST operations and chaining |
| 2.0 | June 2024 | Refactored project with modular codebase and test suite |

---
