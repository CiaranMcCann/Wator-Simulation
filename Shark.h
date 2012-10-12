#ifndef SHARK_H
#define SHARK_H

#include "Globals.h"
#include "GridPosition.h"

/*! \brief A structure to hold the data memebers of Shark.
 *
 *  A simple structure which defines data memebers of Shark.
 */
typedef struct{
    GridPosition pos;
    int updated;  /*!< Bool flag - To stop a enity been updated twice */
    int mSpawnTime;
    int mStarveTime;
    int mAge;
}Shark;


/*! \brief Creates a shark.
 *
 *  Creates a shark type on the heap and initlizes it.
 *  WARNING: The call is repsonisbly for freeing the memory after
 */
Shark * sharkFactory(int x, int y)
{
       Shark * pShark =  malloc(sizeof(Shark));
       pShark->pos.X = x;
       pShark->pos.Y = y;
       pShark->updated = 0;
       pShark->mAge = 1;
       pShark->mStarveTime = 4;
       pShark->mSpawnTime = 5;

       return pShark;
}



/*
*/
void sharkMove(Shark * pShark)
{
    GridPosition newPos;
    // Move to an empty space in the grid
    
}

/*
*/
void sharkDie(Shark * pShark)
{
    if (pShark->mAge % pShark->mStarveTime == 0)
    {
       
    }
}

/*
*/
void sharkSpawn(Shark * pShark, GridPosition spawnPos)
{
    if (pShark->mAge % pShark->mSpawnTime == 0)
    {
        // Spawn a new shark in the previous position
        pShark->mAge = 1;
    }
}

/*
*/
void sharkUpdate(Shark * pShark)
{
    // Make sure not to update twice
    if (pShark->updated == 1)
        return;

    // Store the previous position for spawning
    GridPosition prevPos = pShark->pos;
	
    // Move
	sharkMove(pShark);
    
    // Spawn
	sharkSpawn(pShark, prevPos);
    
    // Die
    sharkDie(pShark);

    pShark->updated = 1;
}

#endif