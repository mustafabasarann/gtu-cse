#include <stdio.h>
#include <string.h>

void sort_people_by_age();
void sort_people_by_branch();
void filter_people_by_branch();
void filter_people_by_profession();

struct Person {
	char name[50];
	char surname[50];
	int age;
	char branch1[50];
	char branch2[50];
};


int main(){

	FILE *file = fopen("input1.txt","r");
	
	if(file == NULL){
		printf("Error opening file.\n");
		return 1;
	}
	
	/* find number of scientists */
	int count = 0;
	char line[200];
	
	while(fgets(line,sizeof(line),file) != NULL){
		count++;
	}
	
	rewind(file);
	
	struct Person people[count];
	
	/* read datas from the file */
	int i;
	for(i = 0; i<count; i++){
		fgets(line, sizeof(line), file);
        sscanf(line, "%[^,],%[^,], %d, %[^,]%[^\n]", people[i].name, people[i].surname, &people[i].age, people[i].branch1, people[i].branch2);
	if (strcmp(people[i].branch2, "") == 0) {
            strcpy(people[i].branch2, "--"); 
        }
        if (strcmp(people[i].surname, " ") == 0) {
            strcpy(people[i].surname, "-"); 
     		   }
        
		}

			
	fclose(file);

	
	int flag = 1;
	while(flag){
	printf("******Menu*********************\n");
	printf("1. Sort and display all individuals by age\n");
	printf("2. Sort and display individuals in the branch by age\n");
	printf("3. Show individuals with the branch 'SCIENCE'\n");
	printf("4. Show computer scientists who are mathematicians\n");
	printf("5. Exit\n");
	
	int choice;
	printf("Choice:");
	scanf("%d",&choice);
	
	switch(choice){
		case 1:
		sort_people_by_age(people, count);
		
		break;
		case 2 :
		sort_people_by_branch(people,count);
		printf("\n\n");
		break;
		case 3:
		filter_people_by_branch(people,count);
		printf("\n\n");
		break;
		case 4:
		filter_people_by_profession(people,count);
		printf("\n\n");
		break;
		case 5:
		flag = 0;
		printf("\n\n");
		break;
		default:
		printf("Invalid Option!\n");
		}
	}
}

void sort_people_by_age(struct Person people[], int n){
	int i,j;
	/* Bubble sort */
	for(i = 0; i < n-1; i++){
		for(j = 0; j < n-i-1; j++){
			if(people[j].age > people[j+1].age) {
				struct Person temp = people[j];
				people[j] = people[j+1];
				people[j+1] = temp;
			}
		}
	}
	
	for (i = 0; i < n; i++) {
        printf("%s %s %d %s %s\n", people[i].name, people[i].surname, people[i].age, people[i].branch1, people[i].branch2);
    }

} 

void sort_people_by_branch(struct Person people[], int n){
	int i,j;
	
	for(i = 0; i < n-1; i++){
		for(j = 0; j < n-i-1; j++){
			if(strcmp(people[j].branch1,people[j+1].branch1) > 0){
				struct Person temp = people[j];
				people[j] = people[j+1];
				people[j+1] = temp;
			}else if(strcmp(people[j].branch1,people[j+1].branch1) == 0){
				if(strcmp(people[j].branch2,people[j+1].branch2) > 0){
					struct Person temp = people[j];
					people[j] = people[j+1];
					people[j+1] = temp;
				}
			}else if((strcmp(people[j].branch1,people[j+1].branch1) == 0) && (strcmp(people[j].branch2,people[j+1].branch2)) == 0 ){
				if(people[j].age > people[j+1].age) {
					struct Person temp = people[j];
					people[j] = people[j+1];
					people[j+1] = temp;	
					}
				}
			}
		}
	
	for (i = 0; i < n; i++) {
        printf("%s %s %d %s %s\n", people[i].name, people[i].surname, people[i].age, people[i].branch1, people[i].branch2);
    }
}

void filter_people_by_branch(struct Person people[], int n){
	int i;
	
	for(i = 0; i<n; i++){
		if(strstr(people[i].branch1,"SCIENCE") || strstr(people[i].branch2,"SCIENCE")){
			printf("%s %s %d %s %s\n", people[i].name, people[i].surname, people[i].age, people[i].branch1, people[i].branch2);
		}
	}
}

void filter_people_by_profession(struct Person people[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        if ((strcmp(people[i].branch1, "COMPUTER SCIENCE") == 0) && (strcmp(people[i].branch2, "MATHEMATICS") < 0 )) {
            printf("%s %s %d %s %s\n", people[i].name, people[i].surname, people[i].age, people[i].branch1, people[i].branch2);
        }
    }
}


