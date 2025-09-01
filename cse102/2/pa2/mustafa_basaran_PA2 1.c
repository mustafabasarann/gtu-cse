#include <stdio.h>

#define X 2 // segment size
#define Y 13 // memory size

int main(){

	FILE* input = fopen("input.txt", "r");
	
	int memory[Y][X];             
	int num,i,j;
	int segment[X];
	int memory_counter[Y];
	int total_segments = 0;
	
	// counter for each memory element
	for(i = 0; i<Y; i++){
		memory_counter[i] = 0;
	}
	
	// getting first X numbers to memory
	for(i = 0; i < X && fscanf(input, "%d", &num) != EOF; i++){
		segment[i] = num;
	}
	
	// main loop lasts until EOF
	while(fscanf(input,"%d",&num) != EOF){
		//sliding elements 
		for(i=1; i<X; i++){
			segment[i-1] = segment[i];
		}
		segment[X-1] = num;
		
		int is_new_segment = 1;
		for(i = 0; i<total_segments; i++){
			int is_exist = 1;
			
			// checking if new element exists already
			for(j=0; j<X; j++){
				if(memory[i][j] != segment[j]){
				is_exist = 0;
				break;
				}
			}
			
			// if exists increase counter for element
			if(is_exist){
				memory_counter[i]++;
				is_new_segment = 0;
				break;
			}
			}
			// if it is a new element adding to memory and erasing the first one and sliding elements 
			if(is_new_segment){
				if(total_segments < Y) {
				for(j = 0; j<X; j++){
				memory[total_segments][j]  = segment[j];
				}
				memory_counter[total_segments] = 1;
				total_segments++;
				}else {
				for (i= 0; i<Y-1; i++){
					for(j= 0; j<X; j++){
						memory[i][j] = memory[i+1][j];
					}
					memory_counter[i] = memory_counter[i+1];
				}
				for(j = 0; j<X; j++){
					memory[Y-1][j] = segment[j];
				}
				memory_counter[Y-1] = 1;
				}
			}
		}
		fclose(input);
		
		// writing results to output file
		FILE* output = fopen("output.txt", "w");
		
		for(i=0; i<total_segments; i++){
			for(j=0; j<X; j++){
				fprintf(output,"%d ",memory[i][j]);
			}
			fprintf(output, ": %d\n", memory_counter[i]);
		}
		fclose(output);
}

