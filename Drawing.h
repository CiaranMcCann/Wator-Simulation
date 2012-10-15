#ifndef DRAWING_H
#define DRAWING_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "Globals.h"
#include "GridPosition.h"

/*! \brief A file containing drawing logic for the Wator simulation.
 *
 *  A file containing  initalization logic for OpenGL and functions to draw the grid, sharks and fish.
 */

Display *dpy;	/*!< A poiter to the display to render to. */
Window root;	/*!< The root (desktop) window. */
GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };	/*!< The visual attributes to use for rendering. */
XVisualInfo *vi;	/*!< A pointer to the visual attributes, once set. */
Colormap cmap;	/*!< The colourmap to use for rendering. */
XSetWindowAttributes swa;	/*!< The window attributes element to use for attaching events to the window. */
Window win;	/*!< The window to render to. */
GLXContext glc;	/*!< The GLContext to use for rendering. */
XWindowAttributes gwa; /*!< ?. */
XEvent xev; /*!< ?. */

float QuadWidth;	/*!< The width of each grid position when rendered to the screen. */
float QuadHeight;	/*!< The height of each grid position when rendered to the screen. */

/*! \brief Initalizes OpenGL drawing.
 *
 *  Initalizes OpenGL for drawing.
 *  Sets rendering paramaters.
 *  Creates a new window to render to.
 */
int InitializeOpenGL()
{
	QuadWidth = 2.0f / ((float)GRID_COLUMNS + 1.0f);
	QuadHeight = 2.0f / ((float)GRID_ROWS  + 1.0f);

	// Send graphical output to the machine which is running the code.
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL)
	{
		return 0;
	}

	// Create a handle to the root (desktop) window to use as the parent of the program window.
	root = DefaultRootWindow(dpy);

	// Initalize visual attributes and check they are supported.
	vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL)
	{
		return 0;
	}

	// Create a colourmap for the window
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

	// Initalize XSetWindowAttributes structure.
	// See X11/Xlib.h for complete definition.
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	// Create the window and attach Exposure and KeyPress events.
	win = XCreateWindow(dpy, root, 0, 0, WindowWidth, WindowHeight, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

	// Display window and set name.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Wator Simulation");

	// Create the GL context and bind it to the window.
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);

	return 1;
}

/*! \brief Draws a shark.
 *
 *  Draws a graphical representation of a shark to the window.
 *  \param sharkPosition The grid position of the shark to draw.
 */
void DrawSharkAt(GridPosition sharkPosition)
{
	float xPos = (2.0f * (float)sharkPosition.X / (float)GRID_COLUMNS ) - 1.0f;
	float yPos = (2.0f * (float)sharkPosition.Y / (float)GRID_ROWS) - 1.0f;

	glBegin(GL_QUADS);
	glColor3f(1., 0., 0.); glVertex3f(xPos, yPos, 1.);
	glColor3f(1., 0., 0.); glVertex3f( xPos + QuadWidth, yPos, 1.);
	glColor3f(1., 0., 0.); glVertex3f( xPos + QuadWidth, yPos + QuadHeight, 1.);
	glColor3f(1., 0., 0.); glVertex3f(xPos,  yPos + QuadHeight, 1.);
	glEnd();
}

/*! \brief Draws a fish.
 *
 *  Draws a graphical representation of a fish to the window.
 *  \param sharkPosition The grid position of the fish to draw.
 */
void DrawFishAt(GridPosition fishPosition)
{
	float xPos = (2.0f * (float)fishPosition.X / (float)GRID_COLUMNS ) - 1.0f;
	float yPos = (2.0f * (float)fishPosition.Y / (float)GRID_ROWS) - 1.0f;

	xPos += QuadWidth * 0.25f;
	yPos += QuadHeight * 0.25f;

	glBegin(GL_QUADS);
	glColor3f(1., 1., 0.); glVertex3f(xPos, yPos, 1.);
	glColor3f(1., 1., 0.); glVertex3f( xPos + QuadWidth * 0.5f , yPos, 1.);
	glColor3f(1., 1., 0.); glVertex3f( xPos + QuadWidth * 0.5f , yPos + QuadHeight * 0.5f , 1.);
	glColor3f(1., 1., 0.); glVertex3f(xPos,  yPos + QuadHeight * 0.5f , 1.);
	glEnd();
}

/*! \brief Draws the background.
 *
 *  Fills the background of the window with black.
 */
void DrawBackground()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1., 1., -1., 1., 1., 20.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glBegin(GL_QUADS);
	glColor3f(0., 0., 0.); glVertex3f(-1., -1., 0.);
	glColor3f(0., 0., 0.); glVertex3f( 1., -1., 0.);
	glColor3f(0., 0., 0.); glVertex3f( 1.,  1., 0.);
	glColor3f(0., 0., 0.); glVertex3f(-1.,  1., 0.);
	glEnd();
}

#endif


