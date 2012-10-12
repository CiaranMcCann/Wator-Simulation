#ifndef GLOBALS_H
#define GLOBALS_H

/*! \brief A file containing shared variables.
 *
 *  A file which defines the variables shared throughout the Wator simulation.
 */

float const WindowHeight = 600.0f;
float const WindowWidth = 600.0f;

// NOTE: const in C means read-only, the value can still actually change
#define GRID_ROWS  100
#define GRID_COLUMNS 100

#define N_SHARKS 20
#define N_FISH 10
#define FISH_SPAWNRATE 4
#define SHARK_SPAWNRATE 5
#define SHARK_STARVERATE 6

#endif
