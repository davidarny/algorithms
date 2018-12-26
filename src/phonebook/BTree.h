#ifndef ALGORITHMS_B_TREE_H
#define ALGORITHMS_B_TREE_H

#include "BTreeNode.h"
#include "Insertable.h"

class BTree : public Insertable<int> {
private:
    BTreeNode* mRootNode; // Pointer to root node
    int mMinDegree; // Minimum degree

public:
    // Constructor (Initializes tree as empty)
    explicit BTree(int degree);

    // function to traverse the tree
    void traverse();

    // function to search a key in this tree
    BTreeNode* search(int key);

    // The main function that inserts a new key in this B-Tree
    void insert(int key) override;

    // The main function that removes a new key in the B-Tree
    void remove(int key);

    // A function to update children[k] node
    void update(int key, int value);
};

#endif //ALGORITHMS_B_TREE_H
