#ifndef SHARK_H
#define SHARK_H

#include "Globals.h"
#include "World.h"
#include "GridPosition.h"

/*! \brief A structure to hold the data memebers of Shark.
 *
 *  A simple structure which defines data memebers of Shark.
 */
typedef struct{
    GridPosition pos;
    int updated;  /*!< Bool flag - To stop a enity been updated twice */
    int mSpawnCounter;
    int mStarveCounter;
    int mDead;
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
       pShark->mStarveCounter = 0;
       pShark->mSpawnCounter = 0;
       pShark->mDead = 0;

       return pShark;
}



/*
*/
void sharkMove(int x, int y, Shark * pShark)
{
    pShark->mSpawnCounter += 1;
    pShark->mStarveCounter += 1;

    // handle wrap around
    if (x < 0)
        x = GRID_COLUMNS - 1;
    else if (x >= GRID_COLUMNS)
        x = 0;

    if (y < 0)
        y = GRID_ROWS - 1;
    else if (y >= GRID_ROWS)
        y = 0;


    if (pShark->mSpawnCounter == SHARK_SPAWNRATE)
    {
    	pShark->mSpawnCounter = 0;
    	createSharkAt(x, y);

    }
    else
    {
    	pShark->pos.X = x;
    	pShark->pos.Y = y;
    }

    // Move to an empty space in the grid
    
}

int sharkHunt(Shark * pShark)
{
	char direction[4];
	int i = 0;

	int x = pShark->pos.X;
	int y = pShark->pos.Y;

	if (checkTileForFish(x, y+1) == 1)
	{
		direction[i] = 'N';
		i++;
	}

	if (checkTileForFish(x, y-1) == 1)
	{
		direction[i] = 'S';
		i++;
	}

	if (checkTileForFish(x+1, y) == 1)
	{
		direction[i] == 'E';
		i++;
	}

	if (checkTileForFish(x-1, y) == 1)
	{
		direction[i] == 'W';
		i++;
	}

	if ( i > 0 )
	{
		i = rand() % i;

		switch( direction[i] )
		{
			case 'N':
				sharkEat(x, y+1, pShark);
				break;
			case 'S':
				sharkEat(x, y-1, pShark);
				break;
			case 'E':
				sharkEat(x+1, y, pShark);
				break;
			case 'W':
				sharkEat(x-1, y, pShark);
				break;
			default:
				break;
		}

		return 1;
	}

	return 0;
}

void sharkEat(int x, int y, Shark * pShark)
{
	pShark->mStarveCounter = 0;

	sharkMove(x, y, pShark);

	// handle wrap around
    if (x < 0)
        x = GRID_COLUMNS - 1;
    else if (x >= GRID_COLUMNS)
        x = 0;

    if (y < 0)
        y = GRID_ROWS - 1;
    else if (y >= GRID_ROWS)
        y = 0;

	destroyAt(x, y);
}

/*
*/
void sharkDie(Shark * pShark)
{
    if (pShark->mStarveCounter == SHARK_STARVERATE)
    {
    	pShark->mDead = 1;
    }
}


/*
*/
void updateShark(int x, int y, Shark * pShark)
{
    // Make sure not to update twice
    if (pShark->updated == 1)
        return;

    
	if (sharkHunt(pShark) == 0)
	{
	    // Move
	    char direction[4];
		int i = 0;

	    if (checkTileForEntity(x, y+1) == 0)
		{
			direction[i] = 'N';
			i++;
		}

		if (checkTileForEntity(x, y-1) == 0)
		{
			direction[i] = 'S';
			i++;
		}

		if (checkTileForEntity(x+1, y) == 0)
		{
			direction[i] == 'E';
			i++;
		}

		if (checkTileForEntity(x-1, y) == 0)
		{
			direction[i] == 'W';
			i++;
		}

		if ( i > 0 )
		{
			i = rand() % i;

			switch( direction[i] )
			{
				case 'N':
					sharkMove(x, y+1, pShark);
					break;
				case 'S':
					sharkMove(x, y-1, pShark);
					break;
				case 'E':
					sharkMove(x+1, y, pShark);
					break;
				case 'W':
					sharkMove(x-1, y, pShark);
					break;
				default:
					break;
			}// end switch
		}// end if
	}


	// Die
    sharkDie(pShark);

    pShark->updated = 1;
}

#endif