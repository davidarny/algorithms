#ifndef ALGORITHMS_B_TREE_H
#define ALGORITHMS_B_TREE_H

#include "BTreeNode.h"
#include "Insertable.h"

class BTree : public Insertable<int> {
private:
    BTreeNode* mRootNode;
    int mMinDegree;

public:
    explicit BTree(int degree);

    void traverse(int depth);

    BTreeNode* search(int key);

    void insert(int key) override;

    void remove(int key);
};

#endif //ALGORITHMS_B_TREE_H
