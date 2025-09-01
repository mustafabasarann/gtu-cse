#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE* values = fopen("values.txt", "r");
    FILE* polynomials = fopen("polynomials.txt", "r");
    FILE* evaluations = fopen("evaluations.txt", "w");
    
    if (values == NULL || polynomials == NULL || evaluations == NULL) {
        perror("Failed to open file");
        return 1;
    }
    
    double x, y;  
    char polinom[MAX_LINE_LENGTH];
    char spaceless_polinom[MAX_LINE_LENGTH];
	
    while (fgets(polinom, sizeof(polinom), polynomials) != NULL) {
        // skip empty lines
        if (*polinom == '\n') {
            continue;
        }

        // copy polinom to spaceless_polinom without spaces
        int j = 0;  
        for (int i = 0; polinom[i] != '\0'; i++) {
            if (polinom[i] != ' ') {
                spaceless_polinom[j] = polinom[i];
                j++;
            }
        }
        spaceless_polinom[j] = '\0';  

        // evaluate polynomials for each x y pair
        while (fscanf(values, "%lf %lf", &x, &y) != EOF) {
            double result = 0.0;  
            
           // Copy spaceless_polinom to `poly_copy` to preserve the original
            char poly_copy[MAX_LINE_LENGTH];
            strcpy(poly_copy, spaceless_polinom);
            
            // parse first term 
            char *term = strtok(poly_copy, "+- ");
            int sign = (spaceless_polinom[0] == '-') ? -1 : 1;  // determine sign of the first term

            while (term != NULL) {
                double coeff = 1.0;
                int x_exp = 0, y_exp = 0;
                int offset = 0;

                // get coefficient and apply the sign
                if (sscanf(term, "%lf%n", &coeff, &offset) == 1) {
                    coeff *= sign;
                } else {
                    coeff = sign;  
                }

                // get x's exponent
                char *x_pos = strchr(term + offset, 'x');
                if (x_pos) {
                    if (*(x_pos + 1) == '^') {
                        sscanf(x_pos + 2, "%d", &x_exp);
                    } else {
                        x_exp = 1;
                    }
                } else {
                    x_exp = 0; 
                }

                // get y's exponent
                char *y_pos = strchr(term + offset, 'y');
                if (y_pos) {
                    if (*(y_pos + 1) == '^') {
                        sscanf(y_pos + 2, "%d", &y_exp);
                    } else {
                        y_exp = 1;
                    }
                } else {
                    y_exp = 0; 
                }

                // calculate this term and add it to the result
                result += coeff * pow(x, x_exp) * pow(y, y_exp);

                // move to the next term and update the sign
                term = strtok(NULL, "+- ");
                if (term != NULL) {
                    int pos = term - poly_copy - 1;
                    sign = (spaceless_polinom[pos] == '-') ? -1 : 1;
                }
            }

            // write the results for this x y pair
            fprintf(evaluations, "%.2f ", result);
        }

        fprintf(evaluations, "\n");  
        rewind(values);  
    }

    fclose(evaluations);
    fclose(values);
    fclose(polynomials);

    return 0;
}

