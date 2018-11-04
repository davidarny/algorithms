#include <cstring>
#include <iostream>
#include <stack>

#include "Tree.h"
#include "calculator.h"

Tree::Tree(char value)
    : value(value)
{
    left = nullptr;
    right = nullptr;
}

Tree* Tree::construct(char* pExpression)
{
    std::stack<Tree*> stack;
    Tree *root, *left, *right;

    for (int i = 0; i < strlen(pExpression); ++i) {
        auto ch = pExpression[i];
        if (ch == Calculator::SPACE) {
            continue;
        }
        if (!Calculator::isOperator(ch)) {
            root = new Tree(ch);
            stack.push(root);
        } else {
            root = new Tree(ch);
            left = stack.top();
            stack.pop();
            right = stack.top();
            stack.pop();

            root->left = left;
            root->right = right;

            stack.push(root);
        }
    }

    root = stack.top();
    stack.pop();

    fillDepthLevels(root, INITIAL_DEPTH);

    return root;
}

void Tree::print(Tree* root)
{
    if (root) {
        std::string indent(root->depth, INDENT);
        printf("%s %c\n", indent.data(), root->value);
        print(root->left);
        print(root->right);
    }
}

void Tree::fillDepthLevels(Tree* root, unsigned depth)
{
    if (root) {
        root->depth = depth;
        unsigned nextDepth = depth + INITIAL_DEPTH;
        fillDepthLevels(root->left, nextDepth);
        fillDepthLevels(root->right, nextDepth);
    }
}
