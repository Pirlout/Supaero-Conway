# Supaero-Conway
Implementation of Conway's game of life in C as homework in ISAE-Supaero engineering program

/** 
 * @mainpage Details on the project
 * 
 * @author Pierre-Louis Sauvage (pierre-louis.sauvage@student.isae-supaero.fr)
 * @date March 14th 2017
 *
 *
 * Purpose :
 * The objective of this mini-project was to use linked-list structures with a practical application : Conway's game of life.
 * Cells are represented with a linked list structure called "cell", inside a game definition structure called "problem".
 * The project also asked students to load from a text file data, then outputs the result of the calculations as a PPM image file.
 * 
 * Behavior :
 * The app-conway main program works in specific steps :
 * - input prompts from the user to parameter the simulation (data to load, game rules to use)
 * - loads data
 * - generates PPM image representing the state of the game
 * - iterates the game with rules defined by the user
 * - repeats the last two steps until enough iterations are calculated
 * 
 * Documentation :
 * Important functions are documented in this Doxygen doc. Auxiliary functions are documented directly in the source code to improve readability of both source code and documentation.
 * 
 * Status of the project : 
 * - everything compiles under -Wall -Werror gcc options (meaning no errors or warnings)
 * - no memory leak during execution (checked with valgrind, see warning at the end)
 * - execution ends (with a non-infinite wanted number of iterations, see warning at the end)
 * - output correct (checked by hand with provided test inputs)
 * 
 * Extensions :
 * - work on ergonomy without the need of modifying source code (terminal input prompts for data path or custom rules for eg.)
 * - possibility of changing basic game's rules : min/max number of neighbours to birth a cell and min/max number of neighbours to keep a cell alive
 * - nice documentation (main page, custom theme, logo)
 * 
 * Makefile useful commands :
 * 
 * - make doc :                 generates doxygen documentation in ./doc
 * 
 * - make firefox-doc :         generates doxygen documentation in ./doc then starts firefox to visualize doc
 *
 * - make compile-all :         compiles app-conway.c final program of the miniproject (which includes all c files) (debug mode) 
 *                              (same as make app-conway, but required by the project)
 * 
 * - make app-conway :          compiles app-conway.c final program of the miniproject (which includes all c files) (debug mode)
 * 
 * - make launch-app-conway :   deletes every file in ./out, 
 *                              executes app-conway program,
 *                              converts the PPM output files to a GIF, then finally
 *                              opens image viewer to watch the GIF (close the animation to use shell)
 *                         
 * - make valgrind-app-conway : deletes every file in ./out then starts valgrind test on app-conway executable
 *
 * - make speed-conway :        compiles app-conway.c final program of the miniproject (which includes all c files) (optimized mode)
 *
 * - make launch-speed-conway : deletes every file in ./out, 
 *                              executes app-conway program,
 *                              converts the PPM output files to a GIF, then finally 
 *                              opens image viewer to watch the GIF (close the animation to use shell)
 * 
 * @warning Do not use make valgrind-app-conway with custom game rules on big grid sizes with big wanted number of iterations as the execution time may increase a lot with the number of allocations, effectively crashing shell.
 *
 * @copyright CC BY-NC-SA 3.0
 */
