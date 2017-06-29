#include <stdio.h>
#include <stdlib.h>

#include "../include/cell.h"
#include "cell.c"

int main(void) {
	
	cell* p_cell_list=create_cell_list();
	problem* p_game_problem = malloc(sizeof(problem));
	(p_game_problem -> game_size)[0] = 20;
	(p_game_problem -> game_size)[1] = 20;
	p_game_problem -> cell_list = p_cell_list;
	
	pos cell_position;
	
	cell_position.x=2;
	cell_position.y=0;
	p_cell_list=create_cell(ALIVE, cell_position, p_cell_list, p_game_problem);

	cell_position.x=3;
	cell_position.y=0;
	p_cell_list=create_cell(ALIVE, cell_position, p_cell_list, p_game_problem);
	
	cell_position.x=4;
	cell_position.y=0;
	p_cell_list=create_cell(ALIVE, cell_position, p_cell_list, p_game_problem);
	/*
	cell_position.x=7;
	cell_position.y=6;
	p_cell_list=create_cell(ALIVE, cell_position, p_cell_list, p_game_problem);
	
	cell_position.x=6;
	cell_position.y=7;
	p_cell_list=create_cell(ALIVE, cell_position, p_cell_list, p_game_problem);
	*/
	p_game_problem->cell_list=p_cell_list;
	
	printf("\niteration 0\n");
	print_existing_cells_pos(p_cell_list);


	next_generation(p_game_problem);
	printf("\niteration 1\n");
	print_existing_cells_pos(p_game_problem->cell_list);
	
	next_generation(p_game_problem);
	printf("\niteration 2\n");
	print_existing_cells_pos(p_game_problem->cell_list);
	
	next_generation(p_game_problem);
	printf("\niteration 3\n");	
	print_existing_cells_pos(p_game_problem->cell_list);
	
	next_generation(p_game_problem);
	print_existing_cells_pos(p_game_problem->cell_list);
	printf("\niteration 4\n");

/*
	p_cell_list = suppress_dying_cells(p_cell_list);
	grow_newborn_cells(p_cell_list);
	p_cell_list=birth_new_cells(p_cell_list, p_game_problem);
	printf("trying murder\n");
	print_existing_cells_pos(p_cell_list);
*/	
	
	
	
	return 0;
}
