/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
	initProgram();
	cursor = header;
}

Program::~Program() {
	deleteProgram();
}

void Program::clear() {
	deleteProgram();
	initProgram();
	cout << "Program deleted" << endl;
}

void Program::addSourceLine(int lineNumber, string line) {
	// Cursor positionned at the new line position (in the recursive function)
	
	// Fabulous recursive insert
	recInsertSorted(header, lineNumber, line);
}

void Program::removeSourceLine(int lineNumber) {
	recDeleteFromList(header, lineNumber);
}

string Program::getSourceLine(int lineNumber) {
	// The cursor should be at the lineNumber position
	// Otherwise the funtion modules have not been called in sequence
	if (cursor->number == lineNumber) {
		return cursor->source; // We could imagine to reposition the cursor ... better to use this damn module function in sequence
	} else {
		cout << "getSourceLine: cursor not in the right position" << endl;
	}
    return "";
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) { 
	// This function is working only if the cursor is on the line lineNumber
	if (cursor->number == lineNumber) {
		cursor->lineStmt = stmt;
	} else {
		cout << "setParsedStatement: cursor not in the right position" << endl;
	}
}

Statement *Program::getParsedStatement(int lineNumber) {
	// Return parsed statement AND position cursor if required

	if (cursor->number != lineNumber) {
		//cout << "getNextLineNumber: cursor not in the right position" << endl;
		positionCursor(lineNumber);
		//cout << "New position: " << cursor->number << endl;
	}
	if (cursor != NULL) {
		return cursor->lineStmt;
	}

	return NULL;
}

int Program::getFirstLineNumber() {
	// Return the first number and PUT the cursor on the FIRST line
	if (header->next != NULL) {
			cursor = header->next;
			return cursor->number;
	} else {
		return -1;
	}
}

int Program::getNextLineNumber(int lineNumber) {
	// Return the next number and MOVE the cursor
	// Can position the cursor if required

	if (cursor->number != lineNumber) {
		//cout << "getNextLineNumber: cursor not in the right position" << endl;
		positionCursor(lineNumber);
		//cout << "New position: " << cursor->number << endl;
	}

	if (cursor->next == NULL) {
		return -1;
	} else {
		SourceLine *next = cursor->next;
		cursor = next; // Move cursor
		return cursor->number; // Hum, since the cursor has been moved to the next number
	}
    return -1;
}

void Program::recInsertSorted(SourceLine * & program, int lineNb, string source) {
	// From the CS106B reader - very nice recursive peace of code
	// Insert OR modify of number existing
	// Adapated to handle the line modification

	if (program == NULL || lineNb < program->number) {
		// Create a new line
		SourceLine *newLine = new SourceLine;
		newLine->number = lineNb;
		newLine->source = source;
		newLine->next = program;
		program = newLine;
		cursor = newLine;
		cout << "New Line added" << endl;
	} else if (lineNb == program->number) {
		program->source = source;
		cursor = program;
		cout << "Line modified" << endl;
	} else {
		recInsertSorted(program->next, lineNb, source);
	}
}

void Program::recDeleteFromList(SourceLine * & program, int lineNumber) {
	// From the CS106B reader - very nice recursive peace of code too

	if (program != NULL) {
		if (program->number == lineNumber) {
			SourceLine *toDelete = program;
			program = program->next; 
			delete toDelete;
			cout << "Entry deleted" << endl;
		} else {
			recDeleteFromList(program->next, lineNumber);
		}
	}
}

void Program::initProgram() {
	// This function initiate the header with consistant data
	header = new SourceLine;
	header->number = 0;
	header->next = NULL;
}

void Program::deleteProgram() {
	// This function delete the whole program lines
	while (header != NULL) {
		SourceLine *next = header->next;
		delete header;
		header = next;
	}
}

void Program::positionCursor(int lineNumber) {
	// May be used when the cursor is not on lineNumber
	// Called when cursor lost
	
	cursor = NULL;
	if (header->next == NULL) return;

	cursor = header;
	while (cursor != NULL) {
		if (cursor->number == lineNumber) break;
		cursor = cursor->next;
	}
}

