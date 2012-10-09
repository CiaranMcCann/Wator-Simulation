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

       return pShark;
}


#endif
