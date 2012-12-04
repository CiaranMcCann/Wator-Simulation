/*! \file Fish.h
 *  \brief A file containing all functions for the Fish
*/
#ifndef FISH_H
#define FISH_H

#include "Globals.h"
#include "World.h"


/*! \brief A structure to hold the data memebers of Fish.
 *
 *  A simple structure which defines data memebers of Fish.
 */
typedef struct{
    char mSpawnCounter;
}Fish;

Fish fishCollection[FISH_LIST_LENGTH];

/*! \brief Creates fish.
 *
 *  Creates a fish type and initlizes it.
 */
Fish fishFactory()
{
    Fish pFish;
    pFish.mSpawnCounter = INACTIVE_VALUE;
    return pFish;
}

/*!
 *  \brief Moves the fish and handles spawning and dying.
 *
 *  \param x The old X position of the fish
 *  \param y The old Y position of the fish
 *  \param newX The new X position of the fish
 *  \param newY The new Y position of the fish
 *  \param fish The pointer to the fish to be moved
*/
void moveFish(short x, short y, short newX, short newY, Fish *fish)
{    
    fish->mSpawnCounter +=1;
    if(fish->mSpawnCounter==FISH_SPAWNRATE)
    {
        fish->mSpawnCounter = 0;
        activateFishAt(newX, newY);
    }
    else
    {
        Fish * newPFish = &fishCollection[newX + (newY * GRID_COLUMNS)];
	char spawnCount = fish->mSpawnCounter;
        deactivateAt(x, y);
        activateFishAt(newX, newY);
        newPFish->mSpawnCounter = spawnCount;
    }
}

/*!
 *  \brief Updates the fish.
 *
 *  \param x The X position of the fish
 *  \param y The Y position of the fish
 *  \param pFish The pointer to the fish to be moved
*/
void updateFish(short x, short y, Fish *pFish)
{
    char direction[4];
    char available = 0; // Number of available directions

    // Add all available directions to a char array
    // Increase the available parameter
    if(checkTileForEntity(x, y+1) == 0){
        direction[available] = 'N';
        available++; // Increase the number of available directions
    } 

    if(checkTileForEntity(x, y-1) == 0){
        direction[available] = 'S';
        available++;
    }

    if (checkTileForEntity(x+1, y) == 0){
        direction[available] = 'E';
        available++;
    }

    if (checkTileForEntity(x-1, y) == 0){
        direction[available] = 'W';
        available++;
    }

    if(available > 0) 
    {
        available = rand() % available;
        short newX = x;
        short newY = y;

        // Set the direction
        switch( direction[available] )
        {
                case 'N': // Direction is North
                    newY+=1;
                    break;
                case 'S': // Direction is South
                    newY-=1;
                    break;
                case 'E': // Direction is East
                    newX+=1;
                    break;
                case 'W': // Direction is West
                    newX-=1;
                    break;
                default :
                    break;
        }// end switch

        manageWrapAround(&newX, &newY);
        moveFish(x, y, newX, newY, pFish);                
    }
}

#endif
