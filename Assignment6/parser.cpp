/*
 * File: parser.cpp
 * ----------------
 * This file implements the parser.h interface.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "exp.h"
#include "parser.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner & scanner) {
    Expression *exp = readE(scanner, 0);
    if (scanner.hasMoreTokens()) {
        error("Unexpected token \"" + scanner.nextToken() + "\"");
    }
    return exp;
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * The implementation of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each level, the parser reads operators and subexpressions
 * until it finds an operator whose precedence is greater than the prevailing
 * one.  When a higher-precedence operator is found, readE calls itself
 * recursively to read that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int prec) {
    Expression *exp = readT(scanner);
    string token;
    while (true) {
        token = scanner.nextToken();
        int tprec = precedence(token);
        if (tprec <= prec) break;
        Expression *rhs = readE(scanner, tprec);
        exp = new CompoundExp(token, exp, rhs);
    }
    scanner.saveToken(token);
    return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner) {
    string token = scanner.nextToken();
    TokenType type = scanner.getTokenType(token);
    if (type == WORD) return new IdentifierExp(token);
    if (type == NUMBER) return new ConstantExp(stringToInteger(token));
    if (token != "(") error("Unexpected token \"" + token + "\"");
    Expression *exp = readE(scanner, 0);
    if (scanner.nextToken() != ")") {
        error("Unbalanced parentheses");
    }
    return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token) {
    // if (token == "=") return 1; // With this comment the parser should no longer manage '='
    if (token == "+" || token == "-") return 2;
    if (token == "*" || token == "/") return 3;
    return 0;
}

// Code for statement parser by _ArnO_

Statement *parseStatement(TokenScanner & scanner) {
	string token = scanner.nextToken();
	if (token == "PRINT") return new PrintStmt(scanner);
	if (token == "LET") return new LetStmt(scanner);
	if (token == "INPUT") return new InputStmt(scanner);
	if (token == "GOTO") return new GoToStmt(scanner);
	if (token == "IF") return new IfStmt(scanner);
	if (token == "END") return new EndStmt(scanner);
	if (token == "REM") return new RemStmt(scanner);
	cout << "Not a legal statement" << endl;
	return NULL;
}