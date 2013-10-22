/*
 * File: ListCompletions.cpp
 * -------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the cell phone mind-reading problem on
 * Assignment #3
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
using namespace std;

/* Constants */

const string alphabet = "abcdefghijklmnopqrstuvwxyz";

/* Function prototypes */

void listCompletions(string digits, Lexicon & lex);
string translateDigitToLetter(char digit);
void recLettersCombination(string prefix, string digits, Lexicon & lex);
void recFindWords(string letters, Lexicon & lex);

/* Main program */

int main() {
    Lexicon english("EnglishWords.dat");
    cout << "Cell phone mind-reading problem" << endl;
    while (true) {
        cout << "Enter a set of digits: ";
        string digits = getLine();
        if (digits == "" || digits == "quit") break;
        cout << "The words beginning with those digits are:" << endl;
        listCompletions(digits, english);
    }
    return 0;
}

/*
 * Function: listCompletions
 * Usage: listCompletions(digits, lex);
 * ------------------------------------
 * Lists all the words in the lexicon that begin with the letters
 * corresponding to the specified digits on a telephone keypad.
 */
void listCompletions(string digits, Lexicon& lex) {
    recLettersCombination("", digits, lex);
}

string translateDigitToLetter(char digit) {
	string result;

	switch (digit) {
		case '2':
			result = "abc";
			break;
		case '3':
			result = "def";
			break;
		case '4':
			result = "ghi";
			break;
		case '5':
			result = "jkl";
			break;
		case '6':
			result = "mno";
			break;
		case '7':
			result = "pqrs";
			break;
		case '8':
			result = "tuv";
			break;
		case '9':
			result = "wxyz";
			break;
		default:
			result = "";
			break;
	}
	
	return result;
}

void recLettersCombination(string prefix, string digits, Lexicon & lex) {
	string currentLetters;

	if (digits.empty()) {
		// Base case
		recFindWords(prefix, lex);
	} else {
		// Recursive calls
		char currentDigit = digits[0];
		string nextDigits = digits.substr(1, (digits.length() - 1));
		currentLetters = translateDigitToLetter(currentDigit);
		for (size_t i = 0; i < currentLetters.length(); i++) {
			recLettersCombination((prefix + currentLetters[i]), nextDigits, lex);
		}
		if (currentLetters.empty()) {
			recLettersCombination(prefix, nextDigits, lex);
		}
	}
}

void recFindWords(string letters, Lexicon & lex) {

	if (lex.contains(letters)) {
		cout << letters << endl;
	}

	if (lex.containsPrefix(letters)) {
		// Recursive calls
		for (size_t i = 0; i < alphabet.length(); i++) {
			recFindWords(letters + alphabet[i], lex);
		}
	}
}