/*
 * File: path.cpp
 * --------------
 * Name: _ArnO_
 * Section: NoBody
 * This file implements the path.h interface.
 */

#include <iostream>
#include "path.h"
using namespace std;

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to write the code   //
// that implements your path.h interface.  For the benefit of      //
// future programmers who will need to work on this interface,     //
// you should also write an extended comment (presumably replacing //
// this to-do box) that documents the design decisions you made    //
// in structuring the Path class as you did.                       //
/////////////////////////////////////////////////////////////////////

Path::Path() {
	numArcs = 0;
	double distance = 0;
}

Path::~Path() {
	vectOfArcs.clear();
}

void Path::addArc(Arc *arc) {
	vectOfArcs.add(arc);
	numArcs++;
	distance += arc->distance;
}

void Path::removeLast() {
	distance -= vectOfArcs[numArcs - 1]->distance;
	vectOfArcs.remove(numArcs - 1);
	numArcs--;
}

Node *Path::getLastNode() {
	return vectOfArcs[numArcs - 1]->finish;
}

Arc *Path::getArc(int i) {
	return vectOfArcs[i];
}

Set<Arc *> Path::getSetOfArcs() {
	Set<Arc *> result;
	for (int i = 0; i < numArcs; i++) {
		result.add(vectOfArcs[i]);
	}
	return result;
}

void Path::clear() {
	vectOfArcs.clear();
}

double Path::getCost() {
	return distance;
}

int Path::getSize() {
	return numArcs;
}

string Path::toString() {
	string result;
	for (int i = 0; i < vectOfArcs.size(); i++) {
		result += vectOfArcs[i]->start->name + "->";
	}
	result += vectOfArcs[numArcs - 1]->finish->name;
	return result;
}

