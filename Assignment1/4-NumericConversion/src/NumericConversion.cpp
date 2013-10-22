/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: _ArnO_
 * Section: Nobody
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * Simple recursive functions to do simple stuff
 */

#include <iostream>
#include <string>
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
	string displayVarString = "ABC" + intToString(178) + "DEF";
	cout << displayVarString << endl;
	displayVarString = "ABC" + intToString(0) + "DEF";
	cout << displayVarString << endl;
	displayVarString = "ABC" + intToString(-17) + "DEF";
	cout << displayVarString << endl;
	int displayVarInt = stringToInt("-18");
	cout << displayVarInt + 2 << endl;
	displayVarInt = stringToInt("-1798876987");
	cout << displayVarInt + 2 << endl;
	return 0;
}

string intToString(int n) {
	string result;
	int thisFigure = abs(n) % 10;

	char thisFigureChar = (char)(thisFigure + 0x30);
	string thisFigureString = thisFigureChar + string();

	if ((n >= 0)&&(n < 10)) {
		// Base case #1
		result = thisFigureString;
	} else if ((n > -10)&&(n < 0)) {
		// Basde case #2
		result = "-" + thisFigureString;
	} else {
		int remainer = n / 10;
		result = intToString(remainer) + thisFigureString;
	}

	return result;
}

int stringToInt(string str) {
	int result, multSign = 1;
	bool isNegative = false;
	
	// Base case = one char for a figure + sign

	if (str[0] == '-')  {
		isNegative = true;
		multSign = -1;
	}

	int nbChar = str.length();
	// Single char conversion
	char thisChar = str[nbChar - 1];
	int thisCharInt	= (thisChar - 0x30) * multSign;

	if ((isNegative)&&(nbChar == 2)||(!isNegative)&&(nbChar == 1)) {
		// Base case = one char for a figure + sign
		result = thisCharInt;
	} else {
		// Recursive calls
		string remainer = str.substr(0, nbChar - 1);
		result = thisCharInt + 10 * stringToInt(remainer);
	}

	return result;
}

