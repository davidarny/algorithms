#include <iostream>

#include "BTreeNode.h"

BTreeNode::BTreeNode(int degree, bool isLeaf)
{
    // Copy the given minimum degree and leaf property
    mDegree = degree;
    mIsLeaf = isLeaf;
    // Allocate memory for maximum number of possible keys
    // and child pointers
    mKeys = new int[2 * mDegree - 1];
    mChildren = new BTreeNode*[2 * mDegree];
    // Initialize the number of keys as 0
    mKeysCount = 0;
}

void BTreeNode::traverse()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < mKeysCount; i++) {
        std::cout << " " << mKeys[i];
    }
    std::cout << std::endl;
    for (i = 0; i < mKeysCount; i++) {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child children[i].
        if (!mIsLeaf) {
            mChildren[i]->traverse();
        }
    }
    // Print the subtree rooted with last child
    if (!mIsLeaf) {
        mChildren[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(int key)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < mKeysCount && key > mKeys[i]) {
        i++;
    }
    // If the found key is equal to k, return this node
    if (mKeys[i] == key) {
        return this;
    }
    // If the key is not found here and this is a leaf node
    if (mIsLeaf) {
        return nullptr;
    }
    // Go to the appropriate child
    return mChildren[i]->search(key);
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(int key)
{
    // Initialize index as index of rightmost element
    int i = mKeysCount - 1;
    // If this is a leaf node
    if (mIsLeaf) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && mKeys[i] > key) {
            mKeys[i + 1] = mKeys[i];
            i--;
        }
        // Insert the new key at found location
        mKeys[i + 1] = key;
        mKeysCount = mKeysCount + 1;
    } else {
        // Find the child which is going to have the new key
        while (i >= 0 && mKeys[i] > key)
            i--;
        // See if the found child is full
        if (mChildren[i + 1]->mKeysCount == 2 * mDegree - 1) {
            // If the child is full, then split it
            splitChild(i + 1, mChildren[i + 1]);
            // After split, the middle key of children[i] goes up and
            // children[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (mKeys[i + 1] < key) {
                i++;
            }
        }
        mChildren[i + 1]->insertNonFull(key);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int index, BTreeNode* node)
{
    // Create a new node which is going to store (degree-1) keys
    // of y
    auto* z = new BTreeNode(node->mDegree, node->mIsLeaf);
    z->mKeysCount = mDegree - 1;
    // Copy the last (degree-1) keys of y to z
    for (int j = 0; j < mDegree - 1; j++) {
        z->mKeys[j] = node->mKeys[j + mDegree];
    }
    // Copy the last degree children of y to z
    if (!node->mIsLeaf) {
        for (int j = 0; j < mDegree; j++) {
            z->mChildren[j] = node->mChildren[j + mDegree];
        }
    }
    // Reduce the number of keys in y
    node->mKeysCount = mDegree - 1;
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = mKeysCount; j >= index + 1; j--) {
        mChildren[j + 1] = mChildren[j];
    }
    // Link the new child to this node
    mChildren[index + 1] = z;
    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = mKeysCount - 1; j >= index; j--) {
        mKeys[j + 1] = mKeys[j];
    }
    // Copy the middle key of y to this node
    mKeys[index] = node->mKeys[mDegree - 1];
    // Increment count of keys in this node
    mKeysCount = mKeysCount + 1;
}

// A utility function that returns the index of the first key that is
// greater than or equal to k
int BTreeNode::findKey(int key)
{
    int idx = 0;
    while (idx < mKeysCount && mKeys[idx] < key) {
        ++idx;
    }
    return idx;
}

// A wrapper function to update the key value by k
void BTreeNode::updateByIndex(int index, int value)
{
    mKeys[index] = value;
}

// A function to remove the key k from the sub-tree rooted with this node
void BTreeNode::remove(int key)
{
    int idx = findKey(key);
    // The key to be removed is present in this node
    if (idx < mKeysCount && mKeys[idx] == key) {
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (mIsLeaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        // If this node is a leaf node, then the key is not present in tree
        if (mIsLeaf) {
            std::cout << "The key " << key << " is does not exist in the tree\n";
            return;
        }
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = idx == mKeysCount;
        // If the child where the key is supposed to exist has less that degree keys,
        // we fill that child
        if (mChildren[idx]->mKeysCount < mDegree) {
            fill(idx);
        }
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast degree keys
        if (flag && idx > mKeysCount) {
            mChildren[idx - 1]->remove(key);
        } else {
            mChildren[idx]->remove(key);
        }
    }
}

// A function to remove the idx-th key from this node - which is a leaf node
void BTreeNode::removeFromLeaf(int index)
{
    // Move all the keys after the idx-th pos one place backward
    for (int i = index + 1; i < mKeysCount; ++i) {
        mKeys[i - 1] = mKeys[i];
    }
    // Reduce the count of keys
    mKeysCount--;
}

// A function to remove the idx-th key from this node - which is a non-leaf node
void BTreeNode::removeFromNonLeaf(int index)
{
    int k = mKeys[index];
    // If the child that precedes k (children[idx]) has atleast degree keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // children[idx]. Replace k by pred. Recursively delete pred
    // in children[idx]
    if (mChildren[index]->mKeysCount >= mDegree) {
        int pred = getPredecessor(index);
        mKeys[index] = pred;
        mChildren[index]->remove(pred);
    } else if (mChildren[index + 1]->mKeysCount >= mDegree) {
        // If the child children[idx] has less that degree keys, examine children[idx+1].
        // If children[idx+1] has atleast degree keys, find the successor 'succ' of k in
        // the subtree rooted at children[idx+1]
        // Replace k by succ
        // Recursively delete succ in children[idx+1]
        int succ = getSuccessor(index);
        mKeys[index] = succ;
        mChildren[index + 1]->remove(succ);
    } else {
        // If both children[idx] and children[idx+1] has less that degree keys,merge k and all of children[idx+1]
        // into children[idx]
        // Now children[idx] contains 2t-1 keys
        // Free children[idx+1] and recursively delete k from children[idx]
        merge(index);
        mChildren[index]->remove(k);
    }
}

// A function to get predecessor of keys[idx]
int BTreeNode::getPredecessor(int index)
{
    // Keep moving to the right most node until we reach a leaf
    BTreeNode* cur = mChildren[index];
    while (!cur->mIsLeaf) {
        cur = cur->mChildren[cur->mKeysCount];
    }
    // Return the last key of the leaf
    return cur->mKeys[cur->mKeysCount - 1];
}

int BTreeNode::getSuccessor(int index)
{
    // Keep moving the left most node starting from children[idx+1] until we reach a leaf
    BTreeNode* cur = mChildren[index + 1];
    while (!cur->mIsLeaf) {
        cur = cur->mChildren[0];
    }
    // Return the first key of the leaf
    return cur->mKeys[0];
}

// A function to fill child children[idx] which has less than degree-1 keys
void BTreeNode::fill(int index)
{
    // If the previous child(children[idx-1]) has more than degree-1 keys, borrow a key
    // from that child
    if (index != 0 && mChildren[index - 1]->mKeysCount >= mDegree) {
        borrowFromPrevious(index);
    } else if (index != mKeysCount && mChildren[index + 1]->mKeysCount >= mDegree) {
        // If the next child(children[idx+1]) has more than degree-1 keys, borrow a key
        // from that child
        borrowFromNext(index);
    } else {
        // Merge children[idx] with its sibling
        // If children[idx] is the last child, merge it with with its previous sibling
        // Otherwise merge it with its next sibling
        if (index != mKeysCount) {
            merge(index);
        } else {
            merge(index - 1);
        }
    }
}

// A function to borrow a key from children[idx-1] and insert it
// into children[idx]
void BTreeNode::borrowFromPrevious(int index)
{
    BTreeNode* child = mChildren[index];
    BTreeNode* sibling = mChildren[index - 1];
    // The last key from children[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in children[idx]. Thus, the  loses
    // sibling one key and child gains one key
    // Moving all key in children[idx] one step ahead
    for (int i = child->mKeysCount - 1; i >= 0; --i) {
        child->mKeys[i + 1] = child->mKeys[i];
    }
    // If children[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->mIsLeaf) {
        for (int i = child->mKeysCount; i >= 0; --i) {
            child->mChildren[i + 1] = child->mChildren[i];
        }
    }
    // Setting child's first key equal to keys[idx-1] from the current node
    child->mKeys[0] = mKeys[index - 1];
    // Moving sibling's last child as children[idx]'s first child
    if (!child->mIsLeaf) {
        child->mChildren[0] = sibling->mChildren[sibling->mKeysCount];
    }
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    mKeys[index - 1] = sibling->mKeys[sibling->mKeysCount - 1];
    child->mKeysCount += 1;
    sibling->mKeysCount -= 1;
}

void BTreeNode::borrowFromNext(int index)
{

    BTreeNode* child = mChildren[index];
    BTreeNode* sibling = mChildren[index + 1];
    // keys[idx] is inserted as the last key in children[idx]
    child->mKeys[(child->mKeysCount)] = mKeys[index];
    // Sibling's first child is inserted as the last child
    // into children[idx]
    if (!(child->mIsLeaf)) {
        child->mChildren[(child->mKeysCount) + 1] = sibling->mChildren[0];
    }
    //The first key from sibling is inserted into keys[idx]
    mKeys[index] = sibling->mKeys[0];
    // Moving all keys in sibling one step behind
    for (int i = 1; i < sibling->mKeysCount; ++i) {
        sibling->mKeys[i - 1] = sibling->mKeys[i];
    }
    // Moving the child pointers one step behind
    if (!sibling->mIsLeaf) {
        for (int i = 1; i <= sibling->mKeysCount; ++i) {
            sibling->mChildren[i - 1] = sibling->mChildren[i];
        }
    }
    // Increasing and decreasing the key count of children[idx] and children[idx+1]
    // respectively
    child->mKeysCount += 1;
    sibling->mKeysCount -= 1;
}

// A function to merge children[idx] with children[idx+1]
// children[idx+1] is freed after merging
void BTreeNode::merge(int index)
{
    BTreeNode* child = mChildren[index];
    BTreeNode* sibling = mChildren[index + 1];
    // Pulling a key from the current node and inserting it into (degree-1)th
    // position of children[idx]
    child->mKeys[mDegree - 1] = mKeys[index];
    // Copying the keys from children[idx+1] to children[idx] at the end
    for (int i = 0; i < sibling->mKeysCount; ++i) {
        child->mKeys[i + mDegree] = sibling->mKeys[i];
    }
    // Copying the child pointers from children[idx+1] to children[idx]
    if (!child->mIsLeaf) {
        for (int i = 0; i <= sibling->mKeysCount; ++i) {
            child->mChildren[i + mDegree] = sibling->mChildren[i];
        }
    }
    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to children[idx]
    for (int i = index + 1; i < mKeysCount; ++i) {
        mKeys[i - 1] = mKeys[i];
    }
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i = index + 2; i <= mKeysCount; ++i) {
        mChildren[i - 1] = mChildren[i];
    }
    // Updating the key count of child and the current node
    child->mKeysCount += sibling->mKeysCount + 1;
    mKeysCount--;
    // Freeing the memory occupied by sibling
    delete (sibling);
}
