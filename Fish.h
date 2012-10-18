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
       pFish->updated = 1;
       pFish->mSpawnCounter = 0;
       return pFish;
}

/*! \ Moves the fish position
 *	
 *  
 */

void moveFish(int x, int y, Fish *fish)
{
    fish->mSpawnCounter +=1;

    if(fish->mSpawnCounter==FISH_SPAWNRATE)
    {
        fish->mSpawnCounter=0;
        createFishAt(x,y);
    }
    else
    {
	GridPosition newPosition;
	newPosition.X = x;
	newPosition.Y = y;
	moveFishPointerTo(newPosition, fish);
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

void updateFish(int x, int y, Fish *pFish)
{

    if (pFish->updated == 1)
        return;

    

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
        x = pFish->pos.X;
        y = pFish->pos.Y;


        switch( direction[i] )
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
        moveFish(x, y, pFish);
                
    }


}

#endif
