#include "BTree.h"

#include <iostream>

BTree::BTree(int _t)
{
    root = nullptr;
    t = _t;
}

void BTree::traverse()
{
    if (root == nullptr) {
        return;
    }
    root->traverse();
}

BTreeNode* BTree::search(int k)
{
    if (root == nullptr) {
        return nullptr;
    }
    return root->search(k);
}

// A function to update children[k] node
void BTree::update(int k, int value)
{
    auto node = search(k);
    if (node == nullptr) {
        throw std::runtime_error("Key " + std::to_string(k) + " not found!");
    }
    auto idx = node->findKey(k);
    node->updateByIndex(idx, value);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(int k)
{
    // If tree is empty
    if (root == nullptr) {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k; // Insert key
        root->n = 1; // Update number of keys in root
    } else {
        // If tree is not empty
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1) {
            // Allocate memory for new root
            auto* s = new BTreeNode(t, false);
            // Make old root as child of new root
            s->children[0] = root;
            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            s->children[i]->insertNonFull(k);
            // Change root
            root = s;
        } else {
            // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
        }
    }
}

void BTree::remove(int k)
{
    if (!root) {
        std::cout << "The tree is empty\n";
        return;
    }
    // Call the remove function for root
    root->remove(k);
    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->leaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        // Free the old root
        delete tmp;
    }
}
