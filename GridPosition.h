#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

#include "Globals.h"

/*! \brief A structure to hold a grid location.
 *
 *  A simple structure which defines a position in a 2D coordinate system.
 */
typedef struct{
	int X;	/*!< The column number of the position. */
	int Y;	/*!< The row number of the position. */
}GridPosition;

#endif