/*
 * File: VotingMachine.cpp
 * ----------------
 * Name: _ArnO_
 * Section: Nobody
 * This program evaluates how vote counting
 * error by machines may affect vote results
 */

// Includes and other stuff
#include <iostream>
#include "simpio.h"
#include "random.h"
using namespace std;

// Constants
const int NB_TRIALS = 500;

// Functions declaration
int getNumOfVoters();
double getPercentBetCandidates();
double getVotingMError();
double getPercentage();
void renderTrials(int numberOfVoters, double percentBetweenCandidate, double votingMachineError);
bool renderElection(int numberOfVoters, double percentBetweenCandidate, double votingMachineError);
bool renderVoteTurn(double percentBetweenCandidate, double votingMachineError);

int main() {
	//setRandomSeed(1);

	int numOfVoters = getNumOfVoters();
	double percentBetCandidates = getPercentBetCandidates();
	double votingMachineError = getVotingMError();

	renderTrials(numOfVoters, percentBetCandidates, votingMachineError);
	return 0;
}

int getNumOfVoters() {
	int promptValue;
	while (true) {
		promptValue = getInteger("Enter number of voters: ");
		if ((promptValue < 10)||(promptValue > 1000000)) {
			cout << "(Enter somethin between between 10 and 1000000)" << endl << endl;
		} else {
			return promptValue;
		}
	}
}

double getPercentBetCandidates() {
	cout << "Enter percentage spread between candidates: ";
	double promptValue = getPercentage();
	return promptValue;
}

double getVotingMError() {
	cout << "Enter voting error percentage: ";
	double promptValue = getPercentage();
	return promptValue;
}

double getPercentage() {
	double enteredValue;
	while (true) {
		cin >> enteredValue;
		if ((enteredValue < 0.0)||(enteredValue > 1.0)) {
			cout << "Not a correct percentage (between 0.000 and 1.000): ";
		} else {
			return enteredValue;
		}
	}
}

void renderTrials(int numberOfVoters, double percentBetweenCandidate, double votingMachineError) {
	// Run (nb trials) elections
	int electionsForA = 0, electionsForB = 0;
	for (int i = 0; i < NB_TRIALS; i++) {
		bool outcomeTrial = renderElection(numberOfVoters, percentBetweenCandidate, votingMachineError);
		if (outcomeTrial) { // Candidate A win the elections
			electionsForA++;
		} else {
			electionsForB++;
		}
	}

	double chanceOfInvalidity = ((double) electionsForB / NB_TRIALS) * 100;
	cout << endl << "Chance of an invalid election result after 500 trials = " << chanceOfInvalidity << "%" << endl;
}


bool renderElection(int numberOfVoters, double percentBetweenCandidate, double votingMachineError) {
	// True = candidate A win / false = candidate B win
	int votesForA = 0, votesForB = 0;
	for (int i = 0; i < numberOfVoters; i++) {
		bool voterChoice = renderVoteTurn(percentBetweenCandidate, votingMachineError);
		if (voterChoice) { // Voter choose B
			votesForA++;
		} else {
			votesForB++;
		}
	}

	// Return 0 if candidate A win
	return (votesForA >= votesForB);
}

bool renderVoteTurn(double percentBetweenCandidate, double votingMachineError) {
	// True = candidate A win / false = candidate B win

	// The higher the percentage, the higher the chance for candidate A
	bool turnVote = randomChance((0.5 + percentBetweenCandidate));
	bool turnError = randomChance(votingMachineError);

	// Return true OR (XOR)
	return (turnVote != turnError);
}