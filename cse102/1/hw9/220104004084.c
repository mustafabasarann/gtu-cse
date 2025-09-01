#include <stdio.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

	struct Forest {
	char map[MAX_HEIGHT][MAX_WIDTH];
	int width;
	int height;
	int flower_x;
	int flower_y;
	};

	struct Botanist {
	int coord_x;
	int coord_y;
	int water_bottle_size;	
	};
	
	struct Forest forest;
	struct Botanist botanist;
	struct Forest flowers[20];
	
	/* initialize game function */
void init_game(int *flower_count){
	FILE *fp = fopen("init.txt", "r");
	
	fscanf(fp,"%d,%d",&forest.height,&forest.width);
	fscanf(fp,"%d,%d,%d",&botanist.coord_y,&botanist.coord_x,&botanist.water_bottle_size);
	
	char c;
	int i = 0, j = 0;
	
	/* filling flowers and forest.map arrays, counting flowers*/
	while((c = fgetc(fp)) != EOF){
		if(c == '\n'){
			i++;
			j = 0;
			continue;
		}else if(c == ','){
			continue;
		}else{
			if(c == 'X'){
				flowers[*flower_count].flower_x = j;
				flowers[*flower_count].flower_y = i-1;
				(*flower_count)++;
				
			}
			forest.map[i-1][j] = c;
			j++;
		}
	}

	fclose(fp);
}

/* printing forest map */
void display_forest(int collected_flowers){
	int i,j;
	for(i = 0; i< forest.height; i++){
		for(j = 0; j<forest.width; j++){
			if(j == forest.width-1){
				printf("%c",forest.map[i][j]);
			}else{
				printf("%c,",forest.map[i][j]);
			}
			
		}
		printf("\n");
	}
	
	printf("Collected Flowers: %d\n",collected_flowers);
	printf("Remaining Water Bottle: %d\n",botanist.water_bottle_size);
	printf("Botanist_X: %d, Botanist_Y: %d\n",botanist.coord_x,botanist.coord_y);
}

/* check next move coordinate if it is possible to move (checking borders and trees) */
int valid_move_check(int x, int y){
	if((x >= 0 && x < forest.width) && (y >= 0 && y < forest.height)){
		if(forest.map[y][x] != 'T'){
			return 1;
		}
		else{
			printf("You can't go through trees.\n");
			return 0;
		}
	}else{
		printf("You can't cross borders.\n");
		return 0;
	}
}

/* prints last view of game to last.txt file */
void last_view(){
	int i,j;
	FILE *fp = fopen("last.txt", "w");
	
	fprintf(fp,"%d,%d\n",forest.width,forest.height);
	fprintf(fp,"%d,%d,%d\n",botanist.coord_y,botanist.coord_x,botanist.water_bottle_size);
	
	for(i = 0; i<forest.height; i++){
		for(j = 0; j < forest.width; j++){
			if(j == forest.width-1){
				fprintf(fp,"%c",forest.map[i][j]);
			}else{
				fprintf(fp,"%c,",forest.map[i][j]);
			}
		}
		fprintf(fp,"%c",'\n');
	}
	fclose(fp);

	
}

/* gameplay and also move function*/
void search(int *collected_flowers, int flower_count, int *k){
	char move;
	int flag = 0;
	int tempX,tempY;

	/* game end check */
	if(*collected_flowers == flower_count){
		printf("All rare flowers are collected.Game ended.\n");
		last_view();
		return;
	}
	
	if( (*k) == 1){
	printf("PRESS ENTER TO START GAME!\n");
		(*k)++;
	}
	while(getchar() != '\n');
	
	printf("Enter a move( right(r), left(l), up(u), down(d), exit(e) ): ");
	scanf("%c",&move);
	printf("\n");
	
	/* game end check contition for 'e' situation */
	if(move == 'e'){
		printf("Game ended.\n");
		display_forest(*collected_flowers);
		last_view();
		return;
	}
	
	tempX = botanist.coord_x;
	tempY = botanist.coord_y;
	

	/* move the botanist if it is possible change botanist's cooridantes*/
	switch(move){
		case 'r':
		if(valid_move_check(botanist.coord_x +1,botanist.coord_y)){
			botanist.coord_x += 1;
			flag = 1;
		}
		break;
		case 'l':
		if(valid_move_check(botanist.coord_x -1,botanist.coord_y)){
			botanist.coord_x -= 1;
			flag = 1;
		}
		break;
		case 'u':
		if(valid_move_check(botanist.coord_x, botanist.coord_y - 1)){
			botanist.coord_y -= 1;
			flag = 1;
		}
		break;
		case 'd':
		if(valid_move_check(botanist.coord_x , botanist.coord_y + 1)){
			botanist.coord_y += 1;
			flag = 1;
		}
		break;
		default:
		printf("Invalid move\n");  
		break;
	}
	
	/* check if  botanist collected a flower */
	if(forest.map[botanist.coord_y][botanist.coord_x] == 'X'){
		(*collected_flowers)++;
		botanist.water_bottle_size--;
		}
		
		/* move the botanist change him/her location*/
	if(flag){
		forest.map[tempY][tempX] = ' ';
		forest.map[botanist.coord_y][botanist.coord_x] = 'B';	
		}
	display_forest(*collected_flowers);
	search(collected_flowers, flower_count, k);
}
int main(){
	int k = 1;
	int collected_flowers = 0;
	int flower_count = 0;
	init_game(&flower_count);
	display_forest(collected_flowers);
	search(&collected_flowers, flower_count, &k);
}
