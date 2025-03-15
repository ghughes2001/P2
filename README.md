# P2

P2: Parser and Tree Builder
Due Wednesday, April 2, 2025
• Implement parser and tree builder for the provided grammar (see below).
• Have your parser generate error (line number and tokens involved) or print parse tree upon successful
parse.
• Use your scanner module and fix if needed.
• Invocation:
P2 [file]
o As in previous projects, a filename may be specified or the information can be read from stdin
o Wrong invocations will not be graded
o Program must compile and run on hellbender
• Additional requirements:
o Implement the parser in a separate file (parser.cpp and parser.h) including the initial auxiliary
parser() function and all nonterminal functions.
o Call the parser function from main.
o The parser function generates error or returns the parse tree to main.
o In testTree.cpp (and testTree.h) implement a printing function using preorder traversal with
indentations as before (P0) for testing purposes (4 spaces per level, print the node's label and
any decorations (e.g. specific ID name) from the node; one node per line).
o Call the printing function from main immediately after calling the parser and returning the tree.
o The printing function call must be later removed for P3 unless debugging.
BNF
(Please ensure this uses only tokens detected in your P1, no exceptions.)
S is the starting nonterminal. Lowercase and punctuation marks are terminals, uppercase letters represent
nonterminals, and the pipe symbol ‘|’ separates the production rule options.
S -> A ( B B )
A -> “ t2 | empty
B -> S | C | D | E | G
C -> # t2 | ! F
D -> $ F
E -> ‘ F F F B
F -> t2 | t3 | & F F
G -> t2 % F
Lexical Definitions (same as project P1)
• Case sensitive
• Comments start with * and end with *
• Alphabet:
o All upper- and lower-case English letters, digits, plus the extra characters as shown below, plus
white space
o No other characters are allowed and they must generate errors
o Each scanner error must display "SCANNER ERROR:" followed by input string and line number
• Token type t1
o ! “ # $ % & ‘ ( ) // these characters correspond to ascii numbers 33 to 41
• Token type t2
o Begin with a single +
o followed by one or more digits (0-9)
 e.g. +0, +1000, are all valid; while +, +3+, 10, ++1 are all invalid tokens
• Token type t3
o Begin with single letter, (a-z, A-Z)
o Followed by one or more digits (0-9)
 e.g. b0, Z421, x1000, Y00 are all valid and z, b&3, 10, cd1, a+95 are all invalid tokens
P2 Suggestions
• Ensure the grammar is LL(k=1).
• Note that the parser calls the scanner, but the parser may need some setup in main.
• Implement the parser in two iterations:
o Starting without the parse tree.
 Have your parser generate error (line number and tokens involved) or print OK message
upon successful parse.
 For each <nonterminal>, use a void function named after the nonterminal and use only
explicit returns.
 Decide how to pass the token.
 Have the main program call the parser, after setting up the scanner.
 Be systematic: assume each function starts with unconsumed token (not matched yet)
and returns unconsumed token.
 Use version control and be ready to revert if something gets messed up.
o Only after completing and testing the above to satisfaction, modify each function to build a
subtree, and return its root node.
 Assume each function builds just the root and connects its subtrees.
 Modify the main function to receive the tree built in the parser, and then display it (for
testing) using the preorder treePrint().
• Some hints for tree:
o Every node should have a label consistent with the name of the function creating it (equal to
the name?)
o Every function creates exactly one tree node (or possibly none)
o All token strings need to be stored and specified on the leaf nodes of the tree
o When storing a token, you may need to make a copy depending on your interface
Testing
• Create files using the grammar to generate programs, starting with simplest programs, adding one
different statement at a time and then building sequences of statements and nested statements.
• Make sure to have sequences of statements, nested statements, and to test all production rules.
• You may skip comments but then test comments in some files.
• Feel free to share test files with others and compare output.
• Some example test files:
Example 1 input:
( # +136 $ +136 )
S
A
empty
t1 (
B
C
t1 #
t2 +136
B
D
t1 $
F
t2 +136
t1 )
Example 2 input:
“ +5 ( +5 % k10 $ +5 )
S
A
“
t2 +5
t1 (
B
G
B
D
t2 +5
t1 %
F
t3 k10
t1 $
F
t2 +5
t1 )
Example 3 input:
( ( # +39 ! +39 ) $ +39 )
S
A
empty
t1 (
B
S
A
empty
t1 (
B
C
t1 #
t2 +39
B
C
t1 !
F
t2 +39
t1 )
B
D
t1 $
F
t2 +39
t1 )
Example 4 input:
“ +91 ( ‘ J100 +91 W4 $ & J100 +91 +91 %
J100 )
S
A
t1 “
t2 +91
t1 (
B
E
t1 ‘
F
F
F
B
t3 J100
t2 +91
t3 W4
D
t1 $
F
t1 &
F
F
t3 J100
t2 +91
B
G
t2 +91
t1 %
F
t3 J100
t1 )
