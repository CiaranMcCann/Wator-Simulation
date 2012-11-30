/*! \file World.h
 *  \brief A file containing all functions for the world
*/
#ifndef WORLD_H
#define WORLD_H

#include "Fish.h"
#include "Shark.h"
#include "Globals.h"
#include <time.h>
 #include <stdio.h>
#include <stdlib.h>
 #include <assert.h>

/*! \brief Used to store pionters to either fish or sharks.
 *
 *  Note: Used this struct instead of a void * Array as the casting process
 *  is messy and this is much simplier means of storing different types in one array.
 */
typedef struct {
    Fish * pFish;
    Shark * pShark;
} GirdObj;

 // Array of GirdObjs which
GirdObj world[GRID_ROWS][GRID_COLUMNS ];

GirdObj world[GRID_ROWS][GRID_COLUMNS ];
Fish fishCollection[FISH_LIST_LENGTH];
Shark sharksCollection[SHARK_LIST_LENGTH];


Shark * addShark( Shark s)
{
    s.active = 1; 

    int i = 0;

    //TODO omp for this bitch
    for( i = 0; i < SHARK_LIST_LENGTH; i++)
    {
        if(sharksCollection[i].active == 0)
        {
            sharksCollection[i] = s;
            return &sharksCollection[i];
        }
    }
    assert( 1 == 2);
}


Fish * addFish(Fish f)
{
    f.active = 1;

    int i = 0;

    //Loop till we fine a fish object which is not active and use that
    for(i = 0; i < FISH_LIST_LENGTH; i++)
    {
        if( fishCollection[i].active == 0 )
        {
            fishCollection[i] = f;   
            return &fishCollection[i];

        }
    }
     assert( 1 == 2);

}

/*! \brief Handles wrap around
 *
 *  \returns A grid position in the bounds of the world
*/
void manageWrapAround(short * x, short * y)
{
    if (*x < 0)
        *x = GRID_COLUMNS - 1;
    else if (*x >= GRID_COLUMNS)
        *x = 0;

    if (*y < 0)
        *y = GRID_ROWS - 1;
    else if (*y >= GRID_ROWS)
        *y = 0;
}


/*! \brief Creates either a fish or a shark.
 *
 * Function only really exists because as a user I hate short flags
 */
void _createAt(short x, short y, short fishFlag)
{
    if( world[x][y].pFish == 0 &&  world[x][y].pShark == 0)
    {
        if(fishFlag)
        {
            world[x][y].pFish = addFish(fishFactory(x,y));
        }
        else
        {
            world[x][y].pShark = addShark(sharkFactory(x,y));
        }
    }
}

/*! \brief Moves the fish pointer within the grid.
 *
 *  Moves the fish pointer within the grid.
 *  Performs no bounds checking.
 *  \param newPos - The grid position to move to.
 *  \param pFish - The fish to move.
 */
void moveFishPointerTo(GridPosition newPos, Fish* pFish)
{
	world[pFish->pos.X][pFish->pos.Y].pFish = 0;
	world[newPos.X][newPos.Y].pFish = pFish;
}

/*! \brief Moves the shark pointer within the grid.
 *
 *  Moves the shark pointer within the grid.
 *  Performs no bounds checking.
 *  \param newPos - The grid position to move to.
 *  \param pShark - The shark to move.
 */
void moveSharkPointerTo(GridPosition newPos, Shark *pShark)
{
	world[pShark->pos.X][pShark->pos.Y].pShark = 0;
	world[newPos.X][newPos.Y].pShark = pShark;
}

/*! \brief Destories the enity at given grid location
 *
 *  Destories the enity at given grid location and frees memory
 *  \param x - index shorto array
 *  \param y - index shorto array
 */
void destroyAt(short x, short y)
{
	if(world[x][y].pFish)
	{
    	//free(world[x][y].pFish);
    	world[x][y].pFish->active = 0;

	}
	else if(world[x][y].pShark)
	{
    	//free(world[x][y].pShark);
    	world[x][y].pShark->active = 0;
	}
}


/*! \brief Creates fish at given [x][y]
 *
 *  Creates fish at given [x][y]
 *  \param x - index shorto array
 *  \param y - index shorto array
 */
void createFishAt(short x, short y){
    _createAt(x,y,1);
}

/*! \brief Creates shark at given [x][y]
 *
 *  Creates shark at given [x][y]
 *  \param x - index shorto array
 *  \param y - index shorto array
 */
void createSharkAt(short x, short y){
    _createAt(x,y,0);
}


/*! \brief Populates the world
 *
 *  Randomly populates the world array with sharks and fish
 *  \param nFish - Number of fish
 *  \param nShark - Number of sharks
 */
void populateWorld(short nFish, short nSharks)
{
    // int i = 0;
    // for(i = 0; i < GRID_ROWS*GRID_COLUMNS; i++)
    // {
    //     fishCollection[i].mSpawnCounter;
    // }

	//    Its probably a good idea to emphasize that srand() should only be called once.
	//    Also, in a threaded application, might want to make sure that the generator's
	//    state is stored per thread, and seed the generator once for each thread.
	#pragma omp parallel
    {
    	srand(time(NULL));
	    short total = nFish + nSharks;
	    short x = 0;
	    short y = 0;
	    short i = 0; //C90 standard doesn't allow loop var declaration inside loop

    	#pragma omp for
	    for(i = 0; i < total; i++)
	    {
	        x = rand() % GRID_ROWS;
	        y = rand() % GRID_COLUMNS;

	        if(i < nFish)
	        {
	            //continue with popluating fish
	            createFishAt(x,y);
	        }
	        else
	        {
	            // once all fish done popluate sharks
	            createSharkAt(x,y);
	        }
	    }
	}
}

/*! \ Checks a tile to see if it contains fish or shark
 *  Checks for nulls squares
 *  This will only work for fish so may rename to checkTileFish or somesuch
 *
 */
short checkTileForEntity(short x, short y)
{
    short i = 0;

    if (x < 0) // handle wrap around
        x = GRID_COLUMNS - 1;
    else if (x >= GRID_COLUMNS)
        x = 0;

    if (y < 0)
        y = GRID_ROWS - 1;
    else if (y >= GRID_ROWS)
        y = 0;

    if(world[x][y].pShark || world[x][y].pFish)
        i = 1;

     return i;
}

/*
 * Checks if there is a shark short a tile
 * @param short x The x position of the tile
 * @param short y The y position of the tile
 * @returns True for shark, false otherwise
 */
short checkTileForShark(short x, short y)
{
    manageWrapAround(&x, &y);

    if (world[x][y].pShark !=0)
        return 1;
    else
        return 0;
}

/*
 * Checks if there is a shark short a tile
 * @param short x The x position of the tile
 * @param short y The y position of the tile
 * @returns The poshorter to the fish in the tile or null
 */
short checkTileForFish(short x, short y)
{
    manageWrapAround(&x, &y);

    if (world[x][y].pFish !=0)
        return 1;
    else
        return 0;
}


/*! update
 */
void updateWorld()
{
	    int y = 0;
	    int x = 0;
        

    #pragma omp parallel 
    {
        int i = 0;
        #pragma omp for
        for(i = 0; i < FISH_LIST_LENGTH; i++)
        {                
               if( fishCollection[i].active == 1 )
               {
                 updateFish(fishCollection[i].pos.X, fishCollection[i].pos.Y, &fishCollection[i]);
               }
        }

        int j = 0;
        #pragma omp for
        for (j = 0; j < SHARK_LIST_LENGTH; j++)
        {
            if( sharksCollection[j].active == 1)
            {
                updateShark(sharksCollection[j].pos.X, sharksCollection[j].pos.Y, &sharksCollection[j]);
            }
        }
	}
    // #pragma omp parallel 
    // {
    //     #pragma omp for
    //     for(y = 0; y < GRID_ROWS; y++)
    //     {		
    //         #pragma omp for
    //         for(x = 0; x < GRID_COLUMNS; x++)
    //         {
    //             if(world[x][y].pFish != 0) // Check if null
    //             {
    //                 updateFish(x, y, world[x][y].pFish);
    //             }
    //         	else if(world[x][y].pShark != 0) // Check if null
    //             {
    //                 updateShark(x, y, world[x][y].pShark);
    //             }
    //         }
    //     }
   		
    //     #pragma omp barrier

    //     #pragma omp for
    //     for(y = 0; y < GRID_ROWS; y++)
    //     {
    //     	#pragma omp for
    //         for(x= 0; x < GRID_COLUMNS; x++)
    //         {
    //             if(world[x][y].pFish != 0)
    //             {
    //                 world[x][y].pFish->updated = 0;
    //             }
    //             else if(world[x][y].pShark != 0)
    //             {
    //                 world[x][y].pShark->updated = 0;
    //                 // Check if the shark is dead
    //                 if (world[x][y].pShark->mDead)
    //                 {
    //                     destroyAt(x, y);
    //                 }
    //             }
    //         } // end for x
    //     } // end for y

    // }
}


/*! \brief Draws the world
 */
void drawWorld()
{
    short y = 0;
    short x = 0;
    for(x = 0; x < GRID_COLUMNS; x++)
    {
        for(y = 0; y < GRID_ROWS; y++)
        {
	    if(world[x][y].pFish != 0)
	    {
		DrawFishAt(world[x][y].pFish->pos);
	    }

	    if(world[x][y].pShark != 0)
	    {
		DrawSharkAt(world[x][y].pShark->pos);
	    }
        }
    }

}


/*! \brief Destroys the enity at given grid location
 *
 *  Destroys the enity at given grid location
 *  @param x - index shorto array
 *  @param y - index shorto array
 */
void cleanWorld(){

	short y = 0;
	short x = 0;
	for(x = 0; x < GRID_COLUMNS; x++)
	{
		for(y = 0; y < GRID_ROWS; y++)
		{
		    destroyAt(x,y);
		}
	}
}



#endif
