#ifndef ALGORITHMS_TREE_H
#define ALGORITHMS_TREE_H

class Tree {
private:
    static const unsigned INITIAL_DEPTH = 1;
    static const char INDENT = '-';

    char value;
    Tree* left;
    Tree* right;
    unsigned depth;

    static void fillDepthLevels(Tree* root, unsigned depth);

public:
    explicit Tree(char value);

    static Tree* construct(char* pExpression);

    static void print(Tree* root);
};

#endif //ALGORITHMS_TREE_H
