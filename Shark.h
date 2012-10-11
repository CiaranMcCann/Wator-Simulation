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
    void sharkUpdate(Shark * pShark)
    void move(Shark * pShark)
    void die(Shark * pShark)
    void spawn(Shark * pShark)
*/

/*
*/
void sharkUpdate(Shark * pShark)
{
	// Move
	// Spawn
	// Die
}

/*
*/
void sharkMove(Shark * pShark)
{
	// Move to an empty space in the grid
	// Store previous position
}

/*
*/
void sharkDie(Shark * pShark)
{
	if (pShark->mAge % pShark->mStarveTime == 0)
	{
	   // Die
	}
}

/*
*/
void sharkSpawn(Shark * pShark)
{
	if (pShark->mAge % pShark->mSpawnTime == 0)
	{
		// Spawn a new shark in the prvious position
	}
}

#endif