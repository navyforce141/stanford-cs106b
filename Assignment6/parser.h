/*
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module.
 */

#ifndef _parser_h
#define _parser_h

#include <string>
#include "exp.h"
#include "statement.h" // Added by _ArnO_

/*
 * Function: parseExp
 * Usage: Expression *exp = parseExp(scanner);
 * -------------------------------------------
 * Parses a complete expression from the specified TokenScanner object,
 * making sure that there are no tokens left in the scanner at the end.
 */

Expression *parseExp(TokenScanner & scanner);

/*
 * Function: readE
 * Usage: Expression *exp = readE(scanner, prec);
 * ----------------------------------------------
 * Reads and returns the next expression from the scanner, stopping when
 * it encounters an operator whose precedence is less than or equal to prec.
 */

Expression *readE(TokenScanner & scanner, int prec);

/*
 * Function: readT
 * Usage: Expression *exp = readT(scanner);
 * ----------------------------------------
 * Reads and returns the next term in an expression, which is either a
 * constant, a variable, or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner);

/*
 * Function: precedence
 * Usage: int prec = precedence(token);
 * ------------------------------------
 * Returns the precedence of the specified operator token.  If token does
 * not correspond to a legal operator, precedence returns 0.
 */

int precedence(std::string token);

// New parser for statement

Statement *parseStatement(TokenScanner & scanner);

#endif
