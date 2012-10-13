#ifndef GLOBALS_H
#define GLOBALS_H

/*! \brief A file containing shared variables.
 *
 *  A file which defines the variables shared throughout the Wator simulation.
 */

float const WindowHeight = 800.0f;
float const WindowWidth = 800.0f;

// NOTE: const in C means read-only, the value can still actually change
#define GRID_ROWS  100
#define GRID_COLUMNS 100

#define N_SHARKS 100
#define N_FISH 500
#define FISH_SPAWNRATE 4
#define SHARK_SPAWNRATE 8
#define SHARK_STARVERATE 6

#endif
