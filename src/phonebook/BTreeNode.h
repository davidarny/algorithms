#ifndef ALGORITHMS_B_TREE_NODE_H
#define ALGORITHMS_B_TREE_NODE_H

class BTreeNode {
private:
    int* mKeys; // An array of keys
    int mDegree; // Minimum degree (defines the range for number of keys)
    BTreeNode** mChildren; // An array of child pointers
    int mKeysCount; // Current number of keys
    bool mIsLeaf; // Is true when node is leaf. Otherwise false

public:
    BTreeNode(int degree, bool isLeaf); // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int key);

    // A utility function to split the child y of this node. i is index of y in
    // child array children[].  The Child y must be full when this function is called
    void splitChild(int index, BTreeNode* node);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to search a key in the subtree rooted with this node.
    BTreeNode* search(int key); // returns NULL if k is not present.

    // A function that returns the index of the first key that is greater
    // or equal to k
    int findKey(int key);

    // A wrapper function to remove the key k in subtree rooted with
    // this node.
    void remove(int key);

    // A wrapper function to update the key value by k
    void updateByIndex(int index, int value);

    // A function to remove the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int index);

    // A function to remove the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int index);

    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    int getPredecessor(int index);

    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    int getSuccessor(int index);

    // A function to fill up the child node present in the idx-th
    // position in the children[] array if that child has less than degree-1 keys
    void fill(int index);

    // A function to borrow a key from the children[idx-1]-th node and place
    // it in children[idx]th node
    void borrowFromPrevious(int index);

    // A function to borrow a key from the children[idx+1]-th node and place it
    // in children[idx]th node
    void borrowFromNext(int index);

    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int index);

    // Make the BTree friend of this so that we can access private members of this
    // class in BTree functions
    friend class BTree;
};

#endif //ALGORITHMS_B_TREE_NODE_H
