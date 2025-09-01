#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

// Function prototypes
void read_input(const char *filename, int ***grid, int *rows, int *cols);
void write_output(const char *filename, int **grid, int rows, int cols);
int find_label(int *labels, int x);
void union_labels(int *labels, int a, int b);
void hoshen_kopelman(int **grid, int rows, int cols);

int main() {
	// Grid and its dimensions
	int **grid = NULL;
	int rows, cols;

	// Read grid data from input file
	read_input("input.txt", &grid, &rows, &cols);

	// Apply the Hoshen-Kopelman algorithm
	hoshen_kopelman(grid, rows, cols);

	// Write labeled grid to output file
	write_output("output.txt", grid, rows, cols);

	// Free dynamically allocated memory
	for (int i = 0; i < rows; i++) {
		free(grid[i]);
	}
	free(grid);

	return 0;
}

// Reads the grid data from input.txt
void read_input(const char *filename, int ***grid, int *rows, int *cols) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("File could not be opened");
		exit(EXIT_FAILURE);
	}

	// Read the dimensions of the grid
	fscanf(file, "%d %d", rows, cols);

	// Allocate memory for the grid
	*grid = (int **)malloc(*rows * sizeof(int *));
	for (int i = 0; i < *rows; i++) {
		(*grid)[i] = (int *)malloc(*cols * sizeof(int));
		for (int j = 0; j < *cols; j++) {
			fscanf(file, "%d", &((*grid)[i][j]));
		}
	}

	fclose(file);
}

// Writes the labeled grid to output.txt
void write_output(const char *filename, int **grid, int rows, int cols) {
	FILE *file = fopen(filename, "w");
	if (!file) {
		perror("File could not be opened");
		exit(EXIT_FAILURE);
	}

	// Write each row of the grid
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fprintf(file, "%d ", grid[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

// Finds the root label of a given label using path compression
int find_label(int *labels, int x) {
	if (labels[x] != x) {
		labels[x] = find_label(labels, labels[x]); // Path compression
	}
	return labels[x];
}

// Merges two groups by uniting their root labels
void union_labels(int *labels, int a, int b) {
	int root_a = find_label(labels, a);
	int root_b = find_label(labels, b);
	if (root_a != root_b) {
		labels[root_b] = root_a;
	}
}

// Implements the Hoshen-Kopelman algorithm for connected component labeling
void hoshen_kopelman(int **grid, int rows, int cols) {
	// Allocate memory for labels
	int *labels = (int *)malloc((rows * cols + 1) * sizeof(int));
	for (int i = 0; i <= rows * cols; i++) {
		labels[i] = i; // Initialize labels
	}

	int label = 1;

	// First pass: Assign labels to connected cells
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] == 1) { // Check if the cell is part of a group
				int left = (j > 0) ? grid[i][j - 1] : 0; // Left neighbor
				int up = (i > 0) ? grid[i - 1][j] : 0;   // Top neighbor

				if (left > 0 && up > 0) {
					// Both neighbors belong to groups
					int new_label = find_label(labels, left);
					grid[i][j] = new_label;
					union_labels(labels, left, up);
				} else if (left > 0) {
					// Only left neighbor belongs to a group
					grid[i][j] = find_label(labels, left);
				} else if (up > 0) {
					// Only top neighbor belongs to a group
					grid[i][j] = find_label(labels, up);
				} else {
					// Create a new group
					grid[i][j] = label++;
				}
			}
		}
	}

	// Allocate new labels for renumbering
	int *new_labels = (int *)calloc(label, sizeof(int));
	int new_label = 1;

	// Second pass: Renumber labels for sequential numbering
	for (int i = 1; i < label; i++) {
		int root = find_label(labels, i);
		if (new_labels[root] == 0) {
			new_labels[root] = new_label++;
		}
	}

	// Update the grid with renumbered labels
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] > 0) {
				grid[i][j] = new_labels[find_label(labels, grid[i][j])];
			}
		}
	}

	// Free allocated memory
	free(labels);
	free(new_labels);
}

