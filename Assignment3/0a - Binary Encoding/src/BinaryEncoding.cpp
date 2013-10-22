/*
 * File: BinaryEncoding.cpp
 * ------------------------
 * Starter file for the binary encoding problem on Assignment #3.
 */

#include <iostream>
#include <string> // Added by _ArnO_
#include "console.h"
#include "simpio.h"
#include "vector.h" // Added by _ArnO_
using namespace std;

/* Function prototypes */

void generateBinaryCode(int nBits);
Vector<string> recAddBit(Vector<string> & prefixBit, int limit);
void addSingleBit(Vector<string> & prefixBit, Vector<string> & resultBit, char bitToAdd);

/* Main program */

int main() {
    int nBits = getInteger("Number of bits: ");
    generateBinaryCode(nBits);
    return 0;
}

/*
 * Function: generateBinaryCode
 * Usage: generateBinaryCode(nBits);
 * ---------------------------------
 * Lists all the binary values containing the specified number of bits.
 */
void generateBinaryCode(int nBits) {
	Vector<string> binaryCode, intial;
	binaryCode = recAddBit(intial, nBits);
	// cout << binaryCode.toString() << endl; // toString return strange results
	for (int i = 0; i < binaryCode.size(); i++) {
		cout << binaryCode[i] << endl;
	}
}

Vector<string> recAddBit(Vector<string> & prefixBit, int limit) {
	Vector<string> result, next;

	addSingleBit(prefixBit, next, '0');
	addSingleBit(prefixBit, next, '1');

	if (limit == 1) {
		// Base case
		result = next;
	} else {
		// Recursive calls
		result = recAddBit(next, (limit - 1));
	}

	return result;
}

void addSingleBit(Vector<string> & prefixBit, Vector<string> & resultBit, char bitToAddChar) {
	string bitToAdd = bitToAddChar + string();
	if (prefixBit.isEmpty()) {
		resultBit.add(bitToAdd);
	} else {
		for (int i = 0; i < prefixBit.size(); i++) {
			resultBit.add(bitToAdd + prefixBit[i]);
		}
	}
}

