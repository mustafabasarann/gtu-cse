#include <stdio.h>

/* fill the board with stones*/
void initializeGame(int board[][7],int n){
	int i,j;
	board[0][6] = 0;
	board[1][6] = 0;
	for(i=0; i<2; i++){
		for(j = 0; j<6; j++){
			board[i][j] = n;
		}
	}
}

/* prints board */
void printBoard(int board[][7]){
	 int j;
    
	printf("+----+---+---+---+---+---+---+----+\n");
    
   
        for (j = 6; j >= 0; j--) {
            
            if (j == 6) printf("|    |");
            
            
            if (j >= 0 && j <= 5) {
                printf("%2d |", board[0][j]);
     	 		}
               	}
               	printf("    |\n");
               	printf("| ");
            	printf("%2d |",board[0][6]);
            	printf("---+---+---+---+---+---|");
            	printf(" %2d |\n",board[1][6]);
		
        for (j = 0; j < 7; j++) {
            
            if (j == 0) printf("|    |");
            
            
            if (j >= 0 && j <= 5) {
                printf("%2d |", board[1][j]);
     	 		}
               	}
               	printf("    |");
               	printf("\n");
               	
	printf("+----+---+---+---+---+---+---+----+\n");
 }

/* move function for player */
void move(int cup,int board[][7],int who){
	int stones,i;
	int playing_who = who;
	
	stones = board[who][cup-1];
	board[who][cup-1] = 0;
	
	for(i=1; i <= stones; i++){
		if( cup-1+i == 7){
			cup -= 7;
			who = (who == 0) ? 1 : 0; 
		}
		if((playing_who != who) && cup-1+i == 6){
			stones++;
			who = (who == 0) ? 1 : 0;
			continue;
		}
		
		board[who][cup-1+i] += 1;
	}
}

/* move function for computer*/
void moveComputer(int board[][7],int cup){
	int i;
	
	for(i = 0; i < 6; i++){
		if(board[0][i] != 0){
			cup = i+1;
			move(cup,board,0);
		}
	}
}

/* gameplay function */
 int gamePlay(int board[][7]){
 	int flag = 1,cup,check = 1;
 	int current_player = 1;   /* 0 computer, 1 me */
 	int n; 
 	
 	/*input error check */
 	while(flag){
 		if(current_player == 1){
 		printf("Select a cup.(1 to 6): ");
 		scanf("%d",&cup);
 	}
 	
 	while(!(cup >= 1 && cup <= 6)){
 		printf("\nInvalid cup.Select a cup 1 to 6: ");
 		scanf("%d",&cup);
 		printf("\n");
 		}
 	while(board[current_player][cup-1] == 0){
 		printf("That cup is empty.Select another.\n");
 		scanf("%d",&cup);
 	}
 	
 	n = board[current_player][cup-1];
 	
 	move(cup,board,current_player);
 	printBoard(board);
 	
	if(gameEndCheck(board,current_player) == 0){
		return current_player;
	}
	
	/* after distribution if last cup is not empty keep distributing  */
	while((lastCupStones(board,current_player,cup,n) != 1) && !largeCupCheck(cup,n)){
		if( (cup + n) > 7){
			current_player = (current_player == 0) ? 1 : 0;
			cup = (cup+n) % 7;
		}else{
			cup = cup + n;
		}
		move(cup,board,current_player);
		printBoard(board);
	}
	
	/*if last cup empty change turn */
	while(lastCupStones(board,current_player,cup,n) == 1){
		current_player = (current_player == 0) ? 1 : 0;
	}
	
	/*if last cup is large cup move one more */
	while(largeCupCheck(cup,n) == 1){
		if(current_player == 1){
			printf("Select a cup.(1 to 6): ");
	 		scanf("%d",&cup);
			move(cup,board,current_player);
			printBoard(board);
		}else if(current_player == 0){
			moveComputer(board,cup);
			printBoard(board);
			}
		}
 	}
 
 } 
 /* if one side of board is empty end game*/
int gameEndCheck(int board[][7],int who){
	int sum = 0;
	int i;
	for(i = 0; i<6; i++){
		sum += board[who][i];
	}
	return sum;
}

/* amount of stones of lastcup*/
int lastCupStones(int board[][7],int who,int cup,int n){
	int x;
	
	if((cup+n) > 7){
		x = (cup+n) % 7;
		who = (who == 0) ? 1 : 0;
		return board[who][x-1];
	}else{
		return board[who][cup-1+n];
	}
}

/* check if last cup is large cup */
int largeCupCheck(int cup,int n){
	if((cup+n) == 7 || (cup+n) == 14){
		return 1;
	}else{
		return 0;
	}
}

/* main function */
int main() {
	int board[2][7];
	
	initializeGame(board,4);
	printBoard(board);
	
	if(gamePlay(board) == 0)
	{
		printf("Winner: Computer!\n");
	}else if(gamePlay(board) == 1){
		printf("Winner: Player!\n");
	}
}




