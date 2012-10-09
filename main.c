#include <stdio.h>
#include <stdlib.h>

#include "Globals.h"
#include "GridPosition.h"
#include "Drawing.h"
#include "World.h"

/*! \brief The main entry point for the program.
 */
int main(int argc, char *argv[])
{
    populateWorld(N_FISH,N_SHARKS);

	if (InitializeOpenGL())
	{
		// Listen for Exposure and KeyPress events
		while (1)
		{
			XNextEvent(dpy, &xev);
			if(xev.type == Expose) // Redraw if the window has been moved, resized, etc.
			{
				XGetWindowAttributes(dpy, win, &gwa);
				glViewport(0, 0, gwa.width, gwa.height);
				DrawBackground();

                drawWorld(); //Draws all the fish and sharks in the world.

				glXSwapBuffers(dpy, win);
			}
			else if(xev.type == KeyPress) // Exit on key press
			{
                cleanWorld(); // cleans up heap memory for the world
				glXMakeCurrent(dpy, None, NULL);
				glXDestroyContext(dpy, glc);
				XDestroyWindow(dpy, win);
				XCloseDisplay(dpy);
				exit(0);
			}
		}
	}
}
