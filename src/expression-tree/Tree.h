#ifndef ALGORITHMS_TREE_H
#define ALGORITHMS_TREE_H

#include <string>

using TTreeValue = std::string;

class Tree {
private:
    static const unsigned INITIAL_DEPTH = 1;
    static const char INDENT = '-';

    TTreeValue value;
    Tree* left;
    Tree* right;
    unsigned depth;

    static void fillDepthLevels(Tree* root, unsigned depth);

public:
    explicit Tree(const TTreeValue& value);

    static Tree* construct(char* pExpression);

    static void print(Tree* root);
};

#endif //ALGORITHMS_TREE_H
