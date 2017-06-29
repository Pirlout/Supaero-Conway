#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include "../include/generate-image.h"

/* Brief : converts an int into its number of digits
*  Parameters : steps_number integer to convert
*  Return : the number of digits of the parameter (int) */
int number_digits_from_int(int steps_number) {
	if(steps_number==0){
		return 1;
	}
	else {
		return((floor(log10(steps_number)))+1);
	}
}


void generate_frame(problem* p_game_problem, int game_size_x, int game_size_y, char* file_path) {
	//ALIVE = 51 153 255 blue
	//NEWBORN = 51 255 51 green
	//DYING = 255 51 51 red
	//DEAD = 255 255 255 white
	
	FILE* p_file = NULL;
	p_file=fopen(file_path, "w+");
	
	int x_cell;
	int y_cell;
	
	if (p_file != NULL){
		
		//Writing first lines of the PPM file
		fprintf(p_file,"P3\n");
		fprintf(p_file,"%d %d\n",game_size_x,game_size_y);
		fprintf(p_file,"255\n");
		
		//number of characters at the start of the file
		int offset_start = ftell(p_file);
		int offset_pos;
		
		//Coloring the grid white
		for(int y=0; y<game_size_y; y++){
			for(int x=0; x<game_size_x; x++){
				fprintf(p_file,"255 255 255 ");
			}
			fprintf(p_file,"\n");
		}
		
		
		//Adding cells to the grid
		cell* p_current_cell = p_game_problem -> cell_list;
		while(p_current_cell != NULL){
			
			x_cell=(p_current_cell->position).x;
			y_cell=(p_current_cell->position).y;
			
			//set writing cursor to cell position
			rewind(p_file);
			fseek(p_file,offset_start,SEEK_CUR);
			offset_pos=y_cell*(12*game_size_x + 1) + 12*x_cell;
			fseek(p_file,offset_pos,SEEK_CUR);
			
			//rewrite pixel
			if ((p_current_cell->state)==ALIVE){
				fprintf(p_file,"051 153 255 ");
			}
			if ((p_current_cell->state)==NEWBORN){
				fprintf(p_file,"051 255 051 ");
			}
			if ((p_current_cell->state)==DYING){
				fprintf(p_file,"255 051 051 ");
			}
			
			p_current_cell = p_current_cell -> next_cell;

		}
	}
	
	else {
		error(1, 0, "Cannot read file %s!\n", file_path); 
	}
	
	fclose(p_file);
}

void generate_image(problem* p_game_problem){

	int iterations_to_do = p_game_problem -> steps_number;
	//game size is calculated now to optimize code
	int game_size_x=(p_game_problem->game_size)[0];
	int game_size_y=(p_game_problem->game_size)[1];
	int number_digits_iterations = number_digits_from_int(iterations_to_do);
	
	//
	//Generation of first frame (iteration 0)
	//
	
	//we suppose no one would try to produce a GIF with more than 10 power 100 frames
	//it would be more frames than there are atoms in the universe
	char file_path[115]="./out/frame";
	char string_frame_number[100];
	
	sprintf(string_frame_number,"%0*d",number_digits_iterations,0);
	strcat(file_path,string_frame_number);
	strcat(file_path,".ppm");
	
	generate_frame(p_game_problem,game_size_x,game_size_y,file_path);
	
	//
	//Generation of next frames
	//
	
	for(int frame_number=1;frame_number<iterations_to_do+1;frame_number++){
		
		//reinitialization of file_path
		sprintf(file_path,"./out/frame");
		sprintf(string_frame_number,"%0*d",number_digits_iterations,frame_number);
		
		strcat(file_path,string_frame_number);
		
		strcat(file_path,".ppm");
		
		next_generation(p_game_problem);
		
		generate_frame(p_game_problem, game_size_x, game_size_y, file_path);
	}
}
