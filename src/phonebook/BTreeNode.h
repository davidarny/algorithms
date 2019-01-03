#ifndef ALGORITHMS_B_TREE_NODE_H
#define ALGORITHMS_B_TREE_NODE_H

#include <string>

class BTreeNode {
private:
    int* mKeys;
    int mDegree;
    BTreeNode** mChildren;
    int mKeysCount;
    bool mIsLeaf;

public:
    BTreeNode(int degree, bool isLeaf);

    void insertNonFull(int key);

    void splitChild(int key, BTreeNode* node);

    void traverse(int depth);

    BTreeNode* search(int key, int depth);

    int findKey(int key);

    void remove(int key);

    void removeFromLeaf(int key);

    void removeFromNonLeaf(int index);

    int getPredecessor(int index);

    int getSuccessor(int index);

    void fill(int index);

    void borrowFromPrevious(int key);

    void borrowFromNext(int key);

    void merge(int key);

    friend class BTree;
};

#endif //ALGORITHMS_B_TREE_NODE_H
