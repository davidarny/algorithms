#include <cstring>
#include <iostream>
#include <stack>

#include "Tree.h"
#include "calculator.h"
#include "operator.h"

Tree::Tree(const TTreeValue& value)
    : value(value)
{
    left = nullptr;
    right = nullptr;
}

Tree* Tree::construct(char* expression)
{
    std::stack<Tree*> stack;
    Tree *root, *left, *right;

    for (int i = 0; i < strlen(expression); ++i) {
        auto ch = expression[i];
        auto isSpace = ch == Calculator::SPACE;
        auto isOperator = Calculator::isOperator(ch);
        if (isSpace) {
            continue;
        }
        if (!isOperator) {
            std::string identifier;
            while (!isOperator && !isSpace) {
                identifier += ch;
                i++;
                ch = expression[i];
                isSpace = ch == Calculator::SPACE;
                isOperator = ch == Calculator::isOperator(ch);
            }
            root = new Tree(identifier);
            stack.push(root);
        } else {
            root = new Tree(std::string{ ch });
            auto isUnaryPlus = ch == Operator::operators.at(Operator::UNARY_PLUS);
            auto isUnaryMinus = ch == Operator::operators.at(Operator::UNARY_MINUS);
            auto isUnarySign = isUnaryPlus || isUnaryMinus;
            if (isUnarySign) {
                left = stack.top();
                stack.pop();
                root->left = left;
            } else {
                left = stack.top();
                stack.pop();
                right = stack.top();
                stack.pop();

                root->left = left;
                root->right = right;
            }

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
        printf("%s %s\n", indent.data(), root->value.data());
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
