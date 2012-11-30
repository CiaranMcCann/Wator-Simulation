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
    char active;
}Fish;

Fish fishCollection[FISH_LIST_LENGTH];

/*! \brief Creates fish.
 *
 *  Creates a fish type on the heap and initlizes it.
 *  WARNING: The call is responsible for freeing the memory after
 */
Fish fishFactory(short x, short y)
{
    Fish pFish;
    pFish.active = 0;
    pFish.mSpawnCounter = 0;
    return pFish;
}

/*! \ Moves the fish position
 *  Update the fish spawncounter by 1
 *  If the spawnrate equals the counter create a new fish in the new position. 
 *  
 *  @param short x The x position of the tile
 *  @param short y The x position of the tile
 *  @param Fish *fish Poshorter to the current fish
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
        deactivateAt(x, y);
        activateFishAt(newX, newY);
        newPFish->mSpawnCounter = fish->mSpawnCounter;
    }
}

/*! \ Checks the surrounding grid positions for a free tile
 *  Store the possible directions in a character array and increase the 'available' directions
 *  If the available directions is greater than 0 then a move is possible
 *  Pick a random number from the available directions and pass that to a switch statement
 *  Finally call movefish using the chosen direction
 *  @param short x The x position of the tile
 *  @param short y The y position of the tile
 *  @param Fish *fish Poshorter to the current fish
 */
void updateFish(short x, short y, Fish *pFish)
{
    char direction[4];
    char available = 0; //!< Number of available directions

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
