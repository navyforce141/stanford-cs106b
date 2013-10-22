/*
 * File: gpathfinder.cpp
 * ---------------------
 * The gpathfinder.cpp file implements a set of functions that help draw the
 * necessary parts of the Pathfinder maps.
 */

#include <iostream>
#include <string>
#include "gevents.h"
#include "ginteractors.h"
#include "gobjects.h"
#include "gpathfinder.h"
#include "gwindow.h"
#include "point.h"
using namespace std;

/* Constants */

extern const int WINDOW_WIDTH = 644;
extern const int WINDOW_HEIGHT = 422;
extern const double NODE_RADIUS = 3.5;
extern const double PAUSE_TIME = .05;
extern const string ARC_COLOR = "DarkGray";
extern const string NODE_COLOR = "Black";
extern const string HIGHLIGHT_COLOR = "Red";
extern const string DIM_COLOR = "Gray";
extern const string LABEL_FONT = "Helvetica-10";

const string CONTROL_STRIP = "#E5E5E5";
const double BUTTON_WIDTH = 90;
const double BUTTON_HEIGHT = 29;
const double BUTTON_MARGIN = 4;
const double BUTTON_SEP = 6;

/* Global data */

static GWindow *gwp;

/* Prototypes */

void drawCircle(double x, double y, double r);
void fillCircle(double x, double y, double r);

/* Exported functions */

void initPathfinderGraphics(GWindow & gw) {
   gwp = &gw;
   gwp->setWindowTitle("Pathfinder");
   gwp->setRegionAlignment("SOUTH", "LEFT");
   pause(400);
}

void drawPathfinderMap(string mapFile) {
   gwp->setColor("WHITE");
   gwp->fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
   gwp->setColor("BLACK");
   if (mapFile != "") {
      GImage map(mapFile);
      gwp->draw(map);
   }
}

void drawPathfinderNode(GPoint center, string color, string str) {
   gwp->setColor(color);
   fillCircle(center.getX(), center.getY(), NODE_RADIUS);
   if (!str.empty()) {
      GLabel label(str);
      label.setFont(LABEL_FONT);
      label.setLocation(center.getX() + NODE_RADIUS + 2, center.getY() + 5);
      gwp->draw(label);
   }
   gwp->repaint();
}

void drawPathfinderArc(GPoint start, GPoint end, string color) {
   gwp->setColor(color);
   gwp->drawLine(start.getX(), start.getY(), end.getX(), end.getY());
   gwp->repaint();
}

/*
 * Implementation notes: getMouseClick
 * -----------------------------------
 * This function waits for a CLICK_EVENT and returns the point at which
 * it occurs.
 */

GPoint getMouseClick() {
   GMouseEvent e = waitForEvent(CLICK_EVENT);
   return GPoint(e.getX(), e.getY());
}

/*
 * Implementation notes: drawCircle, fillCircle
 * --------------------------------------------
 * These functions are useful tools that draw an outlined and a filled
 * circle, respectively.  If you are extending the Pathfinder assignment,
 * you might well want to export these methods through the gpathfinder.h
 * interface.
 */

void drawCircle(double x, double y, double r) {
   gwp->drawOval(x - r, y - r, 2 * r, 2 * r);
}

void fillCircle(double x, double y, double r) {
   gwp->fillOval(x - r, y - r, 2 * r, 2 * r);
}
