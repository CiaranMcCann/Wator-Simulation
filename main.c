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
		int count = 0;
		while (1)
		{
			if (count == CYCLES_PER_FRAME)
			{
				updateWorld();
				if (DRAW_GRID)
				{
					XGetWindowAttributes(dpy, win, &gwa);
					glViewport(0, 0, gwa.width, gwa.height);				
					DrawBackground();
					drawWorld();
					glXSwapBuffers(dpy, win);
				}
				else
				{
					printf("Running\n");
				}
				count = 0;
			}
			++count;
		}
	}
}
