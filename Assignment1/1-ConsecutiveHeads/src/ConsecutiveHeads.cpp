/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: _ArnO_
 * Section: Nobody
 * This file is the starter project for the coin-flipping problem.
 * A coin is fipped until 3 consecutives heads
 */

#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;

int main() {
	//setRandomSeed();
	
	int nbConsecutiveHeads = 0, nbTosses = 0;

	while (nbConsecutiveHeads < 3) {
		bool turnToss = randomChance(.5);
		nbTosses++;
		// true = head // false = tail

		if (turnToss) {
			cout << "head" << endl;
			nbConsecutiveHeads++;
		} else {
			cout << "tail" << endl;
			nbConsecutiveHeads = 0;
		}
	}

	cout << "It took " << nbTosses << " flips to get 3 consecutive heads." << endl;

   return 0;
}
