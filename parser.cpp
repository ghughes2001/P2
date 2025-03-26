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
node* C();
node* D();
node* E();
node* F();

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
            parsingError("Needs t2Tk");
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

    Token current  = currentToken(); // getting current token

    // adding S
    if (current.tokenInstance == "\"" || current.tokenInstance == "(")
    {
        nodeForB->addChildren(S());
    }
    // adding C non-terminal
    if (current.tokenInstance == "#" || current.tokenInstance == "!")
    {
        nodeForB ->addChildren(C());
    }
    // adding D non-terminal
    if (current.tokenInstance == "$")
    {
        nodeForB->addChildren(D());
    }
    // adding E non-terminal
    if (current.tokenInstance == "'")
    {
        nodeForB->addChildren(E());
    }
    // returning one of the B options
    return nodeForB;
}

node* C()
{
    node* nodeForC = new node("C"); // creating C non-terminal node

    if (currentToken().tokenInstance == "#") {
        node* hashNumber = new node("t1", "#");
        nodeForC->addChildren(hashNumber);
        nextToken();
        
        // next token is t2
        if (currentToken().tokenID == t2_tk) {
            node* t2 = new node("t2", currentToken().tokenInstance);
            nodeForC->addChildren(t2);
            nextToken();
        } else {
            parsingError("Need t2Tk");
        }
    }
    else if (currentToken().tokenInstance == "!") {
        node* exclamation = new node("t1", "!");
        nodeForC->addChildren(exclamation);
        nextToken();
        
        // Parse F
        nodeForC->addChildren(F());
    } else {
        parsingError("Need '#' or '!' for C non-terminal");
    }
    // returnng one of the temrinals
    return nodeForC;
}

node* D()
{
    node* nodeForD = new node("D"); // creating D non-terminal node

    if (currentToken().tokenInstance == "$")
    {
        node* dollar = new node("t1", "$"); // creating dollar node
        nodeForD->addChildren(dollar); // adding dollar node
        nextToken();

        // adding/creating F non-temrinal node
        nodeForD->addChildren(F());
    }
    else
    {
        parsingError("Need $ for D non-terminal");
    }
    // returning the result
    return nodeForD;
}

node* E()
{
    node* nodeForE = new node("E"); // adding non-temrinal node E

    if (currentToken().tokenInstance == "'")
    {
        node* quote = new node("t1", "'"); // creating node for quote
        nodeForE->addChildren(quote); // adding quote as child for E
        nextToken();

        // adding the F's non-terminal node
        nodeForE->addChildren(F()); // first E
        nodeForE->addChildren(F()); // second E
        nodeForE->addChildren(F()); // third E

        // adding the B non-temrinal node
        nodeForE->addChildren(B());
    }
    else
    {
        parsingError("Need \"'\" for E non-terminal grammar");
    }
    // return result
    return nodeForE;
}

node* F()
{
    
}