#include <stdio.h>
int main(){
int choice;
           	printf("MENU: \n"); /* MENU */
           	printf("1-) ***** EXPLORE DATA *****\n");
           	printf("2-) ***** TRAIN MODEL ******\n");
           	printf("3-) ***** TEST MODEL *****\n");
           	printf("4-) ***** EXIT *****\n");
           	printf("Enter Operation: ");
		scanf("%d",&choice);
	while(choice != 4){
	
	
    int X, Y, C;
    int x0_max, y0_max;
    int x1_max, y1_max;
                             /*Finding max values */
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    fscanf(file, "%d %d %d", &x1_max, &y1_max, &C);
    fscanf(file, "%d %d %d", &x0_max, &y0_max, &C);

    while (fscanf(file, "%d %d %d", &X, &Y, &C) != EOF) {
        if (C == 1) {
            if (X > x1_max) x1_max = X;
            if (Y > y1_max) y1_max = Y;
        }
        if (C == 0) {
            if (X > x0_max) x0_max = X;
            if (Y > y0_max) y0_max = Y;
        }
    }
    fclose(file);

    int x0_min, y0_min;
    int x1_min, y1_min;
                         /*Finding min values */
    FILE *file2 = fopen("data.txt", "r");
    if (file2 == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    fscanf(file2, "%d %d %d", &x1_min, &y1_min, &C);
    fscanf(file2, "%d %d %d", &x0_min, &y0_min, &C);

    while (fscanf(file2, "%d %d %d", &X, &Y, &C) != EOF) {
        if (C == 1) {
            if (X < x1_min) x1_min = X;
            if (Y < y1_min) y1_min = Y;
        }
        if (C == 0) {
            if (X < x0_min) x0_min = X;
            if (Y < y0_min) y0_min = Y;
        }
    }
        int xMin, xMax, yMin, yMax;
                  /*Finding absolute max and min values */
    if (x0_min < x1_min) {
        xMin = x0_min;
    } else {
        xMin = x1_min;
    }
    if (x0_max > x1_max) {
        xMax = x0_max;
    } else {
        xMax = x1_max;
    }
    if (y0_min < y1_min) {
        yMin = y0_min;
    } else {
        yMin = y1_min;
    }
    if (y0_max > y1_max) {
        yMax = y0_max;
    } else {
        yMax = y1_max;
    }


    fclose(file2);
    
    int i,k;
    int errorcount = 0, r1_0counter = 0, r1_1counter = 0, r2_0counter = 0, r2_1counter = 0, r3_0counter = 0, r3_1counter = 0, r4_0counter = 0, r4_1counter = 0;
    int R1, R2, R3, R4;
    int min_error, bestx, besty, bestR1, bestR2, bestR3, bestR4;
    for (i = xMin; i <= xMax; i++) {             /*  finding best separator  */
        for (k = yMin; k <= yMax; k++) {
            FILE *file3 = fopen("data.txt", "r");
            if (file3 == NULL) {
                printf("Error opening the file");
                return 1;
            }
            while (fscanf(file3, "%d %d %d", &X, &Y, &C) != EOF) {
                if (X <= i && Y > k) {
                    if (C == 0) {
                        r1_0counter++;
                    } else {
                        r1_1counter++;
                    }
                }
                if (X > i && Y > k) {
                    if (C == 0) {
                        r2_0counter++;
                    } else {
                      r2_1counter++;		
                    }
                }
                if (X <= i && Y <= k) {
                    if (C == 0) {
                        r3_0counter++;
                    } else {
                        r3_1counter++;
                    }
                }
                if (X > i && Y <= k) {
                    if (C == 0) {
                        r4_0counter++;
                    } else {
                        r4_1counter++;
                    }
                }
            }
            fclose(file3);       /* Assigning labels to regions and counting errors*/
            if (r1_0counter > r1_1counter) {
                R1 = 0;
                errorcount += r1_1counter;
            } else {
                R1 = 1;
                errorcount += r1_0counter;
            }
            if (r2_0counter > r2_1counter) {
                R2 = 0;
                errorcount += r2_1counter;
            } else {
                R2 = 1;
                errorcount += r2_0counter;
            }
            if (r3_0counter > r3_1counter) {
                R3 = 0;
                errorcount += r3_1counter;
            } else {
                R3 = 1;
                errorcount += r3_0counter;
            }
            if (r4_0counter > r4_1counter) {
                R4 = 0;
                errorcount += r4_1counter;
            } else {
                R4 = 1;
                errorcount += r4_0counter;
            }
            if (i == xMin && k == yMin) {
                min_error = errorcount;
            }                                 /* finding best case */
            if (errorcount < min_error) {
                min_error = errorcount;
                bestx = i;
                besty = k;
                bestR1 = R1;
                bestR2 = R2;
                bestR3 = R3;
                bestR4 = R4;
            }          /* reset counters */
            errorcount = 0;
            r1_0counter = 0;
            r1_1counter = 0;
            r2_0counter = 0;
            r2_1counter = 0;
            r3_0counter = 0;
            r3_1counter = 0;
            r4_0counter = 0;
            r4_1counter = 0;
        }
    }

	        
           	switch (choice){    /* switch case for creating menu*/
           		case 1:
           		    printf("Minimum and Maximum X and Y values:\n");
			    printf("Class 0: X in [%d %d], Y in [%d %d]\n", x0_min, x0_max, y0_min, y0_max);
			    printf("Class 1: X in [%d %d], Y in [%d %d]\n", x1_min, x1_max, y1_min, y1_max);
			    break;
           		case 2:
           		    printf("xMin: %d, xMax: %d\nyMin: %d, yMax: %d\n", xMin, xMax, yMin, yMax);
           		    printf("Separator coordinates: X= %d, Y=%d\n", bestx, besty);
		            printf("Training error of the model= %d\n", min_error);
			   printf("Labels of the regions: R1 = %d, R2 = %d, R3 = %d, R4 = %d\n", bestR1, bestR2, bestR3, bestR4);
				break;
			case 3:
			    FILE *file4 = fopen("test 1.txt","r");
			    if(file4 == NULL){
			    	printf("Error opening the file");
					return 1;
			    }
			    		float coordinateCount;
			    		int R;
			    		float succesCount;
			   		
			    while (fscanf(file4, "%d %d %d", &X, &Y, &C) != EOF) {
			   
					coordinateCount++;      /* assigning coordinates new labels and checking if they true*/
					if (X <= bestx && Y > besty) {
					    	R = bestR1;
					}
					if (X > bestx && Y > besty) {
					    	R=bestR2;
					}
					if (X <= bestx && Y <= besty) {
					    R = bestR3;
					}
					if (X > bestx && Y <= besty) {
					    R = bestR4;
					}
					if(R == C ){
						succesCount++;
					}
					printf("X: %d, Y: %d label: %d, predicted label: %d\n",X,Y,C,R);
				    }	
				    	float succes;
			    		succes = (succesCount/coordinateCount);     /* Calculating succes rate */
			    		printf("Truly predicted %.0f in %.0f.\n",succesCount,coordinateCount);
				    	printf("Succes Rate: %%%.2f\n", succes * 100);
          				  fclose(file4);
          				  printf("\n         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%     \n\n");
          				  FILE *file5 = fopen("test-final.txt","r");
			    if(file5 == NULL){
			    	printf("Error opening the file.");
			    	}	
			    
			    	while (fscanf(file5, "%d %d", &X, &Y) != EOF)     /* Assigning labels to coordinates */
			    	{
			    		if (X <= bestx && Y > besty) {
				    	R = bestR1;
					}
					if (X > bestx && Y > besty) {
					    	R=bestR2;
					}
					if (X <= bestx && Y <= besty) {
					    R = bestR3;
					}
					if (X > bestx && Y <= besty) {
					    R = bestR4;
					}
					printf("X: %d, Y: %d, Class: %d\n",X,Y,R);
					}
					fclose(file5);
           				break;

   		
           		default:
           		printf("Invalid option...");
           		break;
           		
           		
           	}        /* Menu for while loop */
           	printf("-------------------------------------------------------\n");
           	printf("MENU: \n");
           	printf("1-) ***** EXPLORE DATA *****\n");
           	printf("2-) ***** TRAIN MODEL ******\n");
           	printf("3-) ***** TEST MODEL *****\n");
           	printf("4-) ***** EXIT *****\n");
           	printf("Enter Operation: ");
           	
           	scanf("%d",&choice);   
            }
            if(choice == 4){ /* exit operation*/
            	printf("Exiting...\n");
            }
          }
            
    
    		
    	
    
    
