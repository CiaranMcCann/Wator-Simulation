/*! \file Shark.h
 *  \brief A file containing all functions for the Shark
*/
#ifndef SHARK_H
#define SHARK_H

#include "Globals.h"
#include "World.h"

/*! \brief A structure to hold the data memebers of Shark.
 *
 *  A simple structure which defines data memebers of Shark.
 */
typedef struct{
    char mSpawnCounter;
    char mStarveCounter;
}Shark;

Shark sharksCollection[SHARK_LIST_LENGTH];

/*! \brief Creates a shark.
 *
 *  Creates a shark type and initlizes it.
 */
Shark sharkFactory()
{
   Shark pShark;
   pShark.mStarveCounter = 0;
   pShark.mSpawnCounter = INACTIVE_VALUE;
   return pShark;
}

/*!
 *  \brief Moves the shark and handles spawning and dying.
 *
 *  \param x The  old X position of the shark
 *  \param y The old Y position of the shark
 *  \param newX The new X position of the shark
 *  \param newY The new Y position of the shark
 *  \param pShark The pointer to the shark to be moved
*/
void sharkMove(short x, short y, short newX, short newY, Shark * pShark)
{
    pShark->mSpawnCounter += 1;
    pShark->mStarveCounter += 1;

	if (pShark->mStarveCounter == SHARK_STARVERATE)
    {
	pShark->mSpawnCounter = INACTIVE_VALUE;
    }
    else if (pShark->mSpawnCounter == SHARK_SPAWNRATE)
    {    	
    	activateSharkAt(newX, newY);
    	pShark->mSpawnCounter = 0;
    }
    else
    {   
    	Shark * newPShark = &sharksCollection[newX + (newY * GRID_COLUMNS)];
	char spawnCount = pShark->mSpawnCounter;
    	deactivateAt(x, y);
    	activateSharkAt(newX, newY);
    	newPShark->mStarveCounter = pShark->mStarveCounter;
    	newPShark->mSpawnCounter = spawnCount;
    }
}

/*!
 *  \brief Function for the shark to hunt for fish
 *
 *  \param x The  old X position of the shark
 *  \param y The old Y position of the shark
 *  \param pShark The pointer to the shark to be moved
*/
char sharkHunt(short x, short y, Shark * pShark)
{
	char dir[4];
	char i = 0;

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
		short newX = x;
		short newY = y;
		i = rand() % i;
		switch( dir[i] )
    	{
        	case 'N': // North
    			newY+=1;
                break;
            case 'S': // South
        		newY-=1;
                break;
            case 'E': // East
            	newX+=1;
                break;
            case 'W': // West
            	newX-=1;
                break;
            default :
            	break;
    	}// end switch

		manageWrapAround(&newX, &newY);
		deactivateAt(newX, newY);
		pShark->mStarveCounter = 0;
		sharkMove(x, y, newX, newY, pShark);
		return 1;
	}

	return 0;
}

/*!
 *  \brief Updates the shark.
 *
 *  \param x The X position of the shark
 *  \param y The Y position of the shark
 *  \param pShark The pointer to the shark to be moved
*/
void updateShark(short x, short y, Shark * pShark)
{
    if (sharkHunt(x, y, pShark) == 0)
    {
    	char dir[4];
		char i = 0;

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
			short newX = x;
			short newY = y;

			switch( dir[i] )
        	{
	        	case 'N': // North
        			newY+=1;
	                break;
	            case 'S': // South
            		newY-=1;
	                break;
	            case 'E': // East
	            	newX+=1;
	                break;
	            case 'W': // West
	            	newX-=1;
	                break;
	            default :
	            	break;
        	}// end switch

        	manageWrapAround(&newX, &newY);
			sharkMove(x, y, newX, newY, pShark);			
		}// end if i
    }// end if mFed
    else
    {
    	pShark->mStarveCounter = 0;
    }
}

#endif