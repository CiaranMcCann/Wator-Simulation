#ifndef FISH_H
#define FISH_H

#include "Globals.h"
#include "World.h"
#include "GridPosition.h"


/*! \brief A structure to hold the data memebers of Fish.
 *
 *  A simple structure which defines data memebers of Fish.
 */
typedef struct{
    GridPosition pos;
    int updated;  /*!< Bool flag - To stop a enity been updated twice */
    int mSpawnCounter;

}Fish;


/*! \brief Creates fish.
 *
 *  Creates a fish type on the heap and initlizes it.
 *  WARNING: The call is repsonisbly for freeing the memory after
 */
Fish * fishFactory(int x, int y)
{
       Fish * pFish =  malloc(sizeof(Fish));
       pFish->pos.X = x;
       pFish->pos.Y = y;
       pFish->updated = 0;
       pFish->mSpawnCounter = 0;
       return pFish;
}

/*! \ Moves the fish position
 *	
 *  
 */

void moveFish(int x, int y, Fish *fish)
{
    // handle wrap around
    if (x < 0)
        x = GRID_COLUMNS - 1;
    else if (x >= GRID_COLUMNS)
        x = 0;

    if (y < 0)
        y = GRID_ROWS - 1;
    else if (y >= GRID_ROWS)
        y = 0;

    fish->mSpawnCounter +=1;

    if(fish->mSpawnCounter==FISH_SPAWNRATE)
    {
        fish->mSpawnCounter=0;
        createFishAt(x,y);
    }
    else
    {
    	fish->pos.X = x;
    	fish->pos.Y = y;
        // Updated fish age
    }
}



/*! \ Checks the surrounding grid positions for a free tile
 *  
 *  I was originally going to use a loop to keep trying randoms until it hit one that was free
 *  But I decided to 
 */

void updateFish(int x, int y, Fish *fish)
{

    if (fish->updated == 1)
        return;

    fish->updated = 1;
	// Make sure updated is set to 0 
    char direction[4];
    int i = 0;

    // Add all available directions to a char array
    // Will try and refactor this
    if(checkTileForEntity(x, y+1) == 0){
    	direction[i] = 'N';
    	i++;
    } 
    
    if(checkTileForEntity(x, y-1) == 0){
    	direction[i] = 'S';
    	i++;
    }

    if (checkTileForEntity(x+1, y) == 0){
    	direction[i] = 'E';
    	i++;
    }


    if (checkTileForEntity(x-1, y) == 0){
    	direction[i] = 'W';
    	i++;
    }

    if(i>0) // I
    {
        i = rand() % i;

        switch( direction[i] )
        {
            case 'N': // North
                    moveFish(x, y+1, fish);
                break;
            case 'S': // South
                    moveFish(x, y-1, fish);
                break;
            case 'E': // East
                    moveFish(x+1, y, fish);
                break;
            case 'W': // West
                     moveFish(x-1, y, fish);
                break;
            default :
            	break;
        }
            
    }


}

#endif
