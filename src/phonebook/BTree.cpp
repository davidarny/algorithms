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

// A function to update children[k] node
void BTree::update(int key, int value)
{
    auto node = search(key);
    if (node == nullptr) {
        throw std::runtime_error("Key " + std::to_string(key) + " not found!");
    }
    auto idx = node->findKey(key);
    node->updateByIndex(idx, value);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(int key)
{
    // If tree is empty
    if (mRootNode == nullptr) {
        // Allocate memory for root
        mRootNode = new BTreeNode(mMinDegree, true);
        mRootNode->mKeys[0] = key; // Insert key
        mRootNode->mKeysCount = 1; // Update number of keys in root
    } else {
        // If tree is not empty
        // If root is full, then tree grows in height
        if (mRootNode->mKeysCount == 2 * mMinDegree - 1) {
            // Allocate memory for new root
            auto* s = new BTreeNode(mMinDegree, false);
            // Make old root as child of new root
            s->mChildren[0] = mRootNode;
            // Split the old root and move 1 key to the new root
            s->splitChild(0, mRootNode);
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->mKeys[0] < key) {
                i++;
            }
            s->mChildren[i]->insertNonFull(key);
            // Change root
            mRootNode = s;
        } else {
            // If root is not full, call insertNonFull for root
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
    // Call the remove function for root
    mRootNode->remove(key);
    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (mRootNode->mKeysCount == 0) {
        BTreeNode* tmp = mRootNode;
        if (mRootNode->mIsLeaf) {
            mRootNode = nullptr;
        } else {
            mRootNode = mRootNode->mChildren[0];
        }
        // Free the old root
        delete tmp;
    }
}
