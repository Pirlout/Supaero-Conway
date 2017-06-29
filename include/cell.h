/**
 * @file cell.h
 *
 * @brief Conway's game of life implementation using linked list structure.
 *
 * @author Pierre-Louis Sauvage (PC D)
 *
 * This is an implementation of Conway's game of life using a linked list of cells
 * to save memory compared to a naive implementation.
 *
 * Hypothesis : the world outside of the boundaries defined by the user is no cell's land.
 * Any creation of cell there would get cancelled.
 *
 * Warning : the cells pointers should not be shared (deallocation of the game deallocates
 * the memory space reserved for cells and for the game problem definition) !
 * 
 * The API of the game's implementation is as follows :
 * - a function to create an empty cell list
 * - a function to add a cell
 * - a function to delete a cell from its neighbours' neighbours list
 * - a function to suppress DYING cells from the cell list
 * - a function to grow NEWBORN cells to ALIVE status
 * - a function to murder the cells to DYING status if they don't respect the rules of the game
 * - a function to birth new cells to NEWBORN status if they respect the rules of the game
 * - a function to evolve the game's problem to the next generation
 * - a function to deallocate the game problem (including the cell list).
 * 
 * NOTE : The following documentation only covers the API functions. Please refer to cell.c source file for the documentation of utilitary and printing functions.
 */

#ifndef CELL_H
#define CELL_H


/**
 * @brief An alias to the struct representing the game problem.
 */
typedef struct problem problem;


/**
 * @brief An alias to the struct representing a cell.
 */
typedef struct cell cell;


/**
 * @brief An alias to the struct representing the position of a cell.
 */
typedef struct pos pos;


/**
 * @brief An alias to the enumeration of states of a cell.
 */
typedef enum {
	/** Cell is alive for more than one iteration. */
	ALIVE,
	/** Cell got revived during the previous iteration. */
	NEWBORN,
	/** Cell got killed during the previous iteration. */
	DYING
} status;


/**
 * @brief The structure representing the position of a cell.
 */
struct pos {
	/** The x coordinate of the cell */
	int x;
	/** The y coordinate of the cell */
	int y; 
};


/**
 * @brief The structure representing a cell.
 */
struct cell {
	/** The state of the cell. */
	status state;
	/** The position of the cell. */
	pos position;
	/** The list of pointers to the neighbours of the cell. */
	cell* neighbours[8];
	/** The pointer to the next cell in the game. */
	cell* next_cell;
};


/**
 * @brief The structure representing the game problem.
 */
struct problem {
	/** The size of the world studied [width, height]. */
	int game_size [2];
	/** The number of iterations to do. */
	int steps_number;
	/** The linked list of cells in the game. */
	cell* cell_list; 
	/** The number of neighbours cells required to birth a cell [minimum, maximum]. */
	int birth_window [2];
	/** The number of neighbours cells required to keep alive a cell [minimum, maximum]. */
	int live_window [2];
};



///////////////////////////////////////////
//  FUNCTIONS DOCUMENTED IN cell.c FILE  //
///////////////////////////////////////////

//utilitary functions
pos index_neighbour_to_position(int index, pos cell_position);
int index_to_relative_x(int index);
int index_to_relative_y(int index);
int change_pov(int index);
bool is_cell_1_neighbour_cell_2(cell* p_cell_1, cell* p_cell_2);
bool is_pos_1_neighbour_pos_2(pos pos_1, pos pos_2);
bool is_out_of_bounds(pos position, problem* p_game_problem);
int relative_pos(pos position_origin_cell, pos position_cell_checked);

//printing functions
void print_cell_pos(cell* p_cell_checked);
void print_neighbours_pos(cell* p_cell_checked);
void print_existing_cells_number(cell* p_cell_list);
void print_existing_cells_pos(cell* p_cell_list);



///////////////////////////////////////////
// FUNCTIONS DOCUMENTED WITH DOXYGEN DOC //
///////////////////////////////////////////

/**
 * @brief Creates an empty game problem.
 *
 * @return a pointer to the game problem allocated.
 */
problem* create_game_problem(void);


/**
 * @brief Creates a cell and links it to the cell list.
 *
 * @param cell_state      the state of the cell to be created.
 * @param cell_position   the position of the cell to be created.
 * @param p_cell_list     a pointer to the cell list.
 * @param p_game_problem  a pointer to the defined problem.
 *
 * @return a pointer to the cell list that now includes the created cell.
 */
cell* create_cell(status cell_state, pos cell_position, cell* p_cell_list, problem* p_game_problem);


/**
 * @brief Deletes a cell from its neighbours' neighbour pointer array.
 *
 * @param p_neighbour_to_delete  a pointer to the cell to delete from its neighbours.
 * @param p_cell_list            a pointer to the cell list.
 */
void suppress_cell_from_neighbours(cell* p_neighbour_to_delete, cell* p_cell_list);


/**
 * @brief Deletes from the cell list any cells with DYING state (which are deallocated).
 *
 * @param p_game_problem  a pointer to the game problem
*/
void suppress_dying_cells(problem* p_game_problem);


/**
 * @brief Transforms in the cell list any cells with NEWBORN state to ALIVE state.
 *
 * @param p_game_problem  a pointer to the game problem.
 */
void grow_newborn_cells(problem* p_game_problem);

/**
 * @brief Transforms in the cell list any cells with ALIVE state 
 *        not respecting the rules to DYING state.
 *
 * @param p_game_problem  a pointer to the game problem.
 */
void murder_cells_in_danger(problem* p_game_problem);


/**
 * @brief Adds to the cell list any NEWBORN cell 
 *        that can be created according to the rules.
 *
 * @param p_game_problem  a pointer to the defined problem
 */
void birth_new_cells(problem* p_game_problem);


/**
 * @brief Iterates the cell list according to the Game of life's rules.
 *
 * @param p_game_problem  a pointer to the defined problem
 */
void next_generation(problem* p_game_problem);


/**
 * @brief Deallocates the cells from the cell list and the defined problem.
 *
 * @param p_game_problem a pointer to the defined problem.
 */
void nuke_everything(problem* p_game_problem);




#endif
