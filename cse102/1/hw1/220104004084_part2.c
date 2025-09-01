#include <stdio.h>

int main() {
    char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char k;
    int key = 7;
    int i = 0;
    int comment = 0;
    int newTensIndex = 0;
    int newOnesIndex = 0;
    
    while (scanf("%c", &k) != EOF) {
        if (k == '@') {
            comment = 1;
            continue;
        }
        
        if (comment == 1) {
            newTensIndex = (k - key)%61;
            comment = 2;
            continue;
        }
        
        if (comment == 2) {
            newOnesIndex = (k - key)%61;
            printf(" /*There is %c%c characters as comment.*/", alphabet[newTensIndex], alphabet[newOnesIndex]);
            comment = 0;
            continue;
        }
        
        i = 0;
        while (i < 61) {
            if (k == alphabet[i]) {
                int newIndex = (i - key) ; 
                k = alphabet[newIndex];
                printf("%c", k);
                break;
            } else if (k == ' ') {
                printf(" ");
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

