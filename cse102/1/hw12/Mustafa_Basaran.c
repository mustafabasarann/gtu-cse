#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Species {
	char class[20];
	char order[20];
	char family[20];
	char genus[20];
	char species[20];
	struct Species* next;
}Species;

	
Species* add(Species* root){
	Species* node = (Species*)malloc(sizeof(Species));

	printf("Class: ");
    	scanf("%s", node->class);
    	printf("Order: ");
   	scanf("%s", node->order);
    	printf("Family: ");
    	scanf("%s", node->family);
    	printf("Genus: ");
    	scanf("%s", node->genus);
    	printf("Species: ");
   	scanf("%s", node->species);
   	printf("*********************************\n");
	
	node->next = NULL;
	
	if(root == NULL){
		root = node;
	}else{
		Species* temp = root;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = node;
		
	}
		return root;
}

void modify(Species* root){
	char target[20];
	int isFound = 0;
	printf("Enter species name to modify:\n");
	printf("Old Species: ");
	scanf("%s", target);
	

	Species* node = root;
	while(node != NULL){
		if(strcmp(node->species, target) == 0){
			printf("New Class: ");
            		scanf("%s", node->class);
		        printf("New Order: ");
		        scanf("%s", node->order);
		        printf("New Family: ");
		        scanf("%s", node->family);
		        printf("New Genus: ");
		        scanf("%s", node->genus);
		        printf("New Species: ");
		        scanf("%s", node->species);
		        printf("Species modified successfully!\n");
		        isFound = 1;
		}
		node = node->next;
	}
	if(!isFound){
		printf("Species not found.\n");
	}
	printf("*********************************\n");
}

Species* delete(Species* root){
	char target[20];
	printf("Enter species name to delete: ");
	scanf("%s", target);
	
	Species* current = root;
	Species* prev = NULL;
	
	while(current != NULL){
		if(strcmp(current->species, target) == 0){
			if(prev == NULL){
				Species* new_root = current->next;
				free(current);
				return new_root;
			}else {
				prev->next = current->next;
				free(current);
				return root;
			}
		}
		prev = current;
		current = current->next;
	}
	printf("Species not found.\n");
	return root;
}


void display(Species* root){
	Species* node = root;
		
	if(node == NULL){
		printf("No species information existing.\n");
		return;
	}
	
	while(node != NULL){
		printf("Class: %s\n",node->class);
		printf("Order: %s\n",node->order);
		printf("Family: %s\n",node->family);
		printf("Genus: %s\n",node->genus);
		printf("Species: %s\n",node->species);
		
		node = node->next;
		printf("*********************************\n");
	}
	
}

Species* sort(Species* root, int sortBy) {
	if (root == NULL || root->next == NULL) {
        	return root;
  	  }

    	Species* new_root = NULL;

    	while (root != NULL) {
        	Species* current = root;
        	root = root->next;

        if (new_root == NULL || (sortBy == 1 && strcmp(current->class, new_root->class) < 0) ||
        	(sortBy == 2 && strcmp(current->order, new_root->order) < 0) ||
        	(sortBy == 3 && strcmp(current->family, new_root->family) < 0) ||
        	(sortBy == 4 && strcmp(current->genus, new_root->genus) < 0) ||
   		(sortBy == 5 && strcmp(current->species, new_root->species) < 0)) {
        	current->next = new_root;    
        	new_root = current;
        } else {
                Species* temp = new_root;
                while (temp->next != NULL && 
                    ((sortBy == 1 && strcmp(current->class, temp->next->class) >= 0) ||
                    (sortBy == 2 && strcmp(current->order, temp->next->order) >= 0) ||
                    (sortBy == 3 && strcmp(current->family, temp->next->family) >= 0) ||
                    (sortBy == 4 && strcmp(current->genus, temp->next->genus) >= 0) ||
                    (sortBy == 5 && strcmp(current->species, temp->next->species) >= 0))) {
                temp = temp->next;
            }
            	current->next = temp->next;        
           	temp->next = current;
        }
    }                                                  		         
    	printf("Species sorted successfully!\n");
    	return new_root;
}

int main(){
	Species* root = NULL;
   	 int choice;
   	 char criteria[20];
    do {
        printf("Menu:\n");
        printf("1. Add\n");
        printf("2. Display\n");
        printf("3. Modify\n");
        printf("4. Delete species\n");
        printf("5. Sort\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = add(root);
                break;
            case 2:
                display(root);
                break;
            case 3:
                modify(root);
                break;
            case 4:
                root = delete(root);
                break;
            case 5:
            	printf("Enter list criteria (class, order, family, genus, species): ");
            	scanf("%s",criteria);
            	if(strcmp(criteria, "class") == 0){
            		root = sort(root,1);
            	}else if(strcmp(criteria, "order") == 0){
            		root = sort(root,2);
            	}else if(strcmp(criteria, "family") == 0){
            		root = sort(root,3);
            	}else if(strcmp(criteria, "genus") == 0){
            		root = sort(root,4);
            	}else if(strcmp(criteria, "species") == 0){
            		root = sort(root,5);
            	}
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);
}








