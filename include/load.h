/**
 * @file load.h
 * 
 * @brief Converts a grid structure in a text file to Conway's game of life problem structure.
 *
 * @author Pierre-Louis Sauvage (PC D)
 *
 * This implementation allows the user to input a Conway's game of life problem structure
 * onto a text file.
 *
 * Syntax of the text input file :
 *
 * 1st line : the width and the height of the grid as two integers separated by a space
 *
 * 2nd line : the number of iterations required as an integer
 *
 * Next lines : the grid line by line, dead cells being represented by a '.' character,
 * and alive cells being represented by a 'o' character.
 */

#ifndef CELL_H
#define CELL_H


/**
 * @brief Converts a text file to the conway's problem structure.
 *
 * @param filename        a pointer to the path to the text file as a string
 *
 * @return a pointer to the game problem generated from the text file
 */
problem* load_grid(const char* filename);


#endif
