/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In the finished
 * version, this file will also specify subclasses for each of the
 * statement types.  As you design your own version of this class,
 * you should pay careful attention to the exp.h interface specified
 * in Chapter 19, which is an excellent model for the Statement class
 * hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "exp.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(context);
 * ------------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvaluationContext object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvaluationContext & context) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

// PRINT
class PrintStmt: public Statement {

public:

	PrintStmt(TokenScanner & scanner);
	virtual ~PrintStmt();
	virtual void execute(EvaluationContext & context);

private:

	Expression *exp;
};

// LET
class LetStmt: public Statement {

public:

	LetStmt(TokenScanner & scanner);
	virtual ~LetStmt();
	virtual void execute(EvaluationContext & context);

private:

	string variableName;
	Expression *exp; // Will store what comes after the '=' token

};

// INPUT
class InputStmt: public Statement {

public:

	InputStmt(TokenScanner & scanner);
	virtual ~InputStmt();
	virtual void execute(EvaluationContext & context);

private:

	string variableName;

};

// GOTO
class GoToStmt: public Statement {

public:

	GoToStmt(TokenScanner & scanner);
	virtual ~GoToStmt();
	virtual void execute(EvaluationContext & context);

private:

	int nextLine;

};

// IF
class IfStmt: public Statement {

public:

	IfStmt(TokenScanner & scanner);
	virtual ~IfStmt();
	virtual void execute(EvaluationContext & context);

private:

	Expression *exp1;
	Expression *exp2;
	string token;
	int nextLine;

};

// END
class EndStmt: public Statement {

public:

	EndStmt(TokenScanner & scanner);
	virtual ~EndStmt();
	virtual void execute(EvaluationContext & context);

private:

};

// REM (easy one for the last statement)
class RemStmt: public Statement {

public:

	RemStmt(TokenScanner & scanner);
	virtual ~RemStmt();
	virtual void execute(EvaluationContext & context);

private:

	// Empty

};

#endif