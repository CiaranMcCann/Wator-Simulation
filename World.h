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
        }else{
            world[x][y].pShark = sharkFactory(x,y);
        }
    }
}


/*! \brief Destories the enity at given grid location
 *
 *  Destories the enity at given grid location and frees memory
 *  \param x - index into array
 *  \param y - index into array
 */
void destoryAt(int x, int y)
{
    free(world[x][y].pFish);
    free(world[x][y].pShark);

    world[x][y].pFish = 0;
    world[x][y].pShark = 0;
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

int checkTile(int x, int y)
{
    int i = 0;

    if(x < 0 || y < 0 || x > GRID_COLUMNS || y > GRID_ROWS) // Out of bounds check
        i = 0;
    else if(world[x][y].pShark == 1 || world[x][y].pFish == 1)
        i = 0;
    else
        i = 1;

     return i;
}

/*! update
 */

void update()
{
    int y = 0;

    for(y = 0; y < GRID_COLUMNS; y++)
    {
        int x = 0;
        for(x = 0; x < GRID_ROWS; x++)
        {
            if(world[x][y].pFish != 0) // Check if null
            {
                updateFish(x,y,world[x][y].pFish);
            }
        }
    }

}


/*! \brief Draws the world
 */
void drawWorld()
{
    int y = 0;
    for(y = 0; y < GRID_COLUMNS; y++)
    {
        int x = 0;
        for(x = 0; x < GRID_ROWS; x++)
        {
            if(world[x][y].pFish != 0) // Check if null
            {
                DrawFishAt(world[x][y].pFish->pos);
            }

            if(world[x][y].pShark != 0) // Check if null
            {
                DrawSharkAt(world[x][y].pShark->pos);
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
    for(y = 0; y < GRID_COLUMNS; y++)
    {
        int x = 0;
        for(x = 0; x < GRID_ROWS; x++)
        {
            destoryAt(x,y);
        }

    }
}



#endif
