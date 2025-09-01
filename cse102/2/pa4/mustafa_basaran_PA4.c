#include <stdio.h>
#include <string.h>

#define MAX_DESCRIPTION_LENGTH 500
#define MAX_IDENTIFIER_LENGTH 30
#define MAX_TERMS 100

typedef struct {
    char ident[MAX_IDENTIFIER_LENGTH]; // Module identifier
    int coeff;                      // Coefficient of the term
} Module;

// function to remove spaces from a string
void remove_spaces(char* input, char* output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ') {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

int evaluate(char* name){
	// check if the module name starts with a digit
	if ((name[0] >= '0' && name[0] <= '9')) {
   		printf("Invalid module name. Mustn't start with a digit.\n");
    		return -1;
	}

	
	printf("Define %s:\n",name);
	char description[MAX_DESCRIPTION_LENGTH];
	fgets(description, MAX_DESCRIPTION_LENGTH, stdin); // read description 
	description[strcspn(description, "\n")] = '\0'; // remove new line character for last term
	
	// remove spaces from the description
	char spaceless_description[MAX_DESCRIPTION_LENGTH];
	remove_spaces(description, spaceless_description);
	
	int sum = 0;
	
	Module modules[MAX_TERMS];
	int number_of_terms = 0;
	// parsing 
	char* token = strtok(spaceless_description, "+");
	int i = 0;
	while(token != NULL){
	// check the number of terms if it exceeds
		if(number_of_terms >= MAX_TERMS) {
			printf("Too many terms. Maximum allowed terms is %d\n", MAX_TERMS);
			return -1;
		}
		
		number_of_terms++;
		strcpy(modules[i].ident, token);
		token = strtok(NULL, "+");
		i++;
	}
	
	char ident[MAX_IDENTIFIER_LENGTH];
	int coeff;
	// process parsed terms
	for(int j = 0; j < number_of_terms; j++){
		if(sscanf(modules[j].ident, "%d*%s", &(modules[j].coeff), ident) == 2 ){
			sum += modules[j].coeff * evaluate(ident);
		}else if(sscanf(modules[j].ident, "%d", &(modules[j].coeff)) == 1 ){
			sum += modules[j].coeff;
		}else{
			printf("Unexpected input format in term '%s'.\n", modules[j].ident);
			return -1;
		}
	}
	
	return sum;
}

int main(){
	char name[MAX_IDENTIFIER_LENGTH];
	printf("Module name?:\n");
	scanf("%s", name);
	getchar();
	
	int result = evaluate(name);
	printf("%d\n", result);

	return 0;
}
