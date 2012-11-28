/*! \file Globals.h
 *  \brief A file which defines the variables shared throughout the Wator simulation.
 */
 
#ifndef GLOBALS_H
#define GLOBALS_H

float const WindowHeight = 800.0f;	/*!< The height of the window to create. */
float const WindowWidth = 800.0f;	/*!< The width of the window to create. */

int numThreads = 1;		/*!< The number of threads to use.*/

#define NUMBER_OF_RUNS 4		/*!< The number of times the simulation should run. */

#define GRID_ROWS  4000		/*!< The number of rows in the grid. */
#define GRID_COLUMNS 4000		/*!< The number of columns in the grid. */
#define CYCLES_PER_FRAME 1	/*!< The number of cycles which must complete before an update occurs. */

#define N_SHARKS 1000	/*!< The initial number of sharks. */
#define N_FISH 2000	/*!< The initial number of fish. */
#define FISH_SPAWNRATE 3	/*!< The number of updates which must occur before a fish can spawn. */
#define SHARK_SPAWNRATE 7	/*!< The number of updates which must occur before a shark can spawn. */
#define SHARK_STARVERATE 6	/*!< The number of updates which must occur before a shark will die of starvation. */

#define DRAW_GRID 0	/*!< Whether the grid should be drawn or not. */
#define SIMULATION_LENGTH  5	/*!< The number of seconds to run for, when benchmarking. */

#endif
