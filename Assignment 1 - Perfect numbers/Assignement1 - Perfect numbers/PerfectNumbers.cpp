/*
 * File: PerfectNumbers.cpp
 * ----------------
 * Name: _ArnO_
 * Section: Nobody
 * This program is looking for perfect numbers
 */

#include <iostream>
using namespace std;

// Adapt the max search limit
int MAX_VALUE = 10000;

bool IsPerfect(int integer);

int main() {
	cout << "Evaluating perfect numbers from 0 to " << MAX_VALUE << endl;
	cout << endl;
	for (int i = 2; i <= MAX_VALUE; i++) {
		if (IsPerfect(i)) {
			cout << "This number: " << i << " is perfect." << endl;
		}
	}
	cout << endl << "DONE." << endl;
	return 0;
}

bool IsPerfect (int integer) {
	int sumOfDividers = 0, maxDivider = (integer / 2) + 1;
	for (int i = 1; i < maxDivider; i++) {
		if ((integer % i) == 0) sumOfDividers += i;
	}
	return (sumOfDividers == integer);
}