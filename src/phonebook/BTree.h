#ifndef ALGORITHMS_B_TREE_H
#define ALGORITHMS_B_TREE_H

#include "BTreeNode.h"
#include "Insertable.h"

class BTree : public Insertable<int, const std::string&> {
private:
    BTreeNode* mRootNode;
    int mMinDegree;

public:
    explicit BTree(int degree);

    void traverse();

    BTreeNode* search(int key);

    void insert(int key, const std::string& id) override;

    void insert(int key) override;

    void remove(int key);

    void update(int key, int value);
};

#endif //ALGORITHMS_B_TREE_H
