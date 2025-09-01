#include <stdio.h>
#include <string.h>

#define MAX_ROW_COUNT 100
#define MAX_COL_COUNT 100 

void search_p1(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches){
	char pattern[] = "***++++***++++***";
	int length = strlen(pattern);
	*num_matches = 0;
	int row_index;
	
	for(row_index = 0; row_index < num_rows; row_index++){
		char *row = strs[row_index];
		int col_index = 0;
		while(col_index <= strlen(row) - length){
			if(strncmp(row + col_index, pattern, length) == 0){
				matches[*num_matches][0] = row_index+1;
				matches[*num_matches][1] = col_index+1;
				(*num_matches)++;
			}
			col_index++;
		}
	}
}

void search_p2(char strs[][MAX_COL_COUNT], int num_rows,
int matches[][2], int * num_matches){
	char pattern[] = "+*+*+";
	int length = strlen(pattern);
	*num_matches = 0;
	int col_index,row_index,i;
	
	for(col_index = 0; col_index <= strlen(strs[0]) - length; col_index++){
  		for(row_index = 0; row_index <= num_rows - length; row_index++){
		int match = 1;
		for(i=0; i < length; i++){
		    if(strs[row_index + i][col_index] != pattern[i]){
		        match = 0;
		        break;
		    }
		}
        
        if(match) {
            matches[*num_matches][0] = row_index+1;
            matches[*num_matches][1] = col_index+1;
            (*num_matches)++;
        		}   
    		}
	}
}


void search_p3(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches){
	char pattern[] = "+**+++****+++**+";
	int length = strlen(pattern);
	int col_index,row_index,i;
	*num_matches = 0;
	
	for(row_index = 0; row_index <= num_rows - length; row_index++){
		for(col_index = 0; col_index <= strlen(strs[0]); col_index++){
			int match = 1;
			for(i = 0; i<length; i++){
				if(strs[row_index + i][col_index + i] != pattern[i]){
					match = 0;
					break;
				}
			}
			
			if(match){
				matches[*num_matches][0] = row_index+1;
				matches[*num_matches][1] = col_index+1;
				(*num_matches)++;
			}
		}
	}
}


void read_file(char filename[], char strs[][MAX_COL_COUNT], int *num_rows){
	FILE *fp = fopen(filename,"r");
	
	if(fp == NULL){
		printf("Error opening file %s\n",filename);
		return;
	}
	
	*num_rows = 0;
	while(fgets(strs[*num_rows], MAX_COL_COUNT, fp) != NULL){
		(*num_rows)++;
	}
	fclose(fp);
}

int main(){
	char filename[] = "input2.txt";
	char strs[MAX_ROW_COUNT][MAX_COL_COUNT];
	int num_rows;
	int matches[MAX_ROW_COUNT][2];
	int num_matches;
	
	read_file(filename,strs,&num_rows);
	search_p1(strs, num_rows,matches, &num_matches);
	
	int i;
	    for (i = 0; i < num_matches; i++) {
        printf("P1 @ (%d,%d)\n", matches[i][0], matches[i][1]);
    }

	
	search_p2(strs, num_rows, matches, &num_matches);	
	    for (i = 0; i < num_matches; i++) {
        printf("P2 @ (%d,%d)\n", matches[i][0], matches[i][1]);
        }
        
        
        search_p3(strs, num_rows, matches, &num_matches);
	    for (i = 0; i < num_matches; i++) {
        printf("P3 @ (%d,%d)\n", matches[i][0], matches[i][1]);
	    } 
	} 



