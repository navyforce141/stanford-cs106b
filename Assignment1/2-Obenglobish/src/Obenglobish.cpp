/*
 * File: Obenglobish.java
 * ----------------------
 * Name: _ArnO_
 * Section: Nobody
 * This file is the starter project for the Obenglobish problem.
 * The program translate English words to Obenglobish
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "strlib.h"
using namespace std;

// Functions declarations
bool isVowel(char ch);
string obenglobish(string wordToTranslate);

// Main program
int main() {
	
	while (true) {
		string word = getLine("Enter a word: ");
		if (word == "") break;
		string trans = obenglobish(word);
		cout << word << " -> " << trans << endl;
	}
	
	return 0;
}

bool isVowel(char ch) {
	// Return true for vowels
	return (ch == 'a')||(ch == 'e')||(ch == 'i')||(ch == 'o')||(ch == 'u')||(ch == 'y');
}

string obenglobish(string wordToTranslate) {
	string wordTranslated;
	bool lastCharIsVowel = false;

	int maxValue = wordToTranslate.length() - 1;
	for (int i = 0; i < maxValue; i++) {
		if (isVowel(wordToTranslate[i]) && !lastCharIsVowel) {
			wordTranslated += "ob";
			lastCharIsVowel = true;
		} else {
			lastCharIsVowel = false;
		}
		wordTranslated += wordToTranslate[i];
	}
	wordTranslated += wordToTranslate[maxValue];

	return wordTranslated;
}