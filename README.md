# 🌳 Binary Search Tree Assignment

This project enhances a basic **Binary Search Tree (BST)** implementation by incorporating several advanced functionalities related to student record management.

The system uses a student ID as the key for each node in the BST. Below is a description of the additional functions implemented as part of this assignment.

---

## 📂 Features Implemented

### 📄 `bool readFile(const char* filename, BST* tree)`
Reads student records from a text file and inserts them into the BST based on student ID.  
- Displays the number of records successfully loaded.  
- Returns `false` if the file fails to open, and `true` otherwise.  
- Refer to the sample `student.txt` provided for the expected input format.

---

### 🌿 `bool BST::deepestNodes()`
Finds and prints all nodes at the deepest level of the tree.  
- Example: In Tree1 (Figure 3.2), deepest nodes are `2`, `7`, and `12`; in Tree2, it's `21`.  
- Utilizes tree height for identifying the deepest level.  
- Returns `false` for an empty tree, `true` otherwise.

---

### 📊 `bool BST::display(int order, int source)`
Recursively traverses and prints all nodes in the BST.

- `order = 1`: Print in ascending order (in-order traversal: left, root, right)  
- `order = 2`: Print in descending order (right, root, left)  
- `source = 1`: Output to screen  
- `source = 2`: Output to file (`student-info.txt`)  
- Returns `false` if the tree is empty, `true` otherwise.

---

### 🌱 `bool BST::CloneSubtree(BST t1, type item)`
Clones a subtree from tree `t1` rooted at the node containing `item`, and stores the clone in another BST.

- `t1` remains unchanged after the function call.  
- `t2` must be empty before cloning.  
- Both `t1` and `t2` are displayed using `preOrderPrint()` after cloning.  
- Returns `false` if `t1` is empty, `true` otherwise.

---

## 📌 Notes

- The structure of the `student.txt` file should follow the sample provided.
- Function names and logic were implemented based on assignment specifications and textbook best practices.
- Tree operations were tested on sample inputs to ensure correctness and efficiency.

---

## 👨‍💻 Authors

- **Owi Wilson**
- **Chin Zheng Quan**
- **Lim Yi Xiang**
- **Koo Ian Hong**

