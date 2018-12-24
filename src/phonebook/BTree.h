#ifndef ALGORITHMS_B_TREE_H
#define ALGORITHMS_B_TREE_H

#include "BTreeNode.h"

class BTree {
private:
    BTreeNode* root; // Pointer to root node
    int t; // Minimum degree

public:
    // Constructor (Initializes tree as empty)
    BTree(int _t);

    // function to traverse the tree
    void traverse();

    // function to search a key in this tree
    BTreeNode* search(int k);

    // The main function that inserts a new key in this B-Tree
    void insert(int k);

    // The main function that removes a new key in the B-Tree
    void remove(int k);

    // A function to update children[k] node
    void update(int k, int value);
};

#endif //ALGORITHMS_B_TREE_H
