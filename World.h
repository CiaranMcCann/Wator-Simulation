#ifndef WORLD_H
#define WORLD_H

#include "Fish.h"
#include "Shark.h"
#include "Globals.h"
#include <time.h>
#include <stdlib.h>

typedef struct {
    Fish * pFish;
    Shark * pShark;
} GirdObj;

 // Array of GirdObjs which
GirdObj world[GRID_ROWS][GRID_COLUMNS ];

// Seems to be no standard LinkedList lib? Joe lied? wtf?
//TODO Linked list of sharks
//TODO linked list of fish


/*! \brief Populates the world
 *
 *  Randomly populates the world array with sharks and fish
 *  \param nFish - Number of fish
 *  \param nShark - Number of sharks
 */
void populate(int nFish, int nSharks){
//    Its probably a good idea to emphasize that srand() should only be called once.
//    Also, in a threaded application, might want to make sure that the generator's
//    state is stored per thread, and seed the generator once for each thread.
    srand(time(NULL));

    int total = nFish + nSharks;

    int i = 0; //C90 standard doesn't allow loop var declaration inside loop
    for(i = 0; i < total; i++)
    {
        if(total - nFish > nSharks){
            //continue with popluating fish
            world[rand() % GRID_ROWS][rand() % GRID_COLUMNS ].pFish = 0; // malloc(sizeof(Fish));
        }else{
            // once all fish done popluate sharks
            world[rand() % GRID_ROWS][rand() % GRID_COLUMNS ].pShark = 0; //malloc(sizeof(Shark));
        }

    }

}

/*! \brief Destories the enity at given grid location
 *
 *  Destories the enity at given grid location
 *  \param x - index into array
 *  \param y - index into array
 */
void clean(){


}

/*! \brief Creates either a fish or a shark.
 *
 * Function only really exists because as a user I hate int flags
 */
void _createAt(int x, int y, int fishFlag)
{
    if( world[x][y].pFish == 0 &&  world[x][y].pShark == 0)
    {
        if(fishFlag)
        {
              world[x][y].pFish = 0; //TODO: Linked list push malloc(sizeof(Fish));
        }else{
            world[x][y].pShark = 0; //TODO: Linked list push malloc(sizeof(Shark))
        }
    }
}


/*! \brief Destories the enity at given grid location
 *
 *  Destories the enity at given grid location
 *  \param x - index into array
 *  \param y - index into array
 */
void destoryAt(int x, int y)
{

}


/*! \brief Creates fish at given [x][y]
 *
 *  Creates fish at given [x][y]
 *  \param x - index into array
 *  \param y - index into array
 */
void createFishAt(int x, int y){
    _createAt(x,y,1);
}

/*! \brief Creates shark at given [x][y]
 *
 *  Creates shark at given [x][y]
 *  \param x - index into array
 *  \param y - index into array
 */
void createSharkAt(int x, int y){
    _createAt(x,y,0);
}


#endif
