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

// ! \brief Used to store pionters to either fish or sharks.
//  *
//  *  Note: Used this struct instead of a void * Array as the casting process
//  *  is messy and this is much simplier means of storing different types in one array.
 
// typedef struct {
//     Fish * pFish;
//     Shark * pShark;
// } GirdObj;

// GirdObj GridObjFactory()
// {
// 	GirdObj g;
// 	g.pFish = 0;
// 	g.pShark = 0;

// 	return g;
// }

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
void _activateAt(short x, short y, short fishFlag)
{
    if( fishCollection[x + (y * GRID_COLUMNS)].active == 0 &&  sharksCollection[x + (y * GRID_COLUMNS)].active == 0)
    {
        if(fishFlag)
        {
        	fishCollection[x + (y * GRID_COLUMNS)].active = 1;
       		fishCollection[x + (y * GRID_COLUMNS)].mSpawnCounter = 0;
        }
        else
        {
            sharksCollection[x + (y * GRID_COLUMNS)].active = 1;
            sharksCollection[x + (y * GRID_COLUMNS)].mSpawnCounter = 0;
			sharksCollection[x + (y * GRID_COLUMNS)].mStarveCounter = 0;
        }
    }
}

void deactivateAt(short x, short y)
{
    sharksCollection[(GRID_COLUMNS * y) + x].active = 0;
    fishCollection[(GRID_COLUMNS * y) + x].active = 0;
}

/*! \brief Activates fish at given [x][y]
 *
 *  Activates fish at given [x][y]
 *  \param x - index shorto array
 *  \param y - index shorto array
 */
void activateFishAt(short x, short y)
{
    _activateAt(x,y,1);
}

/*! \brief Creates shark at given [x][y]
 *
 *  Creates shark at given [x][y]
 *  \param x - index shorto array
 *  \param y - index shorto array
 */
void activateSharkAt(short x, short y)
{
    _activateAt(x,y,0);
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
    short x = 0;
    short y = 0;
    short i = 0; //C90 standard doesn't allow loop var declaration inside loop

    #pragma omp parallel
    {
        #pragma omp for collapse(2)
        for(y = 0; y < GRID_ROWS; y++)
        {
            for(x= 0; x < GRID_COLUMNS; x++)
            {            
            	fishCollection[(GRID_COLUMNS * y) + x] = fishFactory(x, y);
            	sharksCollection[(GRID_COLUMNS * y) + x] = sharkFactory(x, y);
            } // end for x
        } // end for y

        #pragma omp for
        for(i = 0; i < total; i++)
        {
            x = rand() % GRID_ROWS;
            y = rand() % GRID_COLUMNS;

            if(i < nFish)
            {
                //continue with popluating fish
                fishCollection[(GRID_COLUMNS * y) + x].active = 1;
            }
            else
            {
                // once all fish done popluate sharks
                fishCollection[(GRID_COLUMNS * y) + x].active = 0;
                sharksCollection[(GRID_COLUMNS * y) + x].active = 1;
            }
        }
    }
}

/*! \ Checks a tile to see if it contains fish or shark
 *  Checks for nulls squares
 *  This will only work for fish so may rename to checkTileFish or somesuch
 *
 */
char checkTileForEntity(short x, short y)
{
    manageWrapAround(&x, &y);

    if(sharksCollection[(GRID_COLUMNS * y) + x].active == 1 || fishCollection[(GRID_COLUMNS * y) + x].active == 1)
        return 1;
    else
     	return 0;
}

/*
 * Checks if there is a shark short a tile
 * @param short x The x position of the tile
 * @param short y The y position of the tile
 * @returns True for shark, false otherwise
 */
char checkTileForShark(short x, short y)
{
    manageWrapAround(&x, &y);

    if (sharksCollection[(GRID_COLUMNS * y) + x].active == 1)
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
char checkTileForFish(short x, short y)
{
    manageWrapAround(&x, &y);

    if (fishCollection[(GRID_COLUMNS * y) + x].active == 1)
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
    #pragma omp parallel for
    for(count = 0; count < SHARK_LIST_LENGTH; ++count)
    {
        if (fishCollection[(GRID_COLUMNS * y) + x].active == 1)
        {
            updateFish(x, y, &fishCollection[(GRID_COLUMNS * y) + x]);
        }
        else if (sharksCollection[(GRID_COLUMNS * y) + x].active == 1)
        {
            updateShark(x, y, &sharksCollection[(GRID_COLUMNS * y) + x]);
        }

        ++x;
        if ((count + 1) % GRID_COLUMNS == 0)
        {
            x = 0;
            ++y;
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
            if (fishCollection[(GRID_COLUMNS * y) + x].active == 1)
            {
                DrawFishAt(x, y);
            }
            else if (sharksCollection[(GRID_COLUMNS * y) + x].active == 1)
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
