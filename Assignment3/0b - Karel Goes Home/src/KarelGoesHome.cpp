/*
 * File: KarelGoesHome.cpp
 * -----------------------
 * Starter file for the Karel Goes Home problem.
 */

#include <iostream>
#include <iomanip>
using namespace std;

/* Function prototypes */

int countPaths(int street, int avenue);

/* Main program */

int main() {
    
	for (int i = 14; i >= 0; i--) {
		for (int j = 0; j < 15; j++) {
			cout << setw(3) << countPaths(i, j);
		}
		cout << endl;
	}
	
    return 0;
}

/*
 * Function: countPaths
 * Usage: int nPaths = countPaths(street, avenue);
 * -----------------------------------------------
 * Counts the paths from a particular street/avenue position in
 * Karel's world to the origin, subject to the restriction that
 * Karel can move only west and south.
 */
int countPaths(int street, int avenue) {
    int result = 0;

	if (street != 0) {
		result = 1 + countPaths((street - 1), avenue);
	}

	if (avenue != 0) {
		result = 1 + countPaths(street, (avenue - 1));
	}
	
	return result;
}
