#include <stdio.h>
void menu();
void get_content();
void readed_news();
float secret_calculator();

int main(){
	menu();
}

void menu(){ /*menu function*/

	/*printing titles of the news*/
	printf("**********Daily Press**********\n\n");
	printf("Today's news are listed for you:\n\n");
	char c;
	FILE *news1 = fopen("1.txt", "r");
	if (news1 == NULL) {
		printf("Error opening the file.\n");
		return;
	}
	
	printf("Title of 1. news: ");
	while (fscanf(news1, "%c", &c) != EOF && c != '\n') {
		printf("%c", c);
	}
	printf("\n");
	fclose(news1);
	
	
	FILE *news2 = fopen("2.txt", "r");
	if (news2 == NULL) {
		printf("Error opening the file.\n");
		return;
	}
	
	printf("Title of 2. news: ");
	while (fscanf(news2, "%c", &c) != EOF && c != '\n') {
		printf("%c", c);
	}
	printf("\n");
	fclose(news2);
	
	FILE *news3 = fopen("3.txt", "r");
	if (news3 == NULL) {
		printf("Error opening the file.\n");
		return;
	}
	
	printf("Title of 3. news: ");
	while (fscanf(news3, "%c", &c) != EOF && c != '\n') {
		printf("%c", c);
	}
	printf("\n");
	fclose(news3);
	
	FILE *news4 = fopen("4.txt", "r");
	if (news4 == NULL) {
		printf("Error opening the file.\n");
		return;
	}
	
	printf("Title of 4. news: ");
	while (fscanf(news4, "%c", &c) != EOF && c != '\n') {
		printf("%c", c);
	}
	printf("\n");
	fclose(news4);
	
	printf("\nWhat do you want to do?\n");
	printf("a.Read a new\n");
	printf("b.List the readed news\n");
	printf("c.Get decrypted information from the news\n");
	
	
	char choice,flag = 'y';
	int num;
	
	while(flag == 'y'){
	
	printf("Select an operation from the menu: ");
	scanf(" %c",&choice);
	
	switch(choice){/*operations*/
		case 'a':
			printf("Select a new to read: ");
			scanf("%d",&num);
			printf("\n*********************\n");
			get_content(num);
			printf("Do you want to return to the menu? Yes(y)/No(n): ");
			scanf(" %c",&flag);
			break;
		case 'b':
			readed_news();
			printf("Do you want to return to the menu? Yes(y)/No(n): ");
			scanf(" %c",&flag);
			break;
		case 'c':
			printf("Which news would you like to decrypt?: ");
			scanf("%d",&num);
			printf("\n%d. Experiment key = %f\n",num,secret_calculator(num));
			printf("Do you want to return to the menu? Yes(y)/No(n): ");
			scanf(" %c",&flag);
			break;
		}
		
		
	}
	printf("Goodbye!\n");
}

void get_content(int num){/*printing readed news to readed_news_id.txt file*/
	FILE *readed = fopen("readed_news_id.txt","r+");
	int k,p=1;
	int check = 0;
	while(fscanf(readed,"%d",&k) != EOF){
		if(k == num){
			check = 1;
			printf("This new is readed.Do you want to read again? Yes(1),No(0): ");
			scanf(" %d",&p);
		}
		}
		if(!check){
			fprintf(readed," %d",num);
		}
	fclose(readed);
	
	if(p){/*getting all content of the news from text files*/
		char c;
		switch(num){
		case 1:
			FILE *file1 = fopen("1.txt","r");
			if(file1 == NULL){
				printf("Error opening the file.");
			}
			while(fscanf(file1,"%c",&c) != EOF)
			{
				printf("%c",c);
			}
			fclose(file1);
			printf("\n");
			break;
		case 2:
			FILE *file2 = fopen("2.txt","r");
			if(file2 == NULL){
				printf("Error opening the file.");
			}
			while(fscanf(file2,"%c",&c) != EOF)
			{
				printf("%c",c);
			}
			fclose(file2);
			printf("\n");
			break;
		
		case 3:
			FILE *file3 = fopen("3.txt","r");
			if(file3 == NULL){
				printf("Error opening the file.");
			}
			while(fscanf(file3,"%c",&c) != EOF)
			{
				printf("%c",c);
			}
			fclose(file3);
			printf("\n");
			break;
			
		case 4:
			FILE *file4 = fopen("4.txt","r");
			if(file4 == NULL){
				printf("Error opening the file.");
			}
			while(fscanf(file4,"%c",&c) != EOF)
			{
				printf("%c",c);
			}
			fclose(file4);
			printf("\n");
			break;
		}
	}
}


void readed_news(){/*printing readed news*/
	int k;
	
	printf("Readed news are listed below:\n");
	FILE *readed = fopen("readed_news_id.txt","r");
	while(fscanf(readed,"%d",&k) !=EOF){
		printf("%d. new is readed\n",k);
	}
	
	fclose(readed);
}	

float secret_calculator(int num){/*calculating the secretNumber funciton*/
	char c;
	float magic;
	float secretNumber = 0.0,result = 0.0;
	
	switch(num){
	case 1:
		FILE *file1 = fopen("1.txt","r");
		
		while(fscanf(file1,"%c",&c) != EOF){
			if(c == '#'){
				fscanf(file1,"%f",&magic);
				secretNumber += (magic*magic*magic-magic*magic+2)*(magic*magic*magic-magic*magic+2);
			}
		}
		fclose(file1);
		break;
	case 2:
		FILE *file2 = fopen("2.txt","r");
		
		while(fscanf(file2,"%c",&c) != EOF){
			if(c == '#'){
				fscanf(file2,"%f",&magic);
				secretNumber += (magic*magic*magic-magic*magic+2)*(magic*magic*magic-magic*magic+2);
			}
			
		}
		fclose(file2);
		break;
	case 3:
		FILE *file3 = fopen("3.txt","r");
		
		while(fscanf(file3,"%c",&c) != EOF){
			if(c == '#'){
				fscanf(file3,"%f",&magic);
				secretNumber += (magic*magic*magic-magic*magic+2)*(magic*magic*magic-magic*magic+2);
			}
			
		}
		fclose(file3);
		break;
	case 4:
		FILE *file4 = fopen("4.txt","r");
		
		while(fscanf(file4,"%c",&c) != EOF){
			if(c == '#'){
				fscanf(file4,"%f",&magic);
				secretNumber += (magic*magic*magic-magic*magic+2)*(magic*magic*magic-magic*magic+2);
			}
			
		}
		fclose(file4);
		break;
	}
	return secretNumber;
}

