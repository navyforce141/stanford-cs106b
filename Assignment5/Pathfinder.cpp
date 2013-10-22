/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: _ArnO_
 * Section: NoBody
 * This file is the starter project for the Pathfinder application
 * for Assignment #5.
 */
 
// That's completed now! A really example of Graph

#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "pqueue.h"
#include "gevents.h"
#include "ginteractors.h"
#include "gpathfinder.h"
#include "graphtypes.h"
#include "gwindow.h"
#include "path.h" // Here we are, my own class, baby!
using namespace std;

/* Constants */

const string DEFAULT_MAP = "Small.txt";
const string DEFAULT_IMAGE = "USA.png";
const bool DEBUG_MOD = true;

/* Function prototypes */

void eventLoop(PathfinderGraph & g);
void loadMap(ifstream & stream, PathfinderGraph & mapGraph);
void loadGraphFromStream(ifstream & stream, PathfinderGraph & mapGraph);
void displayGraphContent(PathfinderGraph & mapGraph);
void displayPathsOnMap(PathfinderGraph & g, string colorNode, string colorArc);
void displayOnePathOnMap(Path & p, string colorHighlight);
void selectMap(PathfinderGraph & g);
void processDijkstra(PathfinderGraph & g);
void clickOnNode(Node * & node, PathfinderGraph & g);
Path findShortestPath(Node *start, Node *finish);
double getPathCost(const Vector<Arc *> & path);
void clickSomewhere();
void processKruskal(PathfinderGraph & g);
int getIndexConnected(Vector< Set<string> > & connectedGroups, string & name);

/* Starter version of the main program */

int main() {
	GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);
	initPathfinderGraphics(gw);
	gw.addToRegion(new GButton("Map"), "SOUTH");
	gw.addToRegion(new GButton("Dijkstra"), "SOUTH");
	gw.addToRegion(new GButton("Kruskal"), "SOUTH");
	gw.addToRegion(new GButton("Quit"), "SOUTH");
	drawPathfinderMap(DEFAULT_IMAGE); 
	gw.repaint();

	if (DEBUG_MOD)
		cout << "Debug mode ON" << endl;

	PathfinderGraph mapGraph;
	ifstream stream;
	openFile(stream, DEFAULT_MAP);
	loadMap(stream, mapGraph);

	eventLoop(mapGraph);

	return 0;
}

/*
 * Function: eventLoop
 * Usage: eventLoop();
 * -------------------
 * Waits for events to occur and then executes the appopriate action.
 * Note that this function never returns.  The program exits only when
 * a command executes the exitGraphics function.
 */

void eventLoop(PathfinderGraph & g) {
   while (true) {
      GActionEvent e = waitForEvent(ACTION_EVENT);
      string cmd = e.getActionCommand();
	  // I do not understand why we do not learn the case statement
	  if (cmd == "Map") selectMap(g);
	  if (cmd == "Dijkstra") processDijkstra(g);
	  if (cmd == "Kruskal") processKruskal(g);
	  if (cmd == "Quit") exitGraphics();
   }
}
	
void selectMap(PathfinderGraph & g) {
	ifstream stream;
	string title = "Select a map - change file type";
	string path = DEFAULT_MAP; // Buggy, this folder is not selected
	openFileDialog(stream, title, path);

	//TO-DO some checks should be added HERE
	loadMap(stream, g);
}

void loadMap(ifstream & stream, PathfinderGraph & g) {
	g.clear();
	loadGraphFromStream(stream, g);
	drawPathfinderMap(g.mapFile); 

	if (DEBUG_MOD)
		displayGraphContent(g);
	displayPathsOnMap(g, NODE_COLOR, ARC_COLOR);
}

void loadGraphFromStream(ifstream & stream, PathfinderGraph & mapGraph) {
	string line;
	bool isNodesData; // true for NODES // false for arcs

	// Read first line for the image file name
	if (!stream.fail()) {
		getline(stream, line);
		mapGraph.mapFile = line;
		cout << "Filename for map image: " << mapGraph.mapFile << endl;
	}

	while (!stream.fail()) {
		getline(stream, line);

		if (line == "NODES") {
			cout << "Now reading NODES data" << endl;
			isNodesData = true;
			continue;
		}

		if (line == "ARCS") {
			cout << "Now reading ARCS data" << endl;
			isNodesData = false;
			continue;
		}

		if (line == "") {
			continue;
			// Not nice to include a blank line at the end of files
		}
		
		TokenScanner scanner(line);
		scanner.ignoreWhitespace();

		if (isNodesData) {
			// Reading NODES	
			Node *localNode = new Node();
			// Grab name
			localNode->name = scanner.nextToken();
			// Grab coordinates and create point
			int x = stringToInteger(scanner.nextToken());
			int y = stringToInteger(scanner.nextToken());
			GPoint pt(x, y);			
			localNode->nodePoint = pt;
			mapGraph.addNode(localNode);
		} else {
			// Reading ARCS
			Node *startNode, *finishNode;
			Arc *localArc1 = new Arc();
			Arc	*localArc2 = new Arc();
			startNode = mapGraph.getNode(scanner.nextToken());
			finishNode = mapGraph.getNode(scanner.nextToken());
			double arcDistance = stringToReal(scanner.nextToken());
			// Add one-way
			localArc1->start = startNode;
			localArc1->finish = finishNode;
			localArc1->distance = arcDistance;
			mapGraph.addArc(localArc1);
			// Add return
			localArc2->start = finishNode;
			localArc2->finish = startNode;
			localArc2->distance = arcDistance;
			mapGraph.addArc(localArc2);
		}		
	}
	cout << "File 100 % read" << endl;
}

void displayGraphContent(PathfinderGraph & g) {
	foreach (Node *node in g.getNodeSet()) {
		cout << "City: " << node->name << " - position: " << node->nodePoint.toString() << endl;
		foreach (Arc *arc in g.getArcSet(node)) {
			cout << " destination: " << arc->finish->name << " - distance: " << arc->distance << endl;
		}
	}
}

void displayPathsOnMap(PathfinderGraph & g, string colorNode, string colorArc) {
	foreach (Arc *arc in g.getArcSet()) {
		GPoint localStartPt = arc->start->nodePoint;
		GPoint localFinishPt = arc->finish->nodePoint;
		// Only display start city
		string cityName = arc->start->name;
		drawPathfinderNode(localStartPt, colorNode, cityName);
		drawPathfinderArc(localStartPt, localFinishPt, colorArc);
	}
}

void displayOnePathOnMap(Path & p, string colorHighlight) {
	foreach (Arc *arc in p.getSetOfArcs()) {
		GPoint localStartPt = arc->start->nodePoint;
		GPoint localFinishPt = arc->finish->nodePoint;
		string cityStartName = arc->start->name;
		string cityFinishName = arc->finish->name;
		drawPathfinderNode(localStartPt, colorHighlight, cityStartName);
		drawPathfinderNode(localFinishPt, colorHighlight, cityFinishName);
		drawPathfinderArc(localStartPt, localFinishPt, colorHighlight);
		drawPathfinderArc(localFinishPt, localStartPt, colorHighlight);
	}
}

void processDijkstra(PathfinderGraph & g) {
	cout << "*** Dijkstra mode: START ***" << endl;
	Node *startNode = NULL;
	Node *endNode = NULL;

	displayPathsOnMap(g, NODE_COLOR, ARC_COLOR);

	while (startNode == NULL) {
		clickOnNode(startNode, g);
	}
	cout << "Node selected: " << startNode->name << endl;

	while (endNode == NULL) {
		clickOnNode(endNode, g);
	}
	cout << "Node selected: " << endNode->name << endl;

	Path p = findShortestPath(startNode, endNode);

	displayPathsOnMap(g, DIM_COLOR, DIM_COLOR);
	displayOnePathOnMap(p, HIGHLIGHT_COLOR);

	cout << "*** Dijkstra mode: END ***" << endl;
}

void clickOnNode(Node * & node, PathfinderGraph & g) {
	double clickX, clickY;

	while (true) {
		GMouseEvent e = waitForEvent();
		if (e.getEventType() == MOUSE_CLICKED) {
			clickX = e.getX();
			clickY = e.getY();
			cout << "Click done somewhere at x=";
			cout << clickX << " and y=" << clickY << endl;
			break;
		}
	}
	
	int distMin = 400;
	foreach (Node *nodeG in g.getNodeSet()) {
		GPoint nodePt = nodeG->nodePoint;
		double nodeGX = nodePt.getX();
		double nodeGY = nodePt.getY();
		int dist2 = (nodeGX - clickX)*(nodeGX - clickX) + (nodeGY - clickY)*(nodeGY - clickY);
		cout << nodeG->name << " distance2: " << dist2 << endl;
		if (dist2<distMin) {
			node = nodeG;
			distMin = dist2;
		}
	}

	if (node != NULL) {
		drawPathfinderNode(node->nodePoint, HIGHLIGHT_COLOR, node->name);
	}
}

Path findShortestPath(Node *start, Node *finish) { 
	Path path;
	PriorityQueue<Path> queue;
	Map<string, double> fixed;
	while (start != finish) {
		if (!fixed.containsKey(start->name)) { 
			fixed.put(start->name, path.getCost());
			foreach (Arc *arc in start->arcs) {
				if (!fixed.containsKey(arc->finish->name)) { 
					path.addArc(arc);
					queue.enqueue(path, path.getCost());
					path.removeLast();
				}
			}
		}
		if (queue.isEmpty()) { 
			path.clear();
			return path; 
		}
		path = queue.dequeue();
		start = path.getLastNode();
	}
	return path; 
}

double getPathCost(const Vector<Arc *> & path) {
	double distance = 0;
	foreach (Arc *arc in path) {
		distance += arc->distance;
	}
	return distance;
}

void clickSomewhere() {
	while (true) {
		GMouseEvent e = waitForEvent();
		if (e.getEventType() == MOUSE_CLICKED) {
			cout << "Click done somewhere ...";
			break;
		}
	}
}

void processKruskal(PathfinderGraph & g) {
	cout << "*** Kruskal mode: START ***" << endl;
	Path shortPath;
	PriorityQueue<Arc *> queue;
	Vector<Set <string> > connectedGroups;

	
	foreach (Arc *arc in g.getArcSet()) {
		queue.enqueue(arc, arc->distance);
	}
	
	while (!queue.isEmpty()) {
		Arc *localArc;
		Set<string> connectedStart;
		Set<string> connectedFinish;

		localArc = queue.dequeue();
		cout << "From " << localArc->start->name << " to " << localArc->finish->name << " - Distance: " << localArc->distance << endl;
		
		int indexStart = getIndexConnected(connectedGroups, localArc->start->name);
		if (indexStart != -1) {
			connectedStart = connectedGroups[indexStart];
		}
		cout << "Connected nodes for origin: " << connectedStart.toString() << endl;

		int indexFinish = getIndexConnected(connectedGroups, localArc->finish->name);
		if (indexFinish != -1) {
			connectedFinish = connectedGroups[indexFinish];
		}
		cout << "Connected nodes for destination: " << connectedFinish.toString() << endl;

		if (indexStart == -1) {
			if (indexFinish == -1) {
				// None of the ends are found
				// Both nodes should be added to the same Set!
				connectedStart.add(localArc->start->name);
				connectedStart.add(localArc->finish->name);
				connectedGroups.add(connectedStart);
				shortPath.addArc(localArc);
				cout << "Arc INcluded" << endl;
			} else {
				// B is found, so A should be added to the connected nodes
				connectedFinish.add(localArc->start->name);
				connectedGroups.remove(indexFinish);
				connectedGroups.add(connectedFinish);
				shortPath.addArc(localArc);
				cout << "Arc INcluded" << endl;
			}
		} else {
			// A is found
			if (indexFinish == -1) {
				// B not found, B is added to the connected nodes of A
				connectedStart.add(localArc->finish->name);
				connectedGroups.remove(indexStart);
				connectedGroups.add(connectedStart);
				shortPath.addArc(localArc);
				cout << "Arc INcluded" << endl;
			} else {
				// Tricky case, both ends founds
				if (indexStart == indexFinish) {
					// A and B are in the same connected nodes group
					// This are not required, so do nothing
					cout << "Arc EXcluded, both node already connected" << endl;
				} else {
					// Merge connected points of start and finish
					// !!! index will be changed by the remove !!!
					// Start with the larger first
					if (indexStart < indexFinish) {
						connectedGroups.remove(indexFinish);
						connectedGroups.remove(indexStart);
					} else {
						connectedGroups.remove(indexStart);
						connectedGroups.remove(indexFinish);
					}
					// Damn tricky
					connectedStart += connectedFinish;
					connectedGroups.add(connectedStart);
					shortPath.addArc(localArc);
					cout << "Arc INcluded with a merge" << endl;
				}
			}
		}
		cout << "Connected point: " << connectedGroups.toString() << endl;
	}

	displayPathsOnMap(g, DIM_COLOR, DIM_COLOR);
	displayOnePathOnMap(shortPath, HIGHLIGHT_COLOR);

	cout << shortPath.toString() << endl;
	cout << "*** Kruskal mode: END ***" << endl;

}

int getIndexConnected(Vector< Set<string> > & connectedGroups, string & name) {
	// Easier to use a Vector instead of Set (yes, a Set of Set)
	// Did not take time to evaluate exec time - Sorry
	int result = -1;

	for (int i = 0; i < connectedGroups.size(); i++) {
		if (connectedGroups[i].contains(name)) {
			result = i;
			break;
		}
	}

	return result;
}
