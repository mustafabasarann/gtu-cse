#include <stdio.h>

int main() {
    char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char k;
    int key = 7; 
    int i = 0;
    int comment = 0;
    int counter = 0;
    int ones, tens;
    while (scanf("%c", &k) != EOF) {
        if (k == '/') {
            char next_char;
            scanf("%c", &next_char);
            if (next_char == '*') {
                comment = 1;
                counter = 0; 
                continue;
            }
            else {
                printf("/");
            }
        }

        if (k == '*') {
            char next_char;
            scanf("%c", &next_char);
            if (next_char == '/') {
                if (comment) {
                    tens = counter / 10; 
                    ones = counter % 10;
                    int newTensIndex = (tens + key)%61;
                    int newOnesIndex = (ones + key)%61 ;
                    printf("@%c%c", alphabet[newTensIndex], alphabet[newOnesIndex]); 
                }
                comment = 0;
                counter = 0;
                continue;
            }
            else {
                printf("*");
            }
        }
        
        if (comment) {
            counter++; 
            continue;
        }

        if (k == ' ') { 
            printf(" ");
            continue;
        }

        i = 0;
        while (i < 61) {
            if (k == alphabet[i]) {
                int newIndex = (i + key)%61 ; 
                k = alphabet[newIndex];
                printf("%c", k);
                break;
            }
            i++;
        }
        if (k == '\n') {
            printf("\n");
        }
    }
    return 0;
}

