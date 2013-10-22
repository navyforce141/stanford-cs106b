/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: _ArnO_
 * Section: Nobody
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * Very fun program
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h" // Added by _ArnO_
#include "simpio.h" // Added by _ArnO_
using namespace std;

// Constants declarations

// Functions declarations
Map<string, Vector<char>> collectSeeds(ifstream & stream, int order);
string getMostFrequentSeed(Map<string, Vector<char>> & seedsMap);
string getMarkovText(Map<string, Vector<char>> & seedsMap, string startSeed, int textLength);

int main() {

	// Open file and get content
	ifstream fileContent;
	string fileName = promptUserForFile(fileContent, "Enter file name: ");

	// Get Markov model order
	int modelOrder = getInteger("Enter Markov model order: ");

	// Populate map with seeds
	Map<string, Vector<char> > seedsMap = collectSeeds(fileContent, modelOrder);
	
	// Find the most frequent seed
	string startSeed = getMostFrequentSeed(seedsMap);
	cout << "Most frequent seed: '" << startSeed << "'" << endl;

	// Generate a sentence and display
	string sentence = getMarkovText(seedsMap, startSeed, 2000);
	cout << "Generated text:" << endl << endl << sentence << endl;

	return 0;
}

Map<string, Vector<char>> collectSeeds(ifstream & stream, int order) {
	Map<string, Vector<char>> result;
	int counterLimit = 0, limit = 10000;
	string currentSeed, blanks(order, ' ');
	
	while (true) {
		char ch = stream.get();
		if (stream.fail()) break;
		counterLimit++;
		if (counterLimit == limit) break;
		if (ch == '\n') continue;
		// Remove seeds full of blank characters, not interesting
		if (currentSeed == blanks) continue;
		Vector<char> nextChars;
		if (currentSeed.length() == order) {
			if (result.containsKey(currentSeed)) {
				nextChars = result.get(currentSeed);
			}
			nextChars.add(ch);
			result.put(currentSeed, nextChars);
			currentSeed.erase(0, 1);
		}
		currentSeed += ch;
	}

	return result;
}

string getMostFrequentSeed(Map<string, Vector<char>> & seedsMap) {
	string result;
	int maxSize = 0;

	foreach (string seed in seedsMap) {
		if (seedsMap[seed].size() > maxSize) {
			result = seed;
			maxSize = seedsMap[seed].size();
		}
		maxSize++;
	}

	return result;
}

string getMarkovText(Map<string, Vector<char>> & seedsMap, string startSeed, int textLength) {
	int seedLength = startSeed.length();
	string text = startSeed, currentSeed = startSeed;

	for (int i = seedLength; i < textLength; i++) {
		if (!seedsMap.containsKey(currentSeed)) break;
		Vector<char> nextChars = seedsMap.get(currentSeed);
		int size = nextChars.size();
		int choice = randomInteger(0, (nextChars.size() - 1));
		text += nextChars[choice];
		currentSeed.erase(0,1);
		currentSeed += nextChars[choice];
	}
	return text;
}