#include <stdio.h>
#include <stdlib.h>
#include "cell.c"
#include "load.c"
#include "generate-image.c"

int main(void){

	char file_path[100];
	char rule_flag[1];
	int int1;
	int int2;
	
	//user input data file path
	printf("Enter data path: ");
	scanf("%s",file_path);
	
	//loading the problem from the data file
	problem* p_game_problem = load_grid(file_path);
	printf("Grid loaded\n");
	
	//user input rules
	printf("Keep default birth/live rules ? (y/n) ");
	scanf("%s",rule_flag);
	
	if (rule_flag[0] == 'N' || rule_flag[0] == 'n') {
		printf("Enter new birth rules (minimum/maximum number of neighbours required)\n (two integers separated by a space): ");
		scanf("%d %d",&int1,&int2);
		(p_game_problem->birth_window)[0]=int1;
		(p_game_problem->birth_window)[1]=int2;
		printf("Enter new live rules (minimum/maximum number of neighbours required)\n (two integers separated by a space): ");
		scanf("%d %d",&int1,&int2);
		(p_game_problem->live_window)[0]=int1;
		(p_game_problem->live_window)[1]=int2;
	}
	else {
		(p_game_problem->birth_window)[0]=3;
		(p_game_problem->birth_window)[1]=3;
		(p_game_problem->live_window)[0]=2;
		(p_game_problem->live_window)[1]=3;
	}
	
	//generating frames for each iteration of the problem
	generate_image(p_game_problem);
	printf("Animation generated\n");
	
	//memory deallocation
	nuke_everything(p_game_problem);
	printf("Memory deallocated! Bye Conway!\n");
	
	return 0;
}

