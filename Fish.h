#ifndef FISH_H
#define FISH_H

#include "Globals.h"
#include "GridPosition.h"


/*! \brief A structure to hold the data memebers of Fish.
 *
 *  A simple structure which defines data memebers of Fish.
 */
typedef struct{
    GridPosition pos;
    int updated;  /*!< Bool flag - To stop a enity been updated twice */
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

       return pFish;
}

/*! \ Moves the fish position
 *	
 *  
 */

int moveFish(int x, int y, Fish *fish)
{
	fish->pos.X = x;
	fish->pos.Y = y;

	return 1;
}


/*! \ Checks the surrounding grid positions for a free tile
 *  
 *  I was originally going to use a loop to keep trying randoms until it hit one that was free
 *  But I decided to 
 */

void updateFish(int x, int y, Fish *fish)
{
	// Make sure updated is set to 0 
    fish->updated = 0; 
    char* direction;
    int i = 0;

    // Add all available directions to a char array
    // Will try and refactor this
    if(checkTile(x, y+1) == 0){
    	direction[i] = 'N';
    	i++;
    } 
    
    if(checkTile(x, y-1) == 0){
    	direction[i] = 'S';
    	i++;
    }

    if (checkTile(x+1, y) == 0){
    	direction[i] = 'E';
    	i++;
    }


    if (checkTile(x+1, y) == 0){
    	direction[i] = 'W';
    	i++;
    }

    // If  there are no available moves set updated to 1 and skip a move
    if (i==0)
    	fish->updated = 1;

    if(fish->updated==0) // I
    {
        i = rand() % i;

        switch( direction[i] )
        {
            case 'N': // North
                    fish->updated = moveFish(x, y+1, fish);
                break;
            case 'S': // South
                    fish->updated = moveFish(x, y-1, fish);
                break;
            case 'E': // East
                    fish->updated = moveFish(x+1, y, fish);
                break;
            case 'W': // West
                    fish->updated = moveFish(x-1, y, fish);
                break;
            default :
            		fish->updated = 1;
            	break;
        }
            
    }


}

#endif
