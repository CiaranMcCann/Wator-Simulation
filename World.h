#ifndef WORLD_H
#define WORLD_H

#include "Fish.h"
#include "Shark.h"
#include "Globals.h"
#include <time.h>
#include <stdlib.h>

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


/*! \brief Handles wrap around
 *
 *  \returns A grid position in the bounds of the world
*/
void manageWrapAround(int * x, int * y)
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
 * Function only really exists because as a user I hate int flags
 */
void _createAt(int x, int y, int fishFlag)
{
    if( world[x][y].pFish == 0 &&  world[x][y].pShark == 0)
    {
        if(fishFlag)
        {
              world[x][y].pFish = fishFactory(x,y);
        }
        else
        {
            world[x][y].pShark = sharkFactory(x,y);
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
 *  \param x - index into array
 *  \param y - index into array
 */
void destroyAt(int x, int y)
{
    //printf("destroyAt\n");
    //printf("%d, ", x);
    //printf("%d\n", y);

    free(world[x][y].pFish);
    free(world[x][y].pShark);

    world[x][y].pFish = 0;
    world[x][y].pShark = 0;

    //printf("destroyAt success\n");

}


/*! \brief Creates fish at given [x][y]
 *
 *  Creates fish at given [x][y]
 *  \param x - index into array
 *  \param y - index into array
 */
void createFishAt(int x, int y){
    _createAt(x,y,1);
}

/*! \brief Creates shark at given [x][y]
 *
 *  Creates shark at given [x][y]
 *  \param x - index into array
 *  \param y - index into array
 */
void createSharkAt(int x, int y){
    _createAt(x,y,0);
}


/*! \brief Populates the world
 *
 *  Randomly populates the world array with sharks and fish
 *  \param nFish - Number of fish
 *  \param nShark - Number of sharks
 */
void populateWorld(int nFish, int nSharks){
//    Its probably a good idea to emphasize that srand() should only be called once.
//    Also, in a threaded application, might want to make sure that the generator's
//    state is stored per thread, and seed the generator once for each thread.
    srand(time(NULL));

    int total = nFish + nSharks;

    int i = 0; //C90 standard doesn't allow loop var declaration inside loop
    for(i = 0; i < total; i++)
    {
        int x = rand() % GRID_ROWS;
        int y = rand() % GRID_COLUMNS;

        if(i < nFish){
            //continue with popluating fish
            createFishAt(x,y);

        }else{
            // once all fish done popluate sharks
            createSharkAt(x,y);
        }

    }

}

/*! \ Checks a tile to see if it contains fish or shark
 *  Checks for nulls squares
 *  This will only work for fish so may rename to checkTileFish or somesuch
 *  
 */

int checkTileForEntity(int x, int y)
{
    int i = 0;

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
 * Checks if there is a shark int a tile
 * @param int x The x position of the tile
 * @param int y The y position of the tile
 * @returns True for shark, false otherwise
 */
int checkTileForShark(int x, int y)
{
    manageWrapAround(&x, &y);

    if (world[x][y].pShark !=0)
        return 1;
    else
        return 0;
}

/*
 * Checks if there is a shark int a tile
 * @param int x The x position of the tile
 * @param int y The y position of the tile
 * @returns The pointer to the fish in the tile or null
 */
int checkTileForFish(int x, int y)
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

    for(x = 0; x < GRID_COLUMNS; x++)
    {
        for(y = 0; y < GRID_ROWS; y++)
        {
            if(world[x][y].pFish != 0) // Check if null
            {
                updateFish(x, y, world[x][y].pFish);
            }

            if(world[x][y].pShark != 0) // Check if null
            {
                updateShark(x, y, world[x][y].pShark);
            }
        }
    }

    // Reset the updated counter
    for(x= 0; x < GRID_COLUMNS; x++)
    {
        for(y = 0; y < GRID_ROWS; y++)
        {
            if(world[x][y].pFish != 0)
                world[x][y].pFish->updated = 0;
            

            if(world[x][y].pShark != 0)
            {
                world[x][y].pShark->updated = 0;

                // Check if the shark is dead
                if (world[x][y].pShark->mDead)
                {
                    destroyAt(x, y);
                }
            }
        }
    }

}


/*! \brief Draws the world
 */
void drawWorld()
{
    int y = 0;
    int x = 0;
    for(x = 0; x < GRID_COLUMNS; x++)
    {
        for(y = 0; y < GRID_ROWS; y++)
        {         
	    
	    if(world[x][y].pShark != 0 && world[x][y].pFish != 0)
	    {
		DrawBothAt(world[x][y].pShark->pos);
	    }
	    else
	    {
		    if(world[x][y].pFish != 0) // Check if null
		    {
			    //~ GridPosition a;
			    //~ a.X = x;
			    //~ a.Y = y;
			    //~ DrawBothAt(a);
			DrawFishAt(world[x][y].pFish->pos);
		    }

		    if(world[x][y].pShark != 0) // Check if null
		    {
			    //~ GridPosition a;
			    //~ a.X = x;
			    //~ a.Y = y;
			    //~ DrawBothAt(a);
			DrawSharkAt(world[x][y].pShark->pos);
		    }
	    }
        }
    }

}


/*! \brief Destories the enity at given grid location
 *
 *  Destories the enity at given grid location
 *  \param x - index into array
 *  \param y - index into array
 */
void cleanWorld(){

	int y = 0;
	int x = 0;
	for(x = 0; x < GRID_COLUMNS; x++)
	{
		for(y = 0; y < GRID_ROWS; y++)
		{
		    destroyAt(x,y);
		}
	}
}



#endif
