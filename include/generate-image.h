/**
* @file generate-image.h
*
* @brief Generates from a Conway's game of life problem images for each iteration.
*
* @author Pierre-Louis Sauvage (PC D)
*
* This implementation converts a Conway's game of life problem to PPM images for each iteration required by the problem.
*
* These images are stored in ./out/ directory and can later on be converted to a GIF animation thanks to the shell command convert.
* 
* DEAD cells are in WHITE color, ALIVE cells are in BLUE color, NEWBORN cells are in GREEN color and DYING cells are in RED color.
* 
*/
#ifndef GENERATE_IMAGE_H
#define GENERATE_IMAGE_H

//this function is auxiliary : it is documented in generate-image.c file
int number_digits_from_int(int steps_number);


/**
 * @brief Generates a PPM file located in ./out representing the current state of the game.
 *
 * @param p_game_problem  a pointer to the current game problem
 * @param game_size_x     an integer representing the grid width
 * @param game_size_y     an integer representing the grid height
 * @param file_path       the path to the output PPM file
*/
void generate_frame(problem* p_game_problem, int game_size_x, int game_size_y, char* file_path);


/**
 * @brief Generates PPM files located in ./out, each representing an iteration of the Conway's problem
 *
 * @param p_game_problem  a pointer to the game problem
*/
void generate_image(problem* p_game_problem);


#endif
