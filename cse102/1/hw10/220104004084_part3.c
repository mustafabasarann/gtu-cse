#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
struct card{
	const char *face;
	const char *suit;
};

void swap(struct card *a, struct card *b){
	struct card temp = *a;
	*a = *b;
	*b = temp;
}

void shuffle(struct card *deck){
	int i,j;
	srand(time(0));
	for(i = 51; i > 0; i--){
		j = rand() % (i + 1);
		swap(&deck[i], &deck[j]);
	}
}

int main(){
	struct card deck[52];
	const char * faces[] = {
	"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven","Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
	int index = 0;
	int i,j;
	for(i = 0; i < 4; i ++){
		for(j = 0; j < 13; j++){
			deck[index].face = faces[j];
			deck[index].suit = suits[i];
			index++;
		}
	}
	
	shuffle(deck);
	for (i = 0; i < 52; i+=2) {
        printf("%8s of %-8s       %8s of %-8s\n", deck[i].face, deck[i].suit, deck[i+1].face, deck[i+1].suit);
    }
}



