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

/*! \brief Handles wrap around
 *  Handles wrap around
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

/*! \brief Deactivates all entities at a given x,y coordinate
 *
 *  Deactivates all entities at a given x,y coordinate
 *  \param x - The x coordinate
 *  \param y - The y coordinate
 */
void deactivateAt(short x, short y)
{
    int index = x + (y * GRID_COLUMNS);
    sharksCollection[index].mSpawnCounter = INACTIVE_VALUE;
    fishCollection[index].mSpawnCounter = INACTIVE_VALUE;
}

/*! \brief Activates a fish at a given x,y coordinate
 *
 *  Activates a fish at a given x,y coordinate
 *  \param x - The x coordinate
 *  \param y - The y coordinate
 */
void activateFishAt(short x, short y)
{
    int index =  x + (y * GRID_COLUMNS);
    fishCollection[index].mSpawnCounter = 0;
}

/*! \brief Activates a shark at a given x,y coordinate
 *
 *  Activates a shark at a given x,y coordinate
 *  \param x - The x coordinate
 *  \param y - The y coordinate
 */
void activateSharkAt(short x, short y)
{
    int index =  x + (y * GRID_COLUMNS);
    sharksCollection[index].mSpawnCounter = 0;
    sharksCollection[index].mStarveCounter = 0;
}

/*! \brief Populates the world
 *
 *  Randomly populates the world array with sharks and fish
 *  \param nFish - Number of fish
 *  \param nShark - Number of sharks
 */
void populateWorld(short nFish, short nSharks)
{
	srand(time(NULL));
    short total = nFish + nSharks;
    short i = 0; //C90 standard doesn't allow loop var declaration inside loop
    int index = 0;
    int size = SHARK_LIST_LENGTH;
    
    #pragma omp privatefirst (size) parallel private (i, index, nFish) shared (fishCollection, sharksCollection)
    {
        #pragma omp for
        for(index = 0; index < size; index++)
        {
            fishCollection[index] = fishFactory();
            sharksCollection[index] = sharkFactory();
        }

        #pragma omp barrier
        
        #pragma omp for
        for(i = 0; i < total; i++)
        {
            index = rand() % size;
            if(i < nFish)
            {
                //continue with popluating fish
                fishCollection[index].mSpawnCounter = 0;
            }
            else
            {
                // once all fish done popluate sharks
                fishCollection[index].mSpawnCounter = INACTIVE_VALUE;
                sharksCollection[index].mSpawnCounter = 0;
            }
        }
    }
}

/*! \brief Checks if there is any entity at a tile
 *
 *  Checks if there is any entity at a tile
 *  \param x - The x position of the tile
 *  \param y - The y position of the tile
 *  \returns A value indicating whether the coordinate contains an entity or not.
 */
char checkTileForEntity(short x, short y)
{
    manageWrapAround(&x, &y);
    int index = (GRID_COLUMNS * y) + x;

    if( fishCollection[index].mSpawnCounter != INACTIVE_VALUE || sharksCollection[index].mSpawnCounter != INACTIVE_VALUE )
        return 1;
    else
     	return 0;
}

/*! \brief Checks if there is a shark at a tile
 *
 *  Checks if there is a shark at a tile
 *  \param x - The x position of the tile
 *  \param y - The y position of the tile
 *  \returns A value indicating whether the coordinate contains a shark or not.
 */
char checkTileForShark(short x, short y)
{
    manageWrapAround(&x, &y);

    if (sharksCollection[(GRID_COLUMNS * y) + x].mSpawnCounter != INACTIVE_VALUE )
        return 1;
    else
        return 0;
}

/*! \brief Checks if there is a fish at a tile
 *
 *  Checks if there is a fish at a tile
 *  \param x - The x position of the tile
 *  \param y - The y position of the tile
 *  \returns A value indicating whether the coordinate contains a fish or not.
 */
char checkTileForFish(short x, short y)
{
    manageWrapAround(&x, &y);

    if (fishCollection[(GRID_COLUMNS * y) + x].mSpawnCounter != INACTIVE_VALUE )
        return 1;
    else
        return 0;
}


/*! update
 */
void updateWorld()
{
	short y = 0;
    short x = 0;
    int count = 0;
    #pragma omp parallel for shared (fishCollection, sharksCollection) private (x, y)
    for(count = 0; count < SHARK_LIST_LENGTH; ++count)
    {
        y = count / GRID_COLUMNS;
        x = count % GRID_COLUMNS;
        if (fishCollection[count].mSpawnCounter != INACTIVE_VALUE )
        {
            updateFish(x, y, &fishCollection[count]);
        }
        else if (sharksCollection[count].mSpawnCounter != INACTIVE_VALUE )
        {
            updateShark(x, y, &sharksCollection[count]);
        }
    }
}


/*! \brief Draws the world
 */
void drawWorld()
{
    int y = 0;
    int x = 0;
    for(y = 0; y < GRID_ROWS; y++)
    {
        for(x= 0; x < GRID_COLUMNS; x++)
        { 
            if (fishCollection[(GRID_COLUMNS * y) + x].mSpawnCounter != INACTIVE_VALUE )
            {
                DrawFishAt(x, y);
            }
            else if (sharksCollection[(GRID_COLUMNS * y) + x].mSpawnCounter != INACTIVE_VALUE )
            {
                DrawSharkAt(x, y);
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

	// short y = 0;
	// short x = 0;
	// for(x = 0; x < GRID_COLUMNS; x++)
	// {
	// 	for(y = 0; y < GRID_ROWS; y++)
	// 	{
	// 	    destroyAt(x,y);
	// 	}
	// }

	// fishCollection = Fish[FISH_LIST_LENGTH];
	// sharksCollection = Shark[SHARK_LIST_LENGTH];
	// world = GirdObj[GRID_ROWS][GRID_COLUMNS ];
}



#endif
