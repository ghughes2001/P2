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

// prototypes
node* S();
node* A();
node* B();

// helper function to return current token
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

// helper fucntion to return errors in grammer
void parsingError(const string& expected) {
    Token current = currentToken();
    cout << "PARSER ERROR: Expected " << expected << ", got '" 
         << current.tokenInstance << "' on line " << current.lineNumber << endl;
    exit(1);
}

// return the next token
void nextToken()
{
    if (tokenSize < tokens.size())
    {
        tokenSize++;
    }
}

// S -> A(BB)
node* S()
{
    node* nodeForS = new node("S"); // creating non-terminal S(root)

    nodeForS->addChildren(A()); // creating A (non-terminal)(node)

    if (currentToken().tokenInstance == "(")
    {
        node* leftParenthesis = new node("t1", "("); // creating left parenth
        nodeForS->addChildren(leftParenthesis); // adding left penth to tree as child
        nextToken();
    }
    else
    {
        parsingError("(");
    }
    // adding the two B non-terminals
    nodeForS->addChildren(B());
    nodeForS->addChildren(B());

    // handing the end parenth (')')
    if (currentToken().tokenInstance == ")")
    {
        node* rightParenthesis = new node("t1", ")"); // creating right parenth
        nodeForS->addChildren(rightParenthesis); // adding right penth to tree as child
        nextToken();
    }
    else
    {
        parsingError(")");
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
            parsingError("Needs t2tk");
        }
    }
    else
    {
        node* empty = new node("EMPTY");
        nodeForA->addChildren(empty); // add the empty node as child
    }
    // return either (" t2) or (empty) node
    return nodeForA;
}

node* B()
{
    node* nodeForB = new node("B"); // creating non-terminal B node

    
}