/*
Author: Grant Hughes
Created: March 26, 2025

testTree.cpp:
    - Implementation for printing the parse tree
*/

#include <iostream>
#include <string>

#include "testTree.hpp"

using namespace std;

void printTree(node* root, int indent)
{
    indent = 0; // start with no indent

    // base case
    if (root == nullptr)
        return;
    
    for (int i = 0; i < indent; i++)
    {
        cout << " ";
    }
    // print node
    cout << root << endl;

    // chekcing if root has content
    if (!root->tokenInstance.empty())
    {
        cout << " " << root->tokenInstance;
    }
    cout << endl;

    for (node* children: root->child)
    {
        printTree(children, indent + 4);
    }
}