/*
 * File: WordLadder.cpp
 * --------------------
 * Name: _ArnO_
 * Section: Nobody
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * ...
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

// Constants declarations
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

// Functions declarations
void getLadderParameters(string &startW, string &destW, Lexicon &lexicon);
Vector<string> getNextWords(string &word, Lexicon &lexicon);
bool isAlreadyUsed(string word, Vector<string> &usedWords);
void displaySolution(Vector<string> &solutionLadder);

int main() {
	Lexicon english("EnglishWords.dat");
	
	while (true) {

		string startWord, destWord;
		getLadderParameters(startWord, destWord, english);

		if (startWord != "") {

			Vector<string> usedWords; // Could have been managed in a set
			Vector<string> ladder;
			Queue<Vector<string>> allLadders;

			usedWords.add(startWord);
			ladder.add(startWord); // Initialize first ladder
			// TODO one day: create a function for ladder resolution
			allLadders.enqueue(ladder);
			ladder.clear();

			while (!allLadders.isEmpty()) {

				Vector<string> currentLadder = allLadders.dequeue();
				string lastLadderWord = currentLadder[(currentLadder.size() - 1)];
				if (lastLadderWord == destWord) {
					// Ladder found
					ladder = currentLadder;
					break;
				}

				Vector<string> nextWords = getNextWords(lastLadderWord, english);
			
				for (int i = 0; i < nextWords.size(); i++) {
					if (!isAlreadyUsed(nextWords[i], usedWords)) {
						Vector<string> nextLadder = currentLadder;
						nextLadder.add(nextWords[i]);
						allLadders.enqueue(nextLadder);
						usedWords.add(nextWords[i]);
					}
				}
			}

			displaySolution(ladder);

		} else break;
	}
	return 0;
}

void getLadderParameters(string &startW, string &destW, Lexicon &lexicon) {
	// Simple function to manage users entries
	// TODO: convert to lower case

	while (true) {
		startW = getLine("Enter start word (RETURN to quit): ");
		if ((!lexicon.contains(startW))&&(startW != "")) {
			cout << "This word does not exist!" << endl;
		} else break;
	}

	if (startW != "") {
		while (true) {
			destW = getLine("Enter destination word: ");
			if ((startW.length() != destW.length())&&(destW != "")) {
				cout << "Try again, dude. Both world should have the same length!" << endl;
			} else if ((!lexicon.contains(destW))&&(destW != "")) {
				cout << "This word does not exist!" << endl;
			} else break;
		}
	}

	if (destW == "") startW = "";
}

Vector<string> getNextWords(string &word, Lexicon &lexicon) {
	// Return the one-char next word
	Vector<string> nextWords;
	
	for (size_t i = 0; i < word.length(); i++) {
		for (size_t j = 0; j < ALPHABET.length(); j++) {
			if (word[i] != ALPHABET[j]) {
				string newWord = word;
				newWord[i] = ALPHABET[j];
				if (lexicon.contains(newWord))
					nextWords.add(newWord);
			}
		}
	}

	return nextWords;
}

bool isAlreadyUsed(string word, Vector<string> &usedWords) {
	// Check if a given word has already been used
	for (int i = 0; i < usedWords.size(); i++) {
		if (word == usedWords[i])
			return true;
	}

	return false;
}

void displaySolution(Vector<string> &solutionLadder) {
	if (solutionLadder.isEmpty()) {
		cout << "No ladder found.";
	} else {
		cout << "Found Ladder: ";
		for (int i = 0; i < solutionLadder.size(); i++) {
			cout << solutionLadder[i] << " ";
		}
	}
	cout << endl;
}
