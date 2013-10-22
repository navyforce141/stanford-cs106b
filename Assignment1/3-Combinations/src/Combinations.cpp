/*
 * File: Combinations.cpp
 * ----------------------
 * Name: _ArnO_
 * Section: Nobody
 * This file is the starter project for the recursive combinations problem.
 * Finally the program displays the Pascal's triangle
 */

#include <iostream>
#include "simpio.h"
#include "strlib.h"
using namespace std;

// Constants declarations
const int NB_LINES = 17;

// Functions declarations
string displayPascalLine(int n);
int recCombination(int n, int k);
string fillSpaces(int nbChar);

int main() {
	int maxLength = displayPascalLine(NB_LINES).length();
	for (int i = 0; i < NB_LINES; i++) {
		int currentLength = displayPascalLine(i).length();
		cout << fillSpaces((maxLength - currentLength) / 2);
		cout << displayPascalLine(i) << endl;
	}
	return 0;
}

string displayPascalLine(int n) {
	int i = 0;	
	string filler;
	while (true) {
		int currentCombination = recCombination(n, i);
		filler += integerToString(currentCombination);
		if (i < n) {
			filler += " ";
			i++;
		} else {
			break;
		}
	}
	return filler;		
}

int recCombination(int n, int k) {
	int value;
	if ((k == 0)||(k == n)) {
		value = 1;
	} else {
		value = recCombination((n - 1), (k - 1)) + recCombination((n - 1), k);
	}

	return value;
}

string fillSpaces(int nbChar) {
	string filler;
	for (int i = 0; i < nbChar; i++) {
		filler += " ";
	}

	return filler;
}