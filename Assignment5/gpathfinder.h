/*
 * File: gpathfinder.h
 * -------------------
 * The gpathfinder.h file defines the interface for a set of functions
 * that help draw the necessary parts of the Pathfinder maps.  The
 * gpathfinder.h interface uses screen coordinates in which distances
 * on the screen are expressed in pixels and in which the origin in the
 * upper left corner of the window.  Several of the functions defined
 * in this package use values of type GPoint, which is simply a pair of
 * x and y coordinate values, as defined in the point.h interface.
 */

#ifndef _gpathfinder_h
#define _gpathfinder_h

#include "gtypes.h"
#include "gobjects.h"

/*
 * Constants
 * ---------
 * A few exported constants concerning the graphical display.
 */

extern const int WINDOW_WIDTH;             /* Width of the graphics window  */
extern const int WINDOW_HEIGHT;            /* Height of the graphics window */
extern const double NODE_RADIUS;           /* Radius of the node circle     */
extern const double PAUSE_TIME;            /* Controls speed of animation   */
extern const string ARC_COLOR;             /* Normal arc color              */
extern const string NODE_COLOR;            /* Normal node color             */
extern const string HIGHLIGHT_COLOR;       /* Color of chosen path/nodes    */
extern const string DIM_COLOR;             /* Color of unchosen path/nodes  */
extern const string LABEL_FONT;            /* Font for node labels          */

/*
 * Function: initPathfinderGraphics
 * Usage: initPathfinderGraphics(gw);
 * ----------------------------------
 * Initializes the graphics window for Pathfinder.
 */

void initPathfinderGraphics(GWindow & gw);

/*
 * Function: drawPathfinderMap
 * Usage: drawPathfinderMap(mapFile);
 * ----------------------------------
 * Clears the graphics window and then draws the image contained in
 * the specified image file, which will typically live in an images
 * subdirectory of the project directory.
 */

void drawPathfinderMap(string mapFile);

/*
 * Function: drawPathfinderNode
 * Usage: drawPathfinderNode(center, color, label);
 * ------------------------------------------------
 * Draw a node circle whose center is at the coordinate position
 * specified by the first argument and that is filled in the specified
 * color.  If a third argument is provided, the function draws a label
 * to the right of the circle containing the specified text.
 */

void drawPathfinderNode(GPoint center, string color, string label = "");

/*
 * Function: drawPathfinderArc
 * Usage: drawPathfinderArc(start, end, color);
 * --------------------------------------------
 * Draws a line on the screen connecting the two specified coordinate
 * positions using the indicated color.
 */

void drawPathfinderArc(GPoint start, GPoint end, string color);

/*
 * Function: getMouseClick
 * Usage: GPoint pt = getMouseClick();
 * -----------------------------------
 * Waits for a mouse click in the graphics window and returns the point at
 * which it occurred.
 */

GPoint getMouseClick();

#endif
