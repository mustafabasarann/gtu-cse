#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ALPHABET_SIZE 27 // 26 letter + 1 space
#define MAX_FILENAME 100

// return characters as index 
int char_to_index(char c) {
        if (c == ' ') return 26;
        return c - 'a';
}

// get bigram frqeuencies from the file and fill the matrix 
void calculate_bigram_frequencies(FILE *file, int matrix[ALPHABET_SIZE][ALPHABET_SIZE], int *total_bigrams) {
        char prev = 0, current;

        while ((current = fgetc(file)) != EOF) {
                // skip the invalid characters 
                if (current == '\n' || current == '\t' || current == '\r') {
                        continue;
                }

                // letter or space control
                if ((prev >= 'a' && prev <= 'z') || prev == ' ') {
                        if ((current >= 'a' && current <= 'z') || current == ' ') {
                                int i = char_to_index(prev);
                                int j = char_to_index(current);
                                if (!(i == 26 && j == 26)) { // two spaces doesn't creates a bigram
                                        matrix[i][j]++;
                                        (*total_bigrams)++;
                                }
                        }
                }

                // save the current character for previous  
                if ((current >= 'a' && current <= 'z') || current == ' ') {
                        prev = current;
                }
        }
}

// calculates dissimilarity score between two bigram  
double calculate_dissimilarity(int matrix1[ALPHABET_SIZE][ALPHABET_SIZE], int total1, 
                                int matrix2[ALPHABET_SIZE][ALPHABET_SIZE], int total2) {
        double dissimilarity = 0.0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
                for (int j = 0; j < ALPHABET_SIZE; j++) {
                        double freq1 = (total1 > 0) ? (double)matrix1[i][j] / total1 : 0.0;
                        double freq2 = (total2 > 0) ? (double)matrix2[i][j] / total2 : 0.0;
                        dissimilarity += fabs(freq1 - freq2);
                }
        }
        return dissimilarity;
}

int main() {
        // define the referance file name as constant  
        const char *reference_file_name = "language_x.txt";

        // calculate matrix and total bigram of referance file
        int reference_matrix[ALPHABET_SIZE][ALPHABET_SIZE] = {0};
        int total_reference = 0;

        FILE *reference_file = fopen(reference_file_name, "r");
        if (!reference_file) {
                fprintf(stderr, "Referans dosya açılamadı: %s\n", reference_file_name);
                return 1;
        }
        calculate_bigram_frequencies(reference_file, reference_matrix, &total_reference);
        fclose(reference_file);

        // read each files 
        int n = 1;
        char current_file_name[MAX_FILENAME];
        while (1) {
                // create file name 
                sprintf(current_file_name, "language_%d.txt", n);

                // try to open the file
                FILE *current_file = fopen(current_file_name, "r");
                if (!current_file) {
                        break; // if cant, exit
                }

                // Geçerli dosyanın bigram matrisini ve toplam bigram sayısını hesapla
                int current_matrix[ALPHABET_SIZE][ALPHABET_SIZE] = {0};
                int total_current = 0;
                calculate_bigram_frequencies(current_file, current_matrix, &total_current);
                fclose(current_file);

                // calculate dissimilarity and print 
                double dissimilarity = calculate_dissimilarity(reference_matrix, total_reference, current_matrix, total_current);
                printf("%lf\n", dissimilarity);
                n++;
        }

        return 0;
}

