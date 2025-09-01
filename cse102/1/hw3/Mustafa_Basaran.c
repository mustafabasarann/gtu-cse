#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[256];
int student_position;
int total_ects;
int total_move;
int i, k, counter = 0;
int wall1[16],wall2[32];
int game_check = 1;

void initialize_game() {
    /* Create empty spaces */
    for (i = 0; i < 256; i++) {
        board[i] = '.';
    }
    /* Place student at the center */
    student_position = 128 + 8;
    board[student_position] = 'P';
    board[255] = 'X';
    
    
        /* Place first wall and keep it in an array. */

    int w1 = 0;
    for (i = 1; i <= 16; i++) {
        for (k = 1; k <= 16; k++) {
            counter++;
            if ((i >= 7 && i <= 11) && (k >= 7 && k <= 11) && ((i == 7 || i == 11) || (k == 7 || k == 11))) {
                board[counter - 1] = '#';
                wall1[w1] = counter-1;
                w1++;
            }
        }
    }
    counter = 0;
    
    /* Place second wall and keep it in an array. */

    int w2=0;
    for (i = 1; i <= 16; i++) {
        for (k = 1; k <= 16; k++) {
            counter++;
            if ((i >= 5 && i <= 13) && (k >= 5 && k <= 13) && ((i == 5 || i == 13) || (k == 5 || k == 13))) {
                board[counter - 1] = '#';
                wall2[w2] = counter-1;
                w2++;
            }
        }
    }
    counter = 0;

    /* Place '1' courses randomly */
    srand(time(NULL));
    int random_array[8];
    int z = 0;
    int randomIndex, courses_placed = 0;
    for (i = 1; i <= 16; i++) {
        for (k = 1; k <= 16; k++) {
            counter++;
            if ((i >= 8 && i <= 10) && (k >= 8 && k <= 10) && ((i == 8 || i == 10) || (k == 8 || k == 10))) {
                random_array[z] = counter;
                z++;
            }
        }
    }
    counter = 0;
    while (courses_placed != 4) {
        randomIndex = rand() % 8;
        if (board[random_array[randomIndex] - 1] != '1') {
            board[random_array[randomIndex] - 1] = '1';
            courses_placed++;
        }
    }
    /*Place '2' courses randomly */
    int random_array2[24];
    int m = 0;
    int randomIndex2, courses_placed2 = 0;
    for (i = 1; i <= 16; i++) {
        for (k = 1; k <= 16; k++) {
            counter++;
            if ((i >= 6 && i <= 12) && (k >= 6 && k <= 12) && ((i == 6 || i == 12) || (k == 6 || k == 12))) {
                random_array2[m] = counter;
                m++;
            }
        }
    }
    counter = 0;
    while (courses_placed2 != 3) {
        randomIndex2 = rand() % 24;
        if (board[random_array2[randomIndex2] - 1] != '2') {
            board[random_array2[randomIndex2] - 1] = '2';
            courses_placed2++;
        }
    }
}

void print_board() {
    int i, j, counter = -1;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            counter++;
            printf("%c ", board[counter]);
        }
        printf("\n");
    }

}

void move_player(char direction) {
int new_position = student_position;

    switch (direction) {
        case 'w':
            new_position -= 16;
            break;
        case 's':
            new_position += 16;
            break;
        case 'a':
            new_position -= 1;
            break;
        case 'd':
            new_position += 1;
            break;
        default:
            printf("Invalid move!\n");
            return;
    }
    total_move++;
     
     /* check state of the game */
    if(board[new_position] == 'X'){
    	printf("Congratulations!\n");
	game_check = 0;
    	}
    	
    	/* check the student if it is out of the bound of the board */
    if(new_position < 0 || new_position >= 256){
    	printf("YOU SHALL NOT PASS!!\n");
    	new_position=student_position;
    }
    
              /* collecting first grade courses and wall1 check */
    if(total_ects < 32){
        if(board[new_position] == '1') total_ects += 8;
   	
    	if(board[new_position] == '#'){
    		printf("Collect all the first grade courses!\n");
    		new_position=student_position;
    		
    	}else{
    	    /* Move the player */
    board[student_position] = '.';
    student_position = new_position;
    board[student_position] = 'P';
    }
    }
    
        /* deactivate the wall1  */
    if(total_ects >=32 && total_ects<56){
    	for(i = 0; i<16; i++){
    		if(new_position == wall1[i]){
   		if(direction == 'w') new_position -=16;
   		if(direction == 's') new_position +=16;
   		if(direction == 'a') new_position -=1; 		
 		if(direction == 'd') new_position +=1;
   
   }   	
  }        
           /* collect second courses and wall2 check */
          if(board[new_position] == '2') total_ects += 8;
   	
    	if(board[new_position] == '#'){
    		printf("Collect all the second grade courses!\n");
    		new_position=student_position;
    		
    	}else{
    	    /* Move the player */
    board[student_position] = '.';
    student_position = new_position;
    board[student_position] = 'P';
    }
     
   }
                  /* deactivate wall1 and wall2  */
       if(total_ects == 56){
           	for(i = 0; i<16; i++){
    		if(new_position == wall1[i]){
   		if(direction == 'w') new_position -=16;
   		if(direction == 's') new_position +=16;
   		if(direction == 'a') new_position -=1; 		
 		if(direction == 'd') new_position +=1;
   
   }   	
  }
    	    	for(i = 0; i<32; i++){
    		if(new_position == wall2[i]){
	   		if(direction == 'w') new_position -=16;
	   		if(direction == 's') new_position +=16;
	   		if(direction == 'a') new_position -=1; 		
	 		if(direction == 'd') new_position +=1;
 		}}
			 /* Move the player */
			    board[student_position] = '.';
			    student_position = new_position;
			    board[student_position] = 'P'; 		
 		
 		}
 		  	
  }
    

int main() {
    char direction;
    initialize_game();
    print_board();
    
             /* game loop */
    while (game_check) {
        printf("Use W (Up), A (Left), S (Down), D (Right) to move.\n: ");
        scanf(" %c", &direction);
        move_player(direction);
        printf("Total ECTS: %d\n",total_ects); 
        printf("Total Movements: %d\n ",total_move);
        print_board();
    }

    return 0;
} 

