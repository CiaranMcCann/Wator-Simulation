#ifndef GLOBALS_H
#define GLOBALS_H

/*! \brief A file containing shared variables.
 *
 *  A file which defines the variables shared throughout the Wator simulation.
 */

float const WindowHeight = 800.0f;
float const WindowWidth = 800.0f;

// NOTE: const in C means read-only, the value can still actually change
#define GRID_ROWS  500
#define GRID_COLUMNS 500
#define CYCLES_PER_FRAME 10000000

#define N_SHARKS 100
#define N_FISH 2000
#define FISH_SPAWNRATE 3
#define SHARK_SPAWNRATE 7
#define SHARK_STARVERATE 6

#endif
