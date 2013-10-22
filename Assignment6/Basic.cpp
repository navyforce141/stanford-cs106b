/*
 * File: Basic.cpp
 * ---------------
 * Name: _ArnO_
 * Section: NoBody
 * This file is the starter project for Assignment #6 (BASIC).
 * Nice piece of work
 */

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "error.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvaluationContext & context);
void welcomeAnnouncement();
void quitCmd();
void helpCmd();
void listCmd(Program & program);
void clearCmd(Program & program);
void editPrgCmd(Program & program, int lineNumber, string & lineSource, TokenScanner & scanner);
void runCmd(Program & program, EvaluationContext context);

/* Main program */

int main() {
    EvaluationContext context;
    Program program;
    welcomeAnnouncement();
    while (true) {
        try {
            processLine(getLine(), program, context);
        } catch (ErrorException & ex) {
            cerr << "Error: " << ex.getMessage() << endl;
			cout << "Oops: " << ex.getMessage() << endl;
			cout << "Probably a malformed statement - try HELP" << endl;
        }
		cout << endl;
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, context);
 * -------------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvaluationContext & context) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.setInput(line);
	// Initial stumb code
    // Expression *exp = parseExp(scanner);
    // cout << exp->toString() << " evaluates to " << exp->eval(context) << endl;
    // delete exp;
	
	if (!scanner.hasMoreTokens()) {
		return;
	}

	string firstElement = scanner.nextToken();
	
	if (firstElement == "QUIT") {
		quitCmd();
		return;
	}
	
	if (firstElement == "HELP") {
		helpCmd();
		return;
	}

	if (firstElement == "LIST") {
		listCmd(program);
		return;
	}

	if (firstElement == "CLEAR") {
		clearCmd(program);
		return;
	}

	if (firstElement == "RUN") {
		runCmd(program, context);
		return;
	}

	if (firstElement == "PRINT" || firstElement == "LET" ||  firstElement == "INPUT") {
		scanner.saveToken(firstElement);
		Statement *stmt = parseStatement(scanner);
		stmt->execute(context);
		delete stmt;
		return;
	}

	if (firstElement == "DEBUG") {
		Expression *exp = parseExp(scanner);
		exp->eval(context);
		// cout << exp->toString() << " evaluates to " << exp->eval(context) << endl;
		delete exp;
		return;
	}

	if ((firstElement > "0")||(firstElement < "999999")) {
		int lineNumber = stringToInteger(firstElement);
		int numberPos = firstElement.length() + 1;
		int lineLength = line.length() - firstElement.length();
		string source;
		if (lineLength != 0) { // This test should be improved by just testing if there is something after
			source = line.substr(numberPos, lineLength);
		}
		editPrgCmd(program, lineNumber, source, scanner); // Try to pass only the scanner and no longer the source
		return;
	}

}

void welcomeAnnouncement() {
	cout << "Welcome to the BASIC interpreter. HELP for help." << endl;
}

void quitCmd() {
	cout << "Bye bye!" << endl;
	exit(0);
}

void helpCmd() {
	cout << "List of command:" << endl;
	cout << "  HELP - Display help (this menu) (D)" << endl;
	cout << "  QUIT - Exit, all data lost (D)" << endl;
	cout << "  LIST - Display program (D)" << endl;
	cout << "  NNN Statement - Insert/overwrite a program line at NNN (D)" << endl;
	cout << "  NNN - Delete program line NNN (D)" << endl;
	cout << "  PRINT - Display statement (D)(P)" << endl;
	cout << "  LET - Assign statement (D)(P)" << endl;
	cout << "  INPUT - Get integer statement (D)(P)" << endl;
	cout << "  GOTO nn - Move to line nn (P)" << endl;
	cout << "  IF stmt (comp) stmt THEN nn - Compare and go to line nn (P)" << endl;
	cout << "  END - Stop execution (optional at the end) (P)" << endl;
	cout << "  REM - Comment line, do not trigger anything (P)" << endl;
	cout << "(D) = direct mode / (P) = program mode" << endl;
}

void listCmd(Program & program) {
	int lineNumber = program.getFirstLineNumber();
	if (lineNumber == -1) {
		cout << "No program lines" << endl;
	} else {
		while (lineNumber != -1) {
			string source = program.getSourceLine(lineNumber);
			cout << lineNumber << " " << source << endl;
			lineNumber = program.getNextLineNumber(lineNumber);
		}
	}
}

void clearCmd(Program & program) {
	program.clear();
}

void editPrgCmd(Program & program, int lineNumber, string & lineSource, TokenScanner & scanner) {
	// lineSource and scanner have the same information ... should be improved (see check on the source before the call)
	if (lineSource == "") {
		program.removeSourceLine(lineNumber);
	} else {
		program.addSourceLine(lineNumber, lineSource);
		Statement *currentStmt = parseStatement(scanner);
		program.setParsedStatement(lineNumber, currentStmt);
	}
}

void runCmd(Program & program, EvaluationContext context) {
	int lineNumber = program.getFirstLineNumber();
	while (lineNumber != -1) {
		Statement *currentStmt = program.getParsedStatement(lineNumber);
		lineNumber = program.getNextLineNumber(lineNumber);
		context.setCurrentLine(lineNumber);
		currentStmt->execute(context);
		lineNumber = context.getCurrentLine();
	}
}