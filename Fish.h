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

#endif
