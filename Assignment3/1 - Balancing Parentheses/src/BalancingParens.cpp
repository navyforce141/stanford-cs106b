/*
 * File: BalancingParens.cpp
 * -------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the balancing parentheses problem on
 * Assignment #3
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

bool isBalanced(string exp);
bool containsBrakets(string & exp);
bool containsBraketsType(string & brakets, string & exp);
string removeBrakets(string & exp);
string removeBraketsType(string & brakets, string & exp);

/* Main program */

int main() {
    cout << " " << isBalanced (string("")) << endl;
	cout << "{} " << isBalanced (string("{}")) << endl;
	cout << "{) " << isBalanced (string("{)")) << endl;
	cout << "({}[]) " << isBalanced (string("({}[])")) << endl;
	cout << "({}[])) " << isBalanced (string("({}[]))")) << endl;
	cout << "{}[] " << isBalanced (string("{}[]")) << endl;
	cout << "((({})[]){[]})" << isBalanced (string("((({})[]){[]})")) << endl;
    return 0;
}

/*
 * Function: isBalanced
 * Usage: if (isBalanced(exp)) . . .
 * ---------------------------------
 * Returns true if the string exp is balanced, which means that it
 * is either (a) empty or (b) contains a consecutive paired operator
 * and the string is balanced if you remove that operator.
 */
bool isBalanced(string exp) {
	bool result = false;
	
	if (exp.empty()) {
		// Base case
		result = true;
	} else if (containsBrakets(exp)) {
		// Recursive calls
		string next = removeBrakets(exp);
		result = isBalanced(next);
	}

	// Another base case: not empy, no brakets and not balanced = false (default for result)
    return result;
}

bool containsBrakets(string & exp) {
	return (containsBraketsType(string("()"), exp)||containsBraketsType(string("{}"), exp)||containsBraketsType(string("[]"), exp));
}

bool containsBraketsType(string & brakets, string & exp) {
	int braketPos = exp.find(brakets);
	return (braketPos != -1);
}

string removeBrakets(string & exp) {
	string brakets, result = exp;
	if (containsBraketsType(string("()"), exp)) {
		brakets = "()";
	} else if (containsBraketsType(string("{}"), exp)) {
		brakets = "{}";
	} else if (containsBraketsType(string("[]"), exp)) {
		brakets = "[]";
	}
	
	if (!brakets.empty()) {
		result = removeBraketsType(brakets, exp);
	}

	return result;
}

string removeBraketsType(string & brakets, string & exp) {
	int braketPos = exp.find(brakets);
	string result = exp;
	result = exp.erase(braketPos, 2);
	return result;
}
