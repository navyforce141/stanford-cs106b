/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "parser.h" // Added by _ArnO_
#include "simpio.h" // Added by _ArnO_

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}

// PRINT statement
PrintStmt::PrintStmt(TokenScanner & scanner) {
	exp = readE(scanner, 0);
	if (scanner.hasMoreTokens()) {
		error("Extraneous token " + scanner.nextToken());
	}
}

PrintStmt::~PrintStmt() {
	delete exp;
}

void PrintStmt::execute(EvaluationContext & context) {
	cout << exp->eval(context) << endl;
};

// LET statement
LetStmt::LetStmt(TokenScanner & scanner) {
	variableName = scanner.nextToken();
	string tokenEq = scanner.nextToken();
	exp = readE(scanner, 0);
	if (scanner.hasMoreTokens()) {
		error("Extraneous token " + scanner.nextToken());
	}
}

LetStmt::~LetStmt() {
	delete exp;
}

void LetStmt::execute(EvaluationContext & context) {
	context.setValue(variableName, exp->eval(context));
};

// INPUT statement
InputStmt::InputStmt(TokenScanner & scanner) {
	variableName = scanner.nextToken();
	if (scanner.hasMoreTokens()) {
		error("Extraneous token " + scanner.nextToken());
	}
}

InputStmt::~InputStmt() {
}

void InputStmt::execute(EvaluationContext & context) {
	int value = getInteger("  ?  ");
	context.setValue(variableName, value);
};

// GOTO statement
GoToStmt::GoToStmt(TokenScanner & scanner) {
	nextLine = stringToInteger(scanner.nextToken());
	if (scanner.hasMoreTokens()) {
		error("Extraneous token " + scanner.nextToken());
	}
}

GoToStmt::~GoToStmt() {
}

void GoToStmt::execute(EvaluationContext & context) {
	context.setCurrentLine(nextLine);
};

// IF statement
IfStmt::IfStmt(TokenScanner & scanner) {
	exp1 = readE(scanner, 0);
	token = scanner.nextToken();
	exp2 = readE(scanner, 0);
	if (scanner.nextToken() != "THEN") {
		error("Malformed IF statement");
	}
	nextLine = stringToInteger(scanner.nextToken());
	if (scanner.hasMoreTokens()) {
		error("Extraneous token " + scanner.nextToken());
	}
}

IfStmt::~IfStmt() {
	delete exp1;
	delete exp2;
}

void IfStmt::execute(EvaluationContext & context) {
	if (token == "=") {
		if (exp1->eval(context) == exp2->eval(context)) context.setCurrentLine(nextLine);
		return;
	}

	if (token == "<") {
		if (exp1->eval(context) < exp2->eval(context)) context.setCurrentLine(nextLine);
		return;
	}

	if (token == ">") {
		if (exp1->eval(context) > exp2->eval(context)) context.setCurrentLine(nextLine);
		return;
	}

	// Pretty ugly piece of code, but did not find any way to confirm a string into a boolean condition

};

// END statement
EndStmt::EndStmt(TokenScanner & scanner) {
	if (scanner.hasMoreTokens()) {
		error("Extraneous token " + scanner.nextToken());
	}
}

EndStmt::~EndStmt() {
}

void EndStmt::execute(EvaluationContext & context) {
	context.setCurrentLine(-1);
};

// REM statement
RemStmt::RemStmt(TokenScanner & scanner) {
}

RemStmt::~RemStmt() {
}

void RemStmt::execute(EvaluationContext & context) {
};