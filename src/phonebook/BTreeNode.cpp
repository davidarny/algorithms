#include <iostream>

#include "BTreeNode.h"

BTreeNode::BTreeNode(int degree, bool isLeaf)
{
    mDegree = degree;
    mIsLeaf = isLeaf;
    mKeys = new int[2 * mDegree - 1];
    mChildren = new BTreeNode*[2 * mDegree];
    mKeysCount = 0;
}

void BTreeNode::traverse(int depth)
{
    int index;
    std::cout << std::string(static_cast<unsigned long>(depth * 2), ' ') << "[";
    for (index = 0; index < mKeysCount; index++) {
        std::cout << mKeys[index];
        if (index != mKeysCount - 1) {
            std::cout << " ";
        }
    }
    int nextDepth = ++depth;
    std::cout << "]" << std::endl;
    for (index = 0; index < mKeysCount; index++) {
        if (!mIsLeaf) {
            mChildren[index]->traverse(nextDepth);
        }
    }
    if (!mIsLeaf) {
        mChildren[index]->traverse(nextDepth);
    }
}

BTreeNode* BTreeNode::search(int key, int depth)
{
    int index = 0;
    while (index < mKeysCount && key > mKeys[index]) {
        index++;
    }
    if (mKeys[index] == key) {
        std::cout << "Found key \""
                  << std::to_string(key)
                  << "\""
                  << " on level \""
                  << std::to_string(depth)
                  << "\""
                  << std::endl;
        return this;
    }
    if (mIsLeaf) {
        return nullptr;
    }
    std::cout << "Got index closest \""
              << std::to_string(index)
              << "\" on level \""
              << std::to_string(depth)
              << "\""
              << std::endl;
    return mChildren[index]->search(key, ++depth);
}

void BTreeNode::insertNonFull(int key)
{
    int index = mKeysCount - 1;
    if (mIsLeaf) {
        while (index >= 0 && mKeys[index] > key) {
            mKeys[index + 1] = mKeys[index];
            index--;
        }
        mKeys[index + 1] = key;
        mKeysCount = mKeysCount + 1;
    } else {
        while (index >= 0 && mKeys[index] > key)
            index--;
        if (mChildren[index + 1]->mKeysCount == 2 * mDegree - 1) {
            splitChild(index + 1, mChildren[index + 1]);
            if (mKeys[index + 1] < key) {
                index++;
            }
        }
        mChildren[index + 1]->insertNonFull(key);
    }
}

void BTreeNode::splitChild(int key, BTreeNode* node)
{
    auto* pNode = new BTreeNode(node->mDegree, node->mIsLeaf);
    pNode->mKeysCount = mDegree - 1;
    for (int index = 0; index < mDegree - 1; index++) {
        pNode->mKeys[index] = node->mKeys[index + mDegree];
    }
    if (!node->mIsLeaf) {
        for (int index = 0; index < mDegree; index++) {
            pNode->mChildren[index] = node->mChildren[index + mDegree];
        }
    }
    node->mKeysCount = mDegree - 1;
    for (int index = mKeysCount; index >= key + 1; index--) {
        mChildren[index + 1] = mChildren[index];
    }
    mChildren[key + 1] = pNode;
    for (int index = mKeysCount - 1; index >= key; index--) {
        mKeys[index + 1] = mKeys[index];
    }
    mKeys[key] = node->mKeys[mDegree - 1];
    mKeysCount = mKeysCount + 1;
}

int BTreeNode::findKey(int key)
{
    int index = 0;
    while (index < mKeysCount && mKeys[index] < key) {
        ++index;
    }
    return index;
}

void BTreeNode::remove(int key)
{
    int index = findKey(key);
    if (index < mKeysCount && mKeys[index] == key) {
        if (mIsLeaf) {
            removeFromLeaf(index);
        } else {
            removeFromNonLeaf(index);
        }
    } else {
        if (mIsLeaf) {
            std::cout << "The key " << key << " is does not exist in the tree\n";
            return;
        }
        bool flag = index == mKeysCount;
        if (mChildren[index]->mKeysCount < mDegree) {
            fill(index);
        }
        if (flag && index > mKeysCount) {
            mChildren[index - 1]->remove(key);
        } else {
            mChildren[index]->remove(key);
        }
    }
}

void BTreeNode::removeFromLeaf(int key)
{
    for (int index = key + 1; index < mKeysCount; ++index) {
        mKeys[index - 1] = mKeys[index];
    }
    mKeysCount--;
}

void BTreeNode::removeFromNonLeaf(int index)
{
    int key = mKeys[index];
    if (mChildren[index]->mKeysCount >= mDegree) {
        int predecessor = getPredecessor(index);
        mKeys[index] = predecessor;
        mChildren[index]->remove(predecessor);
    } else if (mChildren[index + 1]->mKeysCount >= mDegree) {
        int successor = getSuccessor(index);
        mKeys[index] = successor;
        mChildren[index + 1]->remove(successor);
    } else {
        merge(index);
        mChildren[index]->remove(key);
    }
}

int BTreeNode::getPredecessor(int index)
{
    BTreeNode* current = mChildren[index];
    while (!current->mIsLeaf) {
        current = current->mChildren[current->mKeysCount];
    }
    return current->mKeys[current->mKeysCount - 1];
}

int BTreeNode::getSuccessor(int index)
{
    BTreeNode* current = mChildren[index + 1];
    while (!current->mIsLeaf) {
        current = current->mChildren[0];
    }
    return current->mKeys[0];
}

void BTreeNode::fill(int index)
{
    if (index != 0 && mChildren[index - 1]->mKeysCount >= mDegree) {
        borrowFromPrevious(index);
    } else if (index != mKeysCount && mChildren[index + 1]->mKeysCount >= mDegree) {
        borrowFromNext(index);
    } else {
        if (index != mKeysCount) {
            merge(index);
        } else {
            merge(index - 1);
        }
    }
}

void BTreeNode::borrowFromPrevious(int key)
{
    BTreeNode* child = mChildren[key];
    BTreeNode* sibling = mChildren[key - 1];
    for (int index = child->mKeysCount - 1; index >= 0; --index) {
        child->mKeys[index + 1] = child->mKeys[index];
    }
    if (!child->mIsLeaf) {
        for (int index = child->mKeysCount; index >= 0; --index) {
            child->mChildren[index + 1] = child->mChildren[index];
        }
    }
    child->mKeys[0] = mKeys[key - 1];
    if (!child->mIsLeaf) {
        child->mChildren[0] = sibling->mChildren[sibling->mKeysCount];
    }
    mKeys[key - 1] = sibling->mKeys[sibling->mKeysCount - 1];
    child->mKeysCount += 1;
    sibling->mKeysCount -= 1;
}

void BTreeNode::borrowFromNext(int key)
{

    BTreeNode* child = mChildren[key];
    BTreeNode* sibling = mChildren[key + 1];
    child->mKeys[(child->mKeysCount)] = mKeys[key];
    if (!(child->mIsLeaf)) {
        child->mChildren[(child->mKeysCount) + 1] = sibling->mChildren[0];
    }
    mKeys[key] = sibling->mKeys[0];
    for (int index = 1; index < sibling->mKeysCount; ++index) {
        sibling->mKeys[index - 1] = sibling->mKeys[index];
    }
    if (!sibling->mIsLeaf) {
        for (int index = 1; index <= sibling->mKeysCount; ++index) {
            sibling->mChildren[index - 1] = sibling->mChildren[index];
        }
    }
    child->mKeysCount += 1;
    sibling->mKeysCount -= 1;
}

void BTreeNode::merge(int key)
{
    BTreeNode* child = mChildren[key];
    BTreeNode* sibling = mChildren[key + 1];
    child->mKeys[mDegree - 1] = mKeys[key];
    for (int index = 0; index < sibling->mKeysCount; ++index) {
        child->mKeys[index + mDegree] = sibling->mKeys[index];
    }
    if (!child->mIsLeaf) {
        for (int index = 0; index <= sibling->mKeysCount; ++index) {
            child->mChildren[index + mDegree] = sibling->mChildren[index];
        }
    }
    for (int index = key + 1; index < mKeysCount; ++index) {
        mKeys[index - 1] = mKeys[index];
    }
    for (int index = key + 2; index <= mKeysCount; ++index) {
        mChildren[index - 1] = mChildren[index];
    }
    child->mKeysCount += sibling->mKeysCount + 1;
    mKeysCount--;
    delete (sibling);
}
