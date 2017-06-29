#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/load.h"

problem* load_grid(const char* file_path) {
	
	FILE* p_file = NULL;
	p_file=fopen(file_path,"r");
	
	if (p_file==NULL) {
		error(1, 0,"Cannot read file !\n");
	}
	
	problem* p_game_problem = create_game_problem();
	
	int game_size_x;
	int game_size_y;
	int fscanf_result = 0;
	
	//
	//initialization of the game problem size
	//
	fscanf_result=fscanf(p_file, "%d %d", &game_size_x, &game_size_y);
	
	if (fscanf_result != 2) {
		error(1, 0,"Line number 1 is not syntactically correct!\n");
	}
	
	(p_game_problem -> game_size)[0] = game_size_x;
	(p_game_problem -> game_size)[1] = game_size_y;
	
	//
	//intialization of the problem's steps number
	//
	int steps_number;
	
	fscanf_result=fscanf(p_file, "%d", &steps_number);
	
	if (fscanf_result != 1) {
		error(1, 0,"Line number 2 is not syntactically correct!\n");
	}
	
	p_game_problem -> steps_number = steps_number;
	
	//
	//adding the cells to the cell list
	//
	cell* p_cell_list = p_game_problem -> cell_list;
	pos cell_position;
	
	//list of characters representing a line of the grid
	//size game_size_x + 1 so that it stores end of line character
	char chars_line[game_size_x+1];
	//initialization required to avoid valgrind error
	for(int i=0; i<game_size_x+1; i++){
		chars_line[i]='.';
	}
	
	//explore the grid line by line
	for(int y_coordinate=-1; y_coordinate<game_size_y; y_coordinate++){
		
		//saves in chars_line the characters of the line being explored
		//read game_size_x+2 so that end of line character is read
		fgets(chars_line,game_size_x+2,p_file);
		
		for(int x_coordinate=0; x_coordinate<game_size_x; x_coordinate++){
			
			if(chars_line[x_coordinate]=='o'){
				
				cell_position.x=x_coordinate;
				cell_position.y=y_coordinate;
				
				p_cell_list = create_cell(ALIVE,cell_position,p_cell_list,p_game_problem);
			}
			
		}
	}
	
	p_game_problem -> cell_list = p_cell_list;
	
	fclose(p_file);
	
	return p_game_problem;
}


