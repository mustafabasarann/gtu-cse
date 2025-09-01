#include <stdio.h>
char first_initial(FILE *id_fp, int id) {
	char initial;
	fseek(id_fp, 0, SEEK_SET);
	int current_id;
	char c;
	while (fscanf(id_fp, "%d", &current_id) == 1) {
		if (current_id == id) {
			while ((c = fgetc(id_fp)) != EOF && c != ';') {} 
		        fscanf(id_fp,"%c",&c);
		        initial = c;
		        break;
		}else{
			while ((c = fgetc(id_fp)) != EOF && c != '\n') {} 
		    }
		}
	return initial;
}

char last_initial(FILE * id_fp, int id){
	char initial;
	fseek(id_fp,0,SEEK_SET);
	int current_id;
	char c;
	
	while(fscanf(id_fp,"%d",&current_id) == 1){
		if(current_id == id){
			while(fscanf(id_fp,"%c",&c) != EOF && c != ';'){}
			while(fscanf(id_fp,"%c",&c) != EOF && c != ';'){}
			fscanf(id_fp,"%c",&c);
			initial = c;
		}else{
			while(fscanf(id_fp,"%c",&c) != EOF && c != '\n'){}
		}
	}
		return initial;
}



int get_id_fi(FILE *id_fp, char first_initial) {
    int id = 0;
    int current_id;
    char c;

    fseek(id_fp, 0, SEEK_SET);

    while ((c = fgetc(id_fp)) != EOF) {
        ungetc(c, id_fp);
        fscanf(id_fp, "%d", &current_id);
        while ((c = fgetc(id_fp)) != EOF && c != ';') {}
        fscanf(id_fp, " %c", &c);
        if (c == first_initial) {
            if (id != 0) {
                printf(", ");
            }
            printf("%d", current_id);
            id = current_id;
        } else {
            while ((c = fgetc(id_fp)) != EOF && c != '\n') {}
        }
    }
    
    printf("\n");

    return id;
}



int get_id_li(FILE * id_fp, char last_initial){
    int id = 0;
    int current_id;
    char c;

    fseek(id_fp, 0, SEEK_SET);

    while ((c = fgetc(id_fp)) != EOF) {
        ungetc(c, id_fp);
        fscanf(id_fp, "%d", &current_id);
        while ((c = fgetc(id_fp)) != EOF && c != ';') {}
        while ((c = fgetc(id_fp)) != EOF && c != ';') {}
        fscanf(id_fp, " %c", &c);
        if (c == last_initial) {
            if (id != 0) {
                printf(", ");
            }
            printf("%d", current_id);
            id = current_id;
        } else {
            while ((c = fgetc(id_fp)) != EOF && c != '\n') {}
        }
    }
    
    printf("\n");

    return;
}

int average_grade(FILE * info_fp, int id){
	fseek(info_fp, 0, SEEK_SET);
	int current_id,mid1,mid2,final,class;
	float gpa= -1.0,mid_avg102= 0.0,final_avg102= 0.0,mid_avg108=0.0,final_avg108=0.0;
		int i;
		
		for(i=0; i<25; i++){
			fscanf(info_fp,"%d %d %d %d %d",&id,&mid1,&mid2,&final,&class);
			mid_avg102 += (mid1+mid2)/2;
			final_avg102 += final;
		}
		mid_avg102= mid_avg102/25;
		final_avg102 = final_avg102/25;
		
		for(i=0; i<25; i++){
			fscanf(info_fp,"%d %d %d %d ",&id,&mid1,&final,&class);
			mid_avg108 += mid1;
			final_avg108 += final;
		}
		
		mid_avg108 = mid_avg108/25.0;
		final_avg108 = final_avg108/25.0;
		
		 fseek(info_fp, 0, SEEK_SET);
		
		while(fscanf(info_fp,"%d",&current_id) == 1){
			if(current_id == id ){
				if(((id/10000000) % 10) == 2){
					fscanf(info_fp,"%d %d %d %d %d ",&id,&mid1,&mid2,&final,&class);
					if((mid1+mid2)/2 <40 && (mid1+mid2)<mid_avg102){
						gpa = 1;
					}else if((mid1+mid2)/2 >40 && (mid1+mid2)<mid_avg102){
						gpa = 2.5;
					}else if((mid1+mid2)/2 >40 && (mid1+mid2)>mid_avg102){
						gpa = 3.0;
					}else if((90 > mid1+mid2)/2 && (mid1+mid2) > mid_avg102){
						gpa = 3.5;
					}else if((mid1+mid2)/2.0 >= 90){
						gpa = 4.0;
					}
					
					if(final<40 && final < final_avg102){
						gpa += 1;
					}else if(final > 40 && final < final_avg102){
						gpa += 2.5;
					}else if(final >40 && final > final_avg102){
						gpa +=3.0;
					}else if(90 > final && final>final_avg102){
						gpa +=3.5;
					}else if(final >=90){
						gpa += 4.0;
					}
					gpa = gpa/2;
					
				}else if(((id/10000000) % 10) == 1){
					fscanf(info_fp,"%d %d %d %d  ",&id,&mid1,&final,&class);
					if((mid1)/2 <40 && (mid1)<mid_avg102){
						gpa = 1;
					}else if((mid1)/2 >40 && (mid1)<mid_avg108){
						gpa = 2.5;
					}else if((mid1)/2 >40 && (mid1)>mid_avg108){
						gpa = 3.0;
					}else if((90 > mid1)/2 && (mid1) > mid_avg108){
						gpa = 3.5;
					}else if((mid1)/2 >= 90){
						gpa = 4.0;
					}
					
					if(final<40 && final < final_avg108){
						gpa += 1;
					}else if(final > 40 && final < final_avg108){
						gpa += 2.5;
					}else if(final >40 && final > final_avg108){
						gpa +=3.0;
					}else if(90 > final && final>final_avg108){
						gpa +=3.5;
					}else if(final >=90){
						gpa += 4.0;
					}
					gpa = gpa/2;
				}
			}
		
		}	
		
		return gpa;	
	}
int find_classes(FILE * info_fp, int id){	
	fseek(info_fp, 0, SEEK_SET);
	int number;
	int current_id;
	while(fscanf(info_fp,"%d",&current_id) == 1){
			if(current_id == id ){
				fscanf(info_fp,"%d",&number);
				break;
			}
			
			}
			return number;
}

int find_department(FILE *id_fp,char role_initial){
	fseek(id_fp, 0, SEEK_SET);
	
	char c;
	int current_id=0;
	
	while((c = fgetc(id_fp) != EOF)){
	ungetc(c, id_fp);
        fscanf(id_fp, "%d", &current_id);
	while ((c = fgetc(id_fp)) != EOF && c != ';') {}
	while ((c = fgetc(id_fp)) != EOF && c != ';') {}
	while ((c = fgetc(id_fp)) != EOF && c != ';') {}
	fscanf(id_fp, " %c", &c);
	if(c == role_initial){
		if (current_id != 0) {
                printf(", ");
            }
            printf("%d", current_id);
            
        } else {
            while ((c = fgetc(id_fp)) != EOF && c != '\n') {}
        }
	}

	}



int main(){
	FILE *first_fp = fopen("first.txt", "r");
	FILE *second_fp = fopen("second.txt", "r");
	int flag = 1,id; 
	char choice;

	while(flag){
	printf("‘d’: Print the department of all persons according to the role.\n");
	printf("'n' print only the user with a specific first inital. \n");
	printf("'g' calculate the gpa of a given student . \n");
	printf("'c' printf whether each user passed or failed the same class.\n");
	printf("'t' print the number of classes forthe instructor. \n");
	printf("'l' printf_the course_id of a given student.\n");
	printf("'e' quit the program. \n");
	
	printf("your choice: \n");
	scanf("%c",&choice);
	
	
	switch(choice){
		case 'g': 
		printf("enter an id: \n");
		scanf("%d",&id);
		float gpa = average_grade(first_fp, id);
		if(gpa ==1){
			printf("F\n");
		}else if(gpa == 2){
			printf("D\n");
		}else if(gpa ==2.5){
			printf("C\n");
		}else if(gpa ==3.5){
			printf("B\n");
		}else if(gpa == 4){
			printf("A\n");
		}
		break;
		
		case 't':
		int num;
		printf("enter an id: \n");
		scanf("%d",&id);
		num = find_classes(first_fp,id);
		printf("%d\n",num);
		break;
		
		case 'd':
		char initial;
		printf("Enter 's' for student 'i' for instructor.\n");
		scanf("%c",&initial);
		find_department(second_fp,initial);
		break;
		case 'e':
		flag =0;
		break;
		default:
		printf("invalid option.\n ********\n");
		break;
	}
	}

	fclose(first_fp);
	fclose(second_fp);

}










