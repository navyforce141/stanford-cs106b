/*
 * File: Boggle.cpp
 * ----------------
 * Name: _ArnO_
 * Section: NoBody
 * This file is the main starter file for Assignment #4, Boggle.
 * Try to push the recursive algorithmes to the maximum
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void shuffleBoggle(Grid<char> & gamePad, int size);
Vector<string> fillCubeVec(int size);
void displayBoggle(Grid<char> & gamePad);
bool isWordSizeOK(string & word);
bool isWordEnglish(string & word, Lexicon & lex);
bool hasBeenPlayedBy(string & word, Set<string> wordsPlayed);
bool isOnTheBoard(string & word, Grid<char> & gamePad);
bool recCheckWordOnBoard(string & rest, GPoint & currentCube, Grid<bool> & playedCubes, Grid<char> & gamePad);
void computerPlays(Set<string> wordsPlayedByHuman, Grid<char> & gamePad, Lexicon & lex);
void recComputerPlays(string & sofar, GPoint & currentCube, Grid<bool> & playedCubes, Set<string> & wordsPlayed, Grid<char> & gamePad, Lexicon & lex);
int comparePoint(GPoint ptA, GPoint ptB);
void highligthCubes(Grid<bool> & playedCubes);
bool isInTheLimits(GPoint cube, int size);
void changePlayedCubes(Grid<bool> & playedCubes, GPoint & cube, bool played);
bool isAlreadyPlayed(Grid<bool> & playedCubes, GPoint & cube);

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();

//	setRandomSeed(1); // Debug
	Lexicon english("EnglishWords.dat");
	int boggleSize = 4;
	drawBoard(boggleSize, boggleSize);
	Grid<char> gamePad(boggleSize, boggleSize);

	cout << "Shuffling boggle ..." << endl;
	shuffleBoggle(gamePad, boggleSize);
	displayBoggle(gamePad);


	// Human turn
	cout << "*** Human turn ***" << endl;
	Set<string> wordsPlayedByHuman;
	while (true) {
		string wordIn = getLine("Enter a word (enter to let the computer play): ");
		string word = toUpperCase(wordIn);

		if (word.empty()) break;

		if  (!isWordSizeOK(word)) {
			cout << "This word is to short, try again" << endl;
			continue;
		}

		if  (!isWordEnglish(word, english)) {
			cout << "This word is not English, try a real word" << endl;
			continue;
		}

		if (hasBeenPlayedBy(word, wordsPlayedByHuman)) {
			cout << "This word has already been played" << endl;
			continue;
		}

		if (!isOnTheBoard(word, gamePad)) {
			cout << "This word cannot be played" << endl;
			continue;
		}

		wordsPlayedByHuman.add(word);
		recordWordForPlayer(word, HUMAN);

	}

	// Computer turn
	cout << "*** Computer turn ***" << endl;
	computerPlays(wordsPlayedByHuman, gamePad, english);

	cout << "Bye!" << endl;
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

void shuffleBoggle(Grid<char> & gamePad, int size) {
	
	// Assign the correct game size
	Vector<string> vec = fillCubeVec(size);

	for (int i = 0; i < vec.size(); i++) {
		int rd = randomInteger(0, (i - 1));
		string cubeToSwap = vec[rd];
		vec.remove(rd);
		vec.add(cubeToSwap);
	}
	
	for (int i = 0; i < size; i++) {
		for (int j =0; j < size; j++) {
			int rd = randomInteger(0, 5);
			int index = i + j;
			string dice = vec[index];
			char face = dice[rd];
			gamePad[i][j] = face;
		}
	}
}

Vector<string> fillCubeVec(int size) {
	Vector<string> result;

	for (int i = 0; i < (size * size); i++) {
		if (size == 4) {
			result.add(STANDARD_CUBES[i]);
		} else {
			result.add(BIG_BOGGLE_CUBES[i]);
		}
	}

	return result;
}

void displayBoggle(Grid<char> & gamePad) {

	for (int i = 0; i < gamePad.numRows(); i++) {
		for (int j =0; j < gamePad.numCols(); j++) {
			char face = gamePad[i][j];
			labelCube(i, j, face);
		}
	}
}

bool isWordSizeOK(string & word) {
	return (word.length() > 3);
}

bool isWordEnglish(string & word, Lexicon & lex) {
	return (lex.contains(word));
}

bool hasBeenPlayedBy(string & word, Set<string> wordsPlayed) {
	return (wordsPlayed.contains(word));
}

bool isOnTheBoard(string & word, Grid<char> & gamePad) {
	bool result = false;

	for (int i = 0; i < gamePad.numRows(); i++) {
		for (int j = 0; j < gamePad.numCols(); j++) {
			if (word[0] == gamePad[i][j]) {
				GPoint startCube(i, j);
				Grid<bool> blank(gamePad.nRows, gamePad.nCols);
				result = recCheckWordOnBoard(word, startCube, blank, gamePad);
			}
			if (result) break;
		}
		if (result) break;
	}
	return result;
}

bool recCheckWordOnBoard(string & rest, GPoint & currentCube, Grid<bool> & playedCubes, Grid<char> & gamePad) {
	// This function return true if the word is found
	// Would have been easier to return nothing
	
	int i = (int) currentCube.getX();
	int j = (int) currentCube.getY();
	
	changePlayedCubes(playedCubes, currentCube, true);

	if (gamePad[i][j] == rest[0]) {
		if (rest.length() == 1) {
			// Base case
			highligthCubes(playedCubes);
			return true;
		} else {
			string next = rest.substr(1, (rest.length() - 1));

			for (int row = -1; row < 2; row++) {
				for (int col = -1; col < 2; col++) {
					GPoint nextCube((i + row), (j + col));
					if (isInTheLimits(nextCube, gamePad.nRows)) {
						if (!isAlreadyPlayed(playedCubes, nextCube)) {
							bool result = recCheckWordOnBoard(next, nextCube, playedCubes, gamePad);
							if (result) {
								return true;	
							}
						}
					}
				}
			}
			
			changePlayedCubes(playedCubes, currentCube, false);
			return false;
		}
	} else {
		changePlayedCubes(playedCubes, currentCube, false);
		return false;
	}
}

void computerPlays(Set<string> wordsPlayed, Grid<char> & gamePad, Lexicon & lex) {

	for (int i = 0; i < gamePad.numRows(); i++) {
		for (int j = 0; j < gamePad.numCols(); j++) {
			GPoint startCube(i, j);
			string nothing;
			Grid<bool> blank(gamePad.nRows, gamePad.nCols);
			recComputerPlays(nothing, startCube, blank, wordsPlayed, gamePad, lex);
		}
	}

}

void recComputerPlays(string & sofar, GPoint & currentCube, Grid<bool> & playedCubes, Set<string> & wordsPlayed, Grid<char> & gamePad, Lexicon & lex) {
	// Looks for word in the corner

	int i = (int) currentCube.getX();
	int j = (int) currentCube.getY();

	changePlayedCubes(playedCubes, currentCube, true);
//	cout << currentCube.toString() << " added --> " << playedCubes.toString() << endl;
	string next = sofar + gamePad[i][j];

	if (!lex.containsPrefix(next)) {
		changePlayedCubes(playedCubes, currentCube, false);
//		cout << currentCube.toString() << " removed --> " << playedCubes.toString() << endl;
		return;
	}

	for (int row = -1; row < 2; row++) {
		for (int col = -1; col < 2; col++) {
			GPoint nextCube((i + row), (j + col));
			if (isInTheLimits(nextCube, gamePad.nRows)) {
				if (!isAlreadyPlayed(playedCubes, nextCube)) {
//					cout << nextCube.toString() << " not in " << playedCubes.toString() << endl;
					recComputerPlays(next, nextCube, playedCubes, wordsPlayed, gamePad, lex);
				} else {
//					cout << nextCube.toString() << " already played in " << playedCubes.toString() << endl;
				}
			}
		}
	}

	if (next.length() < 4) {
		changePlayedCubes(playedCubes, currentCube, false);
//		cout << currentCube.toString() << " removed --> " << playedCubes.toString() << " -" << endl;
		return;
	}

	if (hasBeenPlayedBy(next, wordsPlayed)) {
		changePlayedCubes(playedCubes, currentCube, false);
//		cout << currentCube.toString() << " removed --> " << playedCubes.toString() << endl;
		return;
	}

	wordsPlayed.add(next);
	recordWordForPlayer(next, COMPUTER);
	highligthCubes(playedCubes);
//	cout << next << " - " << playedCubes.toString() << endl;
	changePlayedCubes(playedCubes, currentCube, false);
//	cout << currentCube.toString() << " removed from " << playedCubes.toString() << endl;

}

void highligthCubes(Grid<bool> & playedCubes) {

	for (int i = 0; i < playedCubes.nRows; i++) {
		for (int j = 0; j < playedCubes.nCols; j++) {
			if (playedCubes[i][j]) {
				highlightCube(i, j, true);
			}
		}
	}

	pause (1000);

	for (int i = 0; i < playedCubes.nRows; i++) {
		for (int j = 0; j < playedCubes.nCols; j++) {
			if (playedCubes[i][j]) {
				highlightCube(i, j, false);
			}
		}
	}

}

bool isInTheLimits(GPoint cube, int size) {
	int i = (int) cube.getX();
	int j = (int) cube.getY();

	if (i < 0) return false;
	if (j < 0) return false;
	if (i > (size - 1)) return false;
	if (j > (size - 1)) return false;
	
	return true;
}

void changePlayedCubes(Grid<bool> & playedCubes, GPoint & cube, bool played) {
	int i = (int) cube.getX();
	int j = (int) cube.getY();

	playedCubes[i][j] = played;
}

bool isAlreadyPlayed(Grid<bool> & playedCubes, GPoint & cube) {
	int i = (int) cube.getX();
	int j = (int) cube.getY();

	return playedCubes[i][j];
}