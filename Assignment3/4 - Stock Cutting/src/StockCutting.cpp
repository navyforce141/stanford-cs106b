/*
 * File: StockCutting.cpp
 * ----------------------
 * Name: _ArnO_
 * Section: NoBody
 * This file is the starter code for the stock-cutting problem
 * from Assignment #3.
 * Given a vector of pipes length, return minimal number of stock pipe to purchase
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h" // Added by _ArnO_
using namespace std;

/* Function prototypes */

int cutStock(Vector<int> & requests, int stockLength);
int recCutStock(Vector<int> & rest, int curCut, int curNbPipes, int best, int stockLength);

/* Main program */

int main() {
    
	int stockLength = 10;
	Vector<int> pipes;

	while (true) {
		int pipeLength = getInteger("Enter pipe length: ");
		if (pipeLength == 0) {
			break;
		}
		pipes.add(pipeLength);
	}
    
	cout << "Here is your pipe: " << pipes.toString() << endl;
	int nb = cutStock(pipes, stockLength);
	cout << "Nomber of pipes to purchase: " << nb << endl;

	return 0;
}

/*
 * Function: cutStock
 * Usage: int units = cutStock(requests, stockLength);
 * ---------------------------------------------------
 * Computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces.
 */
int cutStock(Vector<int> & requests, int stockLength) {
	Vector<int> blank;
	int maxCut = requests.size();
    int result = recCutStock(requests, 0, 1, maxCut, stockLength);
    return result;
}

int recCutStock(Vector<int> & rest, int cutLength, int nbPipes, int best, int stockLength) {

	int result = 0;
	int minCut = best;
	if (rest.isEmpty()) {
		result = nbPipes;
	} else {
		for (int i = 0; i < rest.size(); i++) {
			Vector<int> remaining = rest;
			int curCutLength, curNbPipes;
			// Really tricky part
			if ((rest[i] + cutLength) > stockLength) {
				// Use a new stock pipe
				curNbPipes = nbPipes + 1;
				// Current cut = size of current pipe
				curCutLength = rest[i];
			} else {
				// Cut the current pipe in the current stock pipe
				curCutLength = cutLength + rest[i];
				// Still on the same stock pipe
				curNbPipes = nbPipes;
			}

			remaining.remove(i);
			result = recCutStock(remaining, curCutLength, curNbPipes, minCut, stockLength);
			
			// This part catches the minimum value
			if (result < minCut) {
				// Best found
				minCut = result;
			} else {
				// Result not best, the min value is return
				result = minCut;
			}

		}
	}

	return result;
}
