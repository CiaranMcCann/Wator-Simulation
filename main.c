/*! \file main.c
 * \brief A file containing the main entry point for the program..
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

short checkTileForEntity(short x, short y);
short checkTileForShark(short x, short y);
short checkTileForFish(short x, short y);

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
int saveLogTofile(float * averageFrameLog)
{
	char name [50];

	float minimum = 10000000.0f;
	float maximum = 0.0f;
	float average = 0.0f;
	float sum = 0.0f;
	int count = 0;
	for (count = 0; count < NUMBER_OF_RUNS; count++)
	{
		sum += averageFrameLog[count];
		if (averageFrameLog[count] > maximum)
		{
			maximum = averageFrameLog[count];
		}
		
		if (averageFrameLog[count] < minimum)
		{
			minimum = averageFrameLog[count];
		}		
	}
	
	average = sum / (float)count;
		
	int length = sprintf (name, "%d %s %d %s %d %s\n", GRID_ROWS, "x", GRID_COLUMNS, ":", numThreads, "cores.log");
	name[length-1] = '\0';	
	
	FILE * pLogFile = fopen( "Performance_data.log", "w" );	
	FILE * pFile = fopen( name, "w" );	

// Added a comment tag, this is for use in gnuplot
	
	fprintf( pFile, "#Min	#Max	#Average\n"); 
	fprintf( pLogFile, "#Min	#Max	#Average\n"); 
		
	fprintf( pFile, "%f%s%f%s%f\n",  minimum,"\t", maximum, "\t", average); 
	fprintf( pLogFile, "%f%s%f%s%f\n",  minimum, "\t", maximum, "\t", average); 
	
	close( pLogFile );
	close( pFile );
}

/*! \brief The main entry point for the program.
 */
int main(int argc, char *argv[])
{
	omp_set_num_threads(numThreads);
	omp_set_nested(1);
	
	printf("%d\n", omp_get_max_active_levels());
	
	int runCount = 0;	
	float averageFrames[NUMBER_OF_RUNS];
	
	while (runCount < NUMBER_OF_RUNS)
	{
		printf( "Simulation will run for %d seconds.\n", SIMULATION_LENGTH );
		
		int running= 1;
		int seconds = 0;
		double secondTimer = 0.0;
		int frameCounter = 0;
		time_t currentTime = 0;
		time_t previousTime = 0;	
				
		float framesPerSecond[SIMULATION_LENGTH];			
		populateWorld(N_FISH,N_SHARKS);
			
		if (InitializeOpenGL())
		{
			int count = 0;
			
			while (running)
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
							frameCounter = 0;
							
							if (seconds == SIMULATION_LENGTH)
							{
								float sum = 0.0f;
								int count = 0;
								for (count = 0; count < SIMULATION_LENGTH; count++)
								{
									sum += framesPerSecond[count];
								}
																
								averageFrames[runCount] = sum / (float)count;
								running = 0;
								runCount ++;								
							}
						}
					}
				}
			}
		}
		printf( "Simulation complete.\n");
	}
	
	saveLogTofile(averageFrames);
	printf( "Performance data saved to log file.\n");
}
