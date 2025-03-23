/*
Author: Grant Hughes
Created: March 23, 2025

parser.hpp:
    - Implamentation of parser interface for BNF grammar
*/

#include "scanner.hpp"
#include "token.hpp"
#include "node.hpp"
#include "parser.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// global varaibels to track tokens
static vector<Token> tokens;
static size_t tokenSize = 0;

// return current token
Token& currentToken()
{
    if (tokenSize < tokens.size())
    {
        return tokens[tokenSize];
    }
    // otherwise retunr EOF
    static Token EOFToken(EOFTk, "EOF", -1);
    return EOFToken;
}

// return the next token
void nextToken()
{
    if (tokenSize < tokens.size())
    {
        tokenSize++;
    }
}

node* A()
{
    node* nodeForA = new node("A"); //creating non-terminal A

    if (currentToken().tokenInstance == "\"")
    {
        node* quote = new node("t1", "\"");
        nodeForA->addChildren(quote); // add node for "
        nextToken(); // move to next token

        // now at t2 since we had a "
        if (currentToken().tokenID == t2_tk)
        {
            node* tokenTwo = new node("t2", currentToken().tokenInstance);
            nodeForA->addChildren(tokenTwo); // add node for t2
            nextToken();
        }
        else
        {
            // missing t2 token so error in tree
            parsingError
        }
    }
}

// S -> A(BB)
node* s()
{
    node* nodeForS = new node("S"); // creating non-terminal S(root)

    nodeForS->addChildren(A()); // creating A (non-terminal)(node)


}