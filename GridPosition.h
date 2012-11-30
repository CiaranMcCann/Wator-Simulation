/*! \file GridPosition.h
 *  \brief Defines a structure to hold 2D positions.
 */
#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

#include "Globals.h"

/*! \brief A structure to hold a grid location.
 *
 *  A simple structure which defines a position in a 2D coordinate system.
 */
typedef struct{
	short X;	/*!< The column number of the position. */
	short Y;	/*!< The row number of the position. */
}GridPosition;

#endif