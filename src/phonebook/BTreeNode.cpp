#include <iostream>

#include "BTreeNode.h"

BTreeNode::BTreeNode(int _t, bool _leaf)
{
    // Copy the given minimum degree and leaf property
    degree = _t;
    leaf = _leaf;
    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2 * degree - 1];
    children = new BTreeNode*[2 * degree];
    // Initialize the number of keys as 0
    n = 0;
}

void BTreeNode::traverse()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++) {
        std::cout << " " << keys[i];
    }
    std::cout << std::endl;
    for (i = 0; i < n; i++) {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child children[i].
        if (!leaf) {
            children[i]->traverse();
        }
    }
    // Print the subtree rooted with last child
    if (!leaf) {
        children[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i]) {
        i++;
    }
    // If the found key is equal to k, return this node
    if (keys[i] == k) {
        return this;
    }
    // If the key is not found here and this is a leaf node
    if (leaf) {
        return nullptr;
    }
    // Go to the appropriate child
    return children[i]->search(k);
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(int k)
{
    // Initialize index as index of rightmost element
    int i = n - 1;
    // If this is a leaf node
    if (leaf) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    } else {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;
        // See if the found child is full
        if (children[i + 1]->n == 2 * degree - 1) {
            // If the child is full, then split it
            splitChild(i + 1, children[i + 1]);
            // After split, the middle key of children[i] goes up and
            // children[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i + 1] < k) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(k);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode* y)
{
    // Create a new node which is going to store (degree-1) keys
    // of y
    auto* z = new BTreeNode(y->degree, y->leaf);
    z->n = degree - 1;
    // Copy the last (degree-1) keys of y to z
    for (int j = 0; j < degree - 1; j++) {
        z->keys[j] = y->keys[j + degree];
    }
    // Copy the last degree children of y to z
    if (!y->leaf) {
        for (int j = 0; j < degree; j++) {
            z->children[j] = y->children[j + degree];
        }
    }
    // Reduce the number of keys in y
    y->n = degree - 1;
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i + 1; j--) {
        children[j + 1] = children[j];
    }
    // Link the new child to this node
    children[i + 1] = z;
    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }
    // Copy the middle key of y to this node
    keys[i] = y->keys[degree - 1];
    // Increment count of keys in this node
    n = n + 1;
}

// A utility function that returns the index of the first key that is
// greater than or equal to k
int BTreeNode::findKey(int k)
{
    int idx = 0;
    while (idx < n && keys[idx] < k) {
        ++idx;
    }
    return idx;
}

// A wrapper function to update the key value by k
void BTreeNode::updateByIndex(int idx, int value)
{
    keys[idx] = value;
}

// A function to remove the key k from the sub-tree rooted with this node
void BTreeNode::remove(int k)
{
    int idx = findKey(k);
    // The key to be removed is present in this node
    if (idx < n && keys[idx] == k) {
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        // If this node is a leaf node, then the key is not present in tree
        if (leaf) {
            std::cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = idx == n;
        // If the child where the key is supposed to exist has less that degree keys,
        // we fill that child
        if (children[idx]->n < degree) {
            fill(idx);
        }
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast degree keys
        if (flag && idx > n) {
            children[idx - 1]->remove(k);
        } else {
            children[idx]->remove(k);
        }
    }
}

// A function to remove the idx-th key from this node - which is a leaf node
void BTreeNode::removeFromLeaf(int idx)
{
    // Move all the keys after the idx-th pos one place backward
    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
    }
    // Reduce the count of keys
    n--;
}

// A function to remove the idx-th key from this node - which is a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx)
{
    int k = keys[idx];
    // If the child that precedes k (children[idx]) has atleast degree keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // children[idx]. Replace k by pred. Recursively delete pred
    // in children[idx]
    if (children[idx]->n >= degree) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->n >= degree) {
        // If the child children[idx] has less that degree keys, examine children[idx+1].
        // If children[idx+1] has atleast degree keys, find the successor 'succ' of k in
        // the subtree rooted at children[idx+1]
        // Replace k by succ
        // Recursively delete succ in children[idx+1]
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        // If both children[idx] and children[idx+1] has less that degree keys,merge k and all of children[idx+1]
        // into children[idx]
        // Now children[idx] contains 2t-1 keys
        // Free children[idx+1] and recursively delete k from children[idx]
        merge(idx);
        children[idx]->remove(k);
    }
}

// A function to get predecessor of keys[idx]
int BTreeNode::getPredecessor(int idx)
{
    // Keep moving to the right most node until we reach a leaf
    BTreeNode* cur = children[idx];
    while (!cur->leaf) {
        cur = cur->children[cur->n];
    }
    // Return the last key of the leaf
    return cur->keys[cur->n - 1];
}

int BTreeNode::getSuccessor(int idx)
{
    // Keep moving the left most node starting from children[idx+1] until we reach a leaf
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf) {
        cur = cur->children[0];
    }
    // Return the first key of the leaf
    return cur->keys[0];
}

// A function to fill child children[idx] which has less than degree-1 keys
void BTreeNode::fill(int idx)
{
    // If the previous child(children[idx-1]) has more than degree-1 keys, borrow a key
    // from that child
    if (idx != 0 && children[idx - 1]->n >= degree) {
        borrowFromPrevious(idx);
    } else if (idx != n && children[idx + 1]->n >= degree) {
        // If the next child(children[idx+1]) has more than degree-1 keys, borrow a key
        // from that child
        borrowFromNext(idx);
    } else {
        // Merge children[idx] with its sibling
        // If children[idx] is the last child, merge it with with its previous sibling
        // Otherwise merge it with its next sibling
        if (idx != n) {
            merge(idx);
        } else {
            merge(idx - 1);
        }
    }
}

// A function to borrow a key from children[idx-1] and insert it
// into children[idx]
void BTreeNode::borrowFromPrevious(int idx)
{
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];
    // The last key from children[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in children[idx]. Thus, the  loses
    // sibling one key and child gains one key
    // Moving all key in children[idx] one step ahead
    for (int i = child->n - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }
    // If children[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }
    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = keys[idx - 1];
    // Moving sibling's last child as children[idx]'s first child
    if (!child->leaf) {
        child->children[0] = sibling->children[sibling->n];
    }
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::borrowFromNext(int idx)
{

    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    // keys[idx] is inserted as the last key in children[idx]
    child->keys[(child->n)] = keys[idx];
    // Sibling's first child is inserted as the last child
    // into children[idx]
    if (!(child->leaf)) {
        child->children[(child->n) + 1] = sibling->children[0];
    }
    //The first key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];
    // Moving all keys in sibling one step behind
    for (int i = 1; i < sibling->n; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    // Moving the child pointers one step behind
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }
    // Increasing and decreasing the key count of children[idx] and children[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;
}

// A function to merge children[idx] with children[idx+1]
// children[idx+1] is freed after merging
void BTreeNode::merge(int idx)
{
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    // Pulling a key from the current node and inserting it into (degree-1)th
    // position of children[idx]
    child->keys[degree - 1] = keys[idx];
    // Copying the keys from children[idx+1] to children[idx] at the end
    for (int i = 0; i < sibling->n; ++i) {
        child->keys[i + degree] = sibling->keys[i];
    }
    // Copying the child pointers from children[idx+1] to children[idx]
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->children[i + degree] = sibling->children[i];
        }
    }
    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to children[idx]
    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
    }
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i = idx + 2; i <= n; ++i) {
        children[i - 1] = children[i];
    }
    // Updating the key count of child and the current node
    child->n += sibling->n + 1;
    n--;
    // Freeing the memory occupied by sibling
    delete (sibling);
}
