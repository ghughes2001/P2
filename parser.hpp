/*
Author: Grant Hughes
Created: March 16, 2025

parser.hpp:
    - Parser interface for BNF grammar
*/

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <string>
#include "node.hpp"

node* Parser(const std::string &file);

#endif