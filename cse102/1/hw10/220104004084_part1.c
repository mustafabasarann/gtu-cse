#include <stdio.h>
#include <stdlib.h>

#define HOME_STREET 3
#define HOME_AVENUE 3

int numPathsHome(int street, int avenue) {

    if (street == HOME_STREET && avenue == HOME_AVENUE) {
        return 1;
    }

    if (street < 1 || street > 5 || avenue < 1 || avenue > 5) {
    	printf("You need to enter street and avenue numbers between 1 and 5.\n");
        exit(0);
    }

    int paths = 0;

    if (avenue > HOME_AVENUE) {
        paths += numPathsHome(street, avenue - 1);
    }

    if (avenue < HOME_AVENUE) {
        paths += numPathsHome(street, avenue + 1);
    }

    if (street > HOME_STREET) {
        paths += numPathsHome(street - 1, avenue);
    }

    if (street < HOME_STREET) {
        paths += numPathsHome(street + 1, avenue);
    }

    return paths;
}

int main() {
    int street; 
    int avenue; 
    printf("Enter the street number: ");
    scanf("%d",&street);
    printf("Enter the avenue number: ");
    scanf("%d",&avenue);
    
    int paths = numPathsHome(street, avenue);
    printf("Number of optimal paths to take back home: %d\n", paths);
    
}

