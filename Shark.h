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
    int mFed;
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
       pShark->updated = 1;
       pShark->mStarveCounter = 0;
       pShark->mSpawnCounter = 0;
       pShark->mDead = 0;
       pShark->mFed = 0;

       return pShark;
}

void sharkMove(int x, int y, Shark * pShark)
{
    pShark->mSpawnCounter += 1;
    pShark->mStarveCounter += 1;

	if (pShark->mStarveCounter == SHARK_STARVERATE)
    {
    	pShark->mDead = 1;
    }
    else if (pShark->mSpawnCounter == SHARK_SPAWNRATE)
    {
    	createSharkAt(x, y);
    	pShark->mSpawnCounter = 0;
    }
    else
    {
	GridPosition newPosition;
	newPosition.X = x;
	newPosition.Y = y;
	moveSharkPointerTo(newPosition, pShark);
    	pShark->pos.X = x;
    	pShark->pos.Y = y;
    }
}

void sharkHunt(Shark * pShark)
{
	char dir[4];
	int i = 0;

	int x = pShark->pos.X;
	int y = pShark->pos.Y;

	if (checkTileForFish(x, y + 1) == 1)
	{
		dir[i] = 'N';
		++i;
	}
	if (checkTileForFish(x, y - 1) == 1)
	{
		dir[i] = 'S';
		++i;
	}
	if (checkTileForFish(x + 1, y) == 1)
	{
		dir[i] = 'E';
		++i;
	}
	if (checkTileForFish(x - 1, y) == 1)
	{
		dir[i] = 'W';
		++i;
	}


	if (i > 0)
	{
		i = rand() % i;

		switch( dir[i] )
        	{
	        	case 'N': // North
        			y+=1;
	                break;
	            case 'S': // South
            		y-=1;
	                break;
	            case 'E': // East
	            	x+=1;
	                break;
	            case 'W': // West
	            	x-=1;
	                break;
	            default :
	            	break;
        	}// end switch

		manageWrapAround(&x, &y);
		destroyAt(x, y);
		sharkMove(x, y, pShark);
		pShark->mFed = 1;
	}

}


void updateShark(int x, int y, Shark * pShark)
{
    // Make sure not to update twice
    if (pShark->updated == 1)
        return;

    sharkHunt(pShark);

    if (pShark->mFed == 0)
    {
    	char dir[4];
		int i = 0;


		if (checkTileForShark(x, y + 1) == 0)
		{
			dir[i] = 'N';
			++i;
		}
		if (checkTileForShark(x, y - 1) == 0)
		{
			dir[i] = 'S';
			++i;
		}
		if (checkTileForShark(x + 1, y) == 0)
		{
			dir[i] = 'E';
			++i;
		}
		if (checkTileForShark(x - 1, y) == 0)
		{
			dir[i] = 'W';
			++i;
		}

		if (i > 0)
		{
			i = rand() % i;
			x = pShark->pos.X;
			y = pShark->pos.Y;


			switch( dir[i] )
        	{
	        	case 'N': // North
        			y+=1;
	                break;
	            case 'S': // South
            		y-=1;
	                break;
	            case 'E': // East
	            	x+=1;
	                break;
	            case 'W': // West
	            	x-=1;
	                break;
	            default :
	            	break;
        	}// end switch

        	manageWrapAround(&x, &y);
			sharkMove(x, y, pShark);

			
		}// end if i
    }// end if mFed
    else
    {
    	pShark->mStarveCounter = 0;
    }

    pShark->updated = 1;
    pShark->mFed = 0;
}

#endif