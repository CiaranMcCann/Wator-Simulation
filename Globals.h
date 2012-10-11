#ifndef GLOBALS_H
#define GLOBALS_H

/*! \brief A file containing shared variables.
 *
 *  A file which defines the variables shared throughout the Wator simulation.
 */

float const WindowHeight = 900.0f;
float const WindowWidth = 900.0f;

// NOTE: const in C means read-only, the value can still actually change
#define GRID_ROWS  1000
#define GRID_COLUMNS 1000

#define N_SHARKS 100
#define N_FISH 40

#endif
