/*! \file main.c
 * \brief A file containing the main entry point for the program..
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Globals.h"
#include "GridPosition.h"
#include "Drawing.h"
#include "World.h"

#include <omp.h>

/*!
 *  \brief Saves a performance log for the simulation.
 *
 *  \param fpsLogs The array of logged frames per second.
*/
int saveLogTofile(int * fpsLogs)
{
	//Rows = .......\n
	//Columns = ........\n
	//Threads = ........\n
	//20 lines of fps
	FILE * pFile = fopen( "Performance_data.log", "w" );
	fprintf( pFile, "Rows: %d\n", GRID_ROWS ); 
	fprintf( pFile, "Columns: %d\n", GRID_COLUMNS ); 
	fprintf( pFile, "Threads Max: %d\n",  omp_get_max_threads() ); 
	fprintf( pFile, "Threads Used: %d\n",  numThreads ); 
	int count = 0;
	for (count = 0; count < SIMULATION_LENGTH; ++count)
	{
		fprintf( pFile, "%d\n", fpsLogs[count] ); 
	}
	close( pFile );
}

/*! \brief The main entry point for the program.
 */
int main(int argc, char *argv[])
{
	printf( "Simulation will run for %d seconds.\n", SIMULATION_LENGTH );
	
	int run = 1;
	int seconds = 0;
	double secondTimer = 0.0;
	int frameCounter = 0;
	time_t currentTime = 0;
	time_t previousTime = 0;	
	int framesPerSecond[SIMULATION_LENGTH];
		
	populateWorld(N_FISH,N_SHARKS);
		
	if (InitializeOpenGL())
	{
		int count = 0;
		while (run)
		{
			++count;
			if (count == CYCLES_PER_FRAME)
			{				
				count = 0;
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
					frameCounter++;
					currentTime = time(NULL);					
					if (previousTime)
					{
						secondTimer += difftime(currentTime, previousTime);	
					}
					previousTime = time(NULL);				
					
					if (secondTimer >= 1.0)
					{
						secondTimer -= 1.0;
						framesPerSecond[seconds] = frameCounter;
						++seconds;
						// printf( "%d\n", frameCounter);						
						frameCounter = 0;						
						if (seconds == SIMULATION_LENGTH)
						{
							run = 0;
							saveLogTofile( framesPerSecond );
							printf( "Performance data saved to log file.\n");
						}
					}
				}
			}
		}
	}
	printf( "Simulation complete.\n");
}
