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
	char name [50];
	
	int length = sprintf (name, "%d %s %d %s %d %s\n", GRID_ROWS, "x", GRID_COLUMNS, ":", numThreads, "cores.log");
	name[length-1] = '\0';	
	
	FILE * pLogFile = fopen( "Performance_data.log", "w" );	
	FILE * pFile = fopen( name, "w" );	
	fprintf( pFile, "%d %c %d %c %d %s\n", GRID_ROWS, 'x', GRID_COLUMNS, ':', numThreads, "cores" ); 
	fprintf( pLogFile, "%d %c %d %c %d %s\n", GRID_ROWS, 'x', GRID_COLUMNS, ':', numThreads, "cores" ); 
	
	int count = 0;
	for (count = 0; count < SIMULATION_LENGTH; ++count)
	{		
		fprintf( pFile, "%d\n",  fpsLogs[count]); 
		fprintf( pLogFile, "%d\n",  fpsLogs[count]); 
	}
	
	close( pLogFile );
	close( pFile );
}

/*! \brief The main entry point for the program.
 */
int main(int argc, char *argv[])
{
	omp_set_num_threads(numThreads);
	printf( "Simulation will run for %d seconds.\n", SIMULATION_LENGTH );

	//__declspec (align(64)) int thread1_global_variable;
	//__declspec (align(64)) int thread2_global_variable;
		
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
