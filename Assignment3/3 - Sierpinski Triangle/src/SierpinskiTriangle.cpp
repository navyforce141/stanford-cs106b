/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the Sierpinski Triangle problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
using namespace std;

/* Function definition */

void drawSierpinskiTriangle(GPoint & top, int edge, int order, GWindow & gw);

/* Main program */

int main() {
    GWindow gw(600, 500);

	int startEdge = 400;
	int xCenter = (int) gw.getWidth() / 2;
	int yCenter = (int) gw.getHeight() / 2;
	int triangleHeight = (int) sqrt(pow((double) startEdge, 2) - pow(((double)  startEdge / 2), 2));

	GPoint ptTop(xCenter, (yCenter - (triangleHeight / 2)));
	
	drawSierpinskiTriangle(ptTop, startEdge, 8, gw);

    return 0;
}

void drawSierpinskiTriangle(GPoint & top, int edge, int order, GWindow & gw) {

	// Calculate height used almost in any position calculation
	int triangleHeight = (int) sqrt(pow((double) edge, 2) - pow(((double)  edge / 2), 2));

	// Calculate A, B and C position starting from A
	GPoint ptA = top;
	GPoint ptB((top.getX() - (triangleHeight / 2)), (top.getY() + triangleHeight));
	GPoint ptC((top.getX() + (triangleHeight / 2)), (top.getY() + triangleHeight));

	// Draw triangle
	gw.drawLine(ptA, ptB);
	gw.drawLine(ptB, ptC);
	gw.drawLine(ptC, ptA);

	if (order != 0) {
		order -= 1;
		edge = edge / 2;

		if (edge != 0) { // Prevent call for size bellow a pixel
			triangleHeight = triangleHeight / 2;

			GPoint ptAb = top;
			GPoint ptBb((top.getX() - (triangleHeight / 2)), (top.getY() + triangleHeight));
			GPoint ptCb((top.getX() + (triangleHeight / 2)), (top.getY() + triangleHeight));

			drawSierpinskiTriangle(ptAb, edge, order, gw);
			drawSierpinskiTriangle(ptBb, edge, order, gw);
			drawSierpinskiTriangle(ptCb, edge, order, gw);
		}
	}
}