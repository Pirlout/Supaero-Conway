#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "../include/cell.h"

/*
* Functions NOT from the API will be documented here.
* This documentation does not follow the Doxygen
* convention, it is just helping the coding process.
* Documentation of functions from the API can be found in
* ../include/cell.h, or in the Doxygen generated doc.
*/




////////////////////////////////////
//      UTILITARY FUNCTIONS       //
////////////////////////////////////


/*Gives the position of a particular neighbour of a given cell.
* Parameters : the index in the list of neighbours of the cell (int), and its position (pos).
* Output : position of the neighbour (pos).
* Calls : index_to_relative_x and index_to_relative_y functions. */
pos index_neighbour_to_position(int index, pos cell_position) {
	cell_position.x=cell_position.x + index_to_relative_x(index);
	cell_position.y=cell_position.y + index_to_relative_y(index);
	return cell_position;
}


/*Gives the relative position of a neighbour of a given cell (x coordinate only).
* Parameters : the index in the list of neighbours of the cell (int).
* Output : x coordinate of relative position (int). */
int index_to_relative_x(int index){
	if((index>0)&&(index<4)){
		return 1;
	}
	if(index>4){
		return -1;
	}
	return 0;
}


/*Gives the relative position of a neighbour of a given cell (y coordinate only).
* Parameters : the index in the list of neighbours of the cell (int).
* Output : y coordinate of relative position (int). */
int index_to_relative_y(int index){
	if((index<6)&&(index>2)){
		return 1;
	}
	if((index==6)||(index==2)){
		return 0;
	}
	return -1;
}


/*Gives the index of the cell as if it was a neighbour of the neighbour cell.
* Parameters : index of the neighbour we want the point of view from (int).
* Output : index of the origin cell as seen from the neighbour (int). */
int change_pov(int index) {
	int list[8] = {4,5,6,7,0,1,2,3};
	return list[index];
}


/*Computes if a particular cell is a neighbour of another one.
* Parameters : pointer to the first cell (cell*), pointer to the second cell (cell*).
* Output : 'true' if the first cell is neighbour of the second one, 'false' if not (bool).
* Calls : is_pos_1_neighbour_pos_2 function. */
bool is_cell_1_neighbour_cell_2(cell* p_cell_1, cell* p_cell_2) {
	pos pos_1 = p_cell_1 -> position;
	pos pos_2 = p_cell_2 -> position;
	return is_pos_1_neighbour_pos_2(pos_1, pos_2);
}


/*Computes if a particular cell is a neighbour of another one.
* Parameters : position of the first cell (pos), position of the second cell (pos).
* Output : 'true' if the first cell is neighbour of the second one, 'false' if not (bool). */
bool is_pos_1_neighbour_pos_2(pos pos_1, pos pos_2) {
	
	int x_1 = pos_1.x;
	int y_1 = pos_1.y;
	int x_2 = pos_2.x;
	int y_2 = pos_2.y;
	
	if((abs(x_1-x_2)<=1) && (abs(y_1-y_2)<=1)) {
		return true;
	}
	else {
		return false;
	}
}


/*Computes if a particular cell is out of bounds with respect to the defined problem.
* Parameters : position of the cell to check (pos), pointer to the defined problem (problem*).
* Output : 'true' if the cell is out of bounds, 'false' if not (bool).*/
bool is_out_of_bounds(pos position, problem* p_game_problem) {
	if(( (position.x >= 0) && (position.x < (p_game_problem->game_size)[0])) && ( (position.y >= 0) && (position.y < (p_game_problem->game_size)[1]))) {
		return false;
	}
	else {
		return true;
	}
}


/*Gives the relative position of a cell comparing another one, only used when they are neighbours.
* Parameters : position of the comparing cell (pos), position of the compared cell (pos).
* Output : The relative position as a neighbour index (int).*/
int relative_pos(pos position_origin_cell, pos position_cell_checked) {
	
	int origin_x = position_origin_cell.x;
	int origin_y = position_origin_cell.y;
	int checked_x = position_cell_checked.x;
	int checked_y = position_cell_checked.y;
	
	int relative_x = checked_x - origin_x;
	int relative_y = checked_y - origin_y;
	
	if (relative_x == 1) {
		return relative_y + 2;
	}
	if (relative_x == -1) {
		return -relative_y + 6;
	}
	//at this point, relative_x = 0
	return (relative_y+1)*2; 
}

//////////////////////////////////////
//       PRINTING FUNCTIONS         //
//////////////////////////////////////


/*Translates a status from a cell to a string.
* Parameters : a pointer to the cell (cell*).
* Output : a string representing the status of the cell (char*). */
char* status_to_string(cell* p_cell_checked) {
	status s = p_cell_checked -> state;
	if (s == NEWBORN){
		return "NEWBORN";
	}
	if (s == ALIVE){
		return "ALIVE";
	}
	else{
		return "DYING";
	}
}


/*Prints the position of a cell and its status.
* Parameters : a pointer to the cell (cell*).
* Calls : status_to_string function. */
void print_cell_pos(cell* p_cell_checked) {

	pos p = p_cell_checked -> position; 
	char* s = status_to_string(p_cell_checked);
	printf("Cell at position (%d,%d), status %s\n", p.x,p.y,s);
}


/*Prints the position and status of the neighbours of a cell.
* Parameters : a pointer to the cell (cell*).
* Calls : print_cell_pos function. */
void print_neighbours_pos(cell* p_cell_checked) {

	pos p = p_cell_checked -> position;
	printf("\nNeighbours of cell at position (%d,%d)\n", p.x,p.y);
	
	for(int i=0; i<8; i++) {
		if (p_cell_checked -> neighbours[i]) {
			printf("\nNeighbour %d:\n",i);
			print_cell_pos(p_cell_checked->neighbours[i]);
		}
	}
	
	printf("\nNo more neighbours\n");
}


/*Prints the number of existing cells (ALIVE, NEWBORN or DYING).
* Parameters : a pointer to the cell list (cell*).*/
void print_existing_cells_number(cell* p_cell_list) {

	int number = 0;
	cell* p_current_cell = p_cell_list;
	
	while(p_current_cell != NULL) {
		number++;
		p_current_cell = p_current_cell -> next_cell;
	}
	
	printf("\n%d alive cells at the moment\n",number);
}


/*Prints the position and status of all existing cells (ALIVE, NEWBORN or DYING).
* Parameters : a pointer to the cell list (cell*).
* Calls : print_cell_pos function.*/
void print_existing_cells_pos(cell* p_cell_list) {
	
	cell* p_current_cell = p_cell_list;
	printf("\nPosition of existing cells\n");
	
	while(p_current_cell != NULL) {
		print_cell_pos(p_current_cell);
		p_current_cell = p_current_cell -> next_cell;
	}
}
		




////////////////////////////////////////////////////////////
//  API FUNCTIONS DOCUMENTED WITH DOXYGEN IN cell.h file  //
////////////////////////////////////////////////////////////


problem* create_game_problem(void) {
	problem* p_game_problem = malloc(sizeof(problem));
	cell* p_cell_list = NULL;
	p_game_problem -> cell_list = p_cell_list;
	return p_game_problem;
}


cell* create_cell(status cell_state, pos cell_position, cell* p_cell_list, problem* p_game_problem) {
	
	if(is_out_of_bounds(cell_position, p_game_problem)) {
	//if cell is out of bounds, cancel the creation.
		return p_cell_list;
	}
	
	//at this point, cell is in bounds.
	
	//allocation of the cell
	cell* p_created_cell = malloc(sizeof(cell));
	
	
	p_created_cell -> state = cell_state; 
	p_created_cell -> position = cell_position; 
	for (int i=0; i<8; i++){
		(p_created_cell -> neighbours)[i] = NULL;
	}
	
	//add the cell in front of the cell list
	p_created_cell -> next_cell = p_cell_list;
	p_cell_list = p_created_cell;
	
	//update neighbours of the created cell and of other cells
	//no need to check if the created cell is a neighbour of itself
	cell* p_current_cell = p_cell_list -> next_cell;
	
	while (p_current_cell != NULL) {
		//if the cell being checked is a neighbour of the created cell
		if (is_cell_1_neighbour_cell_2(p_cell_list,p_current_cell)) {
			pos position_cell_list = p_cell_list -> position;
			pos position_current_cell = p_current_cell -> position;
			int index = relative_pos(position_cell_list,position_current_cell);
			//add the neighbour cell as a neighbour of the created cell
			(p_cell_list->neighbours)[index] = p_current_cell;
			//add the created cell as a neighbour of the neighbour cell
			(p_current_cell->neighbours)[change_pov(index)] = p_cell_list;
		}
		p_current_cell = p_current_cell -> next_cell;
	}
		
	
	return p_cell_list; //p_created_cell becomes p_cell_list
}


void suppress_cell_from_neighbours(cell* p_neighbour_to_delete, cell* p_cell_list) {
	
	cell* p_current_cell = p_cell_list;
	//going through every cell of the list
	while (p_current_cell != NULL) {
		//going through every neighbour
		for(int i=0; i<8; i++) {
			
			if((p_current_cell -> neighbours)[i] == p_neighbour_to_delete) {
				//deletion
				(p_current_cell -> neighbours)[i] = NULL;
			}
		}
		p_current_cell = p_current_cell -> next_cell;
	}
}
		




void suppress_dying_cells(problem* p_game_problem) {
	
	cell* p_cell_list = p_game_problem->cell_list;
	cell* p_current_cell = p_cell_list;
	
	//pointer to the cell following current_cell
	cell* p_next_cell_to_link;
	
	//pointer to the cell preceding current_cell
	//intialization to NULL only useful if the first cell of the list has DYING status
	cell* p_previous_cell_checked = NULL;
	
	while (p_current_cell != NULL) {
	
		if ((p_current_cell -> state) == DYING) {
			
			//updating pointers
			p_next_cell_to_link = p_current_cell -> next_cell;
			
			suppress_cell_from_neighbours(p_current_cell, p_cell_list);
			free(p_current_cell);
			
			//updating pointers
			p_current_cell=p_next_cell_to_link;
			
			if (p_previous_cell_checked == NULL) {
				//only occures when the first cell of the list is being killed
				p_cell_list = p_current_cell;
			}
			else {
				//if the cell being killed is not the first one
				p_previous_cell_checked -> next_cell = p_next_cell_to_link;
			}
		}
		else {
			//updating pointers
			p_previous_cell_checked = p_current_cell;
			p_current_cell = p_current_cell -> next_cell;
		}
	}
	
	p_game_problem->cell_list = p_cell_list;
}

			
void grow_newborn_cells(problem* p_game_problem) {
	
	cell* p_current_cell = p_game_problem->cell_list;
	while (p_current_cell != NULL) {
		if (p_current_cell -> state == NEWBORN) {
			p_current_cell -> state = ALIVE;
		}
		p_current_cell = p_current_cell -> next_cell;
	}
}
			

void murder_cells_in_danger(problem* p_game_problem) {
	//at this point, all cells are alive
	cell* p_current_cell = p_game_problem->cell_list;
	int neighbours_counter;
	while(p_current_cell != NULL) {
		//number of neighbours of the cell being checked
		neighbours_counter = 0;
		for(int i=0; i<8; i++) {
			//neighbours alive or just dying
			if ((p_current_cell->neighbours)[i] != NULL) {
				neighbours_counter++;
			}
		}
		//check if cell follows live rules
		if ((neighbours_counter < (p_game_problem -> live_window)[0]) 
		   || (neighbours_counter > (p_game_problem -> live_window)[1])) {
			p_current_cell -> state = DYING;
		}
		p_current_cell = p_current_cell -> next_cell;
	}
}				

void birth_new_cells(problem* p_game_problem) {
	
	cell* p_cell_list = p_game_problem -> cell_list;
	//cell whose neighbours are being checked for reviving
	cell* p_current_cell = p_cell_list;
	//cells checked for the neighbour count of current_cell neighbour
	cell* p_cells_to_check = p_cell_list;
	
	pos cell_position;
	pos neighbour_position;
	int neighbours_counter;
	while(p_current_cell != NULL){
		
		//condition not useful unless the function is used without next_generation
		if((p_current_cell->state)!=NEWBORN) {
			
			cell_position = p_current_cell->position;
			for(int i=0; i<8; i++) {
				
				if(((p_current_cell->neighbours)[i])==NULL) {
					neighbours_counter=0;
					neighbour_position = index_neighbour_to_position(i, cell_position);
					
					while(p_cells_to_check != NULL){
						//if cells_to_check is alive or dying AND is a neighbour of the neighbour checked for reviving
						if ((((p_cells_to_check->state)==ALIVE)||((p_cells_to_check->state)==DYING))
						&& (is_pos_1_neighbour_pos_2(neighbour_position,p_cells_to_check->position))){
							neighbours_counter++;
						}
						p_cells_to_check = p_cells_to_check -> next_cell;
					}
					//check if cell follows birth rules
					if((neighbours_counter >= (p_game_problem->birth_window)[0]) 
					&& (neighbours_counter <= (p_game_problem->birth_window)[1])){
						p_cell_list=create_cell(NEWBORN,neighbour_position,p_cell_list,p_game_problem);
					}
					p_cells_to_check=p_cell_list;
				}
			}
		}
		p_current_cell = p_current_cell -> next_cell;
	}
	
	p_game_problem -> cell_list = p_cell_list;
}

void next_generation(problem* p_game_problem) {

	suppress_dying_cells(p_game_problem);
	grow_newborn_cells(p_game_problem);
	murder_cells_in_danger(p_game_problem);
	birth_new_cells(p_game_problem);
}

void nuke_everything(problem* p_game_problem){

	cell* p_cell_list = p_game_problem -> cell_list;
	cell* p_next_cell;
	while(p_cell_list != NULL){
		p_next_cell = p_cell_list->next_cell;
		free(p_cell_list);
		p_cell_list=p_next_cell;
	}
	free(p_game_problem);
}
