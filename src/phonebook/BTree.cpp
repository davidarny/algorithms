#include "BTree.h"
#include <iostream>

BTree::BTree(int degree)
{
    mRootNode = nullptr;
    mMinDegree = degree;
}

void BTree::traverse()
{
    if (mRootNode == nullptr) {
        return;
    }
    mRootNode->traverse();
}

BTreeNode* BTree::search(int key)
{
    if (mRootNode == nullptr) {
        return nullptr;
    }
    return mRootNode->search(key);
}

void BTree::update(int key, int value)
{
    auto node = search(key);
    if (node == nullptr) {
        throw std::runtime_error("Key " + std::to_string(key) + " not found!");
    }
    auto idx = node->findKey(key);
    node->updateByIndex(idx, value);
}

void BTree::insert(int key, const std::string& id)
{
    // If tree is empty
    if (mRootNode == nullptr) {
        mRootNode = new BTreeNode(mMinDegree, true);
        mRootNode->mKeys[0] = key;
        mRootNode->mKeysCount = 1;
        mRootNode->mTableId = id;
    } else {
        if (mRootNode->mKeysCount == 2 * mMinDegree - 1) {
            auto* s = new BTreeNode(mMinDegree, false);
            s->mTableId = id;
            s->mChildren[0] = mRootNode;
            s->splitChild(0, mRootNode);
            int i = 0;
            if (s->mKeys[0] < key) {
                i++;
            }
            s->mChildren[i]->insertNonFull(key);
            mRootNode = s;
        } else {
            mRootNode->insertNonFull(key);
        }
    }
}

void BTree::insert(int key)
{
    if (mRootNode == nullptr) {
        mRootNode = new BTreeNode(mMinDegree, true);
        mRootNode->mKeys[0] = key;
        mRootNode->mKeysCount = 1;
    } else {
        if (mRootNode->mKeysCount == 2 * mMinDegree - 1) {
            auto* s = new BTreeNode(mMinDegree, false);
            s->mChildren[0] = mRootNode;
            s->splitChild(0, mRootNode);
            int i = 0;
            if (s->mKeys[0] < key) {
                i++;
            }
            s->mChildren[i]->insertNonFull(key);
            mRootNode = s;
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
