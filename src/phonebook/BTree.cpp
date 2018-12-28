#include "BTree.h"
#include <iostream>

BTree::BTree(int degree)
{
    mRootNode = nullptr;
    mMinDegree = degree;
}

void BTree::traverse(int depth)
{
    if (mRootNode == nullptr) {
        return;
    }
    mRootNode->traverse(depth);
}

BTreeNode* BTree::search(int key)
{
    if (mRootNode == nullptr) {
        return nullptr;
    }
    return mRootNode->search(key);
}

void BTree::insert(int key)
{
    if (mRootNode == nullptr) {
        mRootNode = new BTreeNode(mMinDegree, true);
        mRootNode->mKeys[0] = key;
        mRootNode->mKeysCount = 1;
    } else {
        if (mRootNode->mKeysCount == 2 * mMinDegree - 1) {
            auto* pNode = new BTreeNode(mMinDegree, false);
            pNode->mChildren[0] = mRootNode;
            pNode->splitChild(0, mRootNode);
            int i = 0;
            if (pNode->mKeys[0] < key) {
                i++;
            }
            pNode->mChildren[i]->insertNonFull(key);
            mRootNode = pNode;
        } else {
            mRootNode->insertNonFull(key);
        }
    }
}

void BTree::remove(int key)
{
    if (!mRootNode) {
        std::cout << "The tree is empty\n";
        return;
    }
    mRootNode->remove(key);
    if (mRootNode->mKeysCount == 0) {
        BTreeNode* tmp = mRootNode;
        if (mRootNode->mIsLeaf) {
            mRootNode = nullptr;
        } else {
            mRootNode = mRootNode->mChildren[0];
        }
        delete tmp;
    }
}
