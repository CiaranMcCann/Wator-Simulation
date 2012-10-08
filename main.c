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
	if (InitializeOpenGL())
	{
		GridPosition sharkPos;
		sharkPos.X = 0;
		sharkPos.Y = 99;
		
		GridPosition fishPos;
		fishPos.X = 10;
		fishPos.Y = 0;
		
		// Listen for Exposure and KeyPress events
		while (1) 
		{
			XNextEvent(dpy, &xev);
			if(xev.type == Expose) // Redraw if the window has been moved, resized, etc.
			{
				XGetWindowAttributes(dpy, win, &gwa);
				glViewport(0, 0, gwa.width, gwa.height);
				DrawBackground(); 
				DrawSharkAt(sharkPos);
				DrawFishAt(fishPos);
				glXSwapBuffers(dpy, win); 
			}
			else if(xev.type == KeyPress) // Exit on key press
			{
				glXMakeCurrent(dpy, None, NULL);
				glXDestroyContext(dpy, glc);
				XDestroyWindow(dpy, win);
				XCloseDisplay(dpy);
				exit(0); 
			}
		}
	}	
}
