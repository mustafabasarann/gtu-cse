#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUTS 10           // Maximum number of inputs for any gate
#define MAX_NAME 20             // Maximum length of a gate name
#define INITIAL_CAPACITY 20     // Initial capacity for gate arrays

// Enumeration to define the types of gates
enum GateType {INPUT_GATE, OUTPUT_GATE, AND_GATE, OR_GATE, NOT_GATE, FLIPFLOP_GATE};

// Structure to represent a logic gate
typedef struct gate {
    int type;                                      // The type of the gate
    char name[MAX_NAME];                           // The name of the gate
    struct gate* input_gates[MAX_INPUTS];          // Array of input gates
    int number_of_inputs;                          // Number of input gates
    int output;                                    // Output of the gate
    int former_out;                                // Previous output (for flip-flop gates)
    short evaluated;                               // Flag to check if the gate has been evaluated
    int (*characteristic_function)(int*, int);    // Pointer to the gate's characteristic function
} Gate;

// Logical AND gate function
int and_function(int* inputs, int n) {
    for (int i = 0; i < n; i++) {
        if (!inputs[i]) return 0; // If any input is 0, the output is 0
    }
    return 1; // All inputs are 1, so the output is 1
}

// Logical OR gate function
int or_function(int* inputs, int n) {
    for (int i = 0; i < n; i++) {
        if (inputs[i]) return 1; // If any input is 1, the output is 1
    }
    return 0; // All inputs are 0, so the output is 0
}

// Logical NOT gate function
int not_function(int* inputs, int n) {
    return !inputs[0]; // Negates the single input
}

// Function to create a new gate
Gate* create_gate(int type, const char* name) {
    Gate* new_gate = (Gate*)calloc(1, sizeof(Gate)); // Allocate memory for the gate
    if (!new_gate) return NULL; // Return NULL if allocation fails

    new_gate->type = type; // Set the gate type
    strncpy(new_gate->name, name, MAX_NAME - 1); // Copy the name, ensuring it doesn't exceed the limit
    new_gate->name[MAX_NAME - 1] = '\0'; // Ensure the name string is null-terminated

    // Assign the characteristic function based on the gate type
    switch (type) {
        case AND_GATE:
            new_gate->characteristic_function = and_function;
            break;
        case OR_GATE:
            new_gate->characteristic_function = or_function;
            break;
        case NOT_GATE:
            new_gate->characteristic_function = not_function;
            break;
        default:
            new_gate->characteristic_function = NULL; // No characteristic function for other types
    }

    return new_gate;
}

// Function to find a gate by its name in the arrays of gates
Gate* find_gate(Gate** input_gates, int input_count,
                Gate** output_gates, int output_count,
                Gate** other_gates, int other_count,
                const char* name) {
    // Search in input gates
    for (int i = 0; i < input_count; i++) {
        if (input_gates[i] && strcmp(input_gates[i]->name, name) == 0) {
            return input_gates[i];
        }
    }

    // Search in output gates
    for (int i = 0; i < output_count; i++) {
        if (output_gates[i] && strcmp(output_gates[i]->name, name) == 0) {
            return output_gates[i];
        }
    }

    // Search in other gates
    for (int i = 0; i < other_count; i++) {
        if (other_gates[i] && strcmp(other_gates[i]->name, name) == 0) {
            return other_gates[i];
        }
    }

    return NULL; // Gate not found
}

// Function to create a connection between two gates
int create_connection(Gate* from_gate, Gate* to_gate) {
    if (!from_gate || !to_gate || to_gate->number_of_inputs >= MAX_INPUTS) {
        return 0; // Connection cannot be created if inputs are invalid or maximum inputs reached
    }

    // Check if the connection already exists
    for (int i = 0; i < to_gate->number_of_inputs; i++) {
        if (to_gate->input_gates[i] == from_gate) {
            return 0; // Connection already exists
        }
    }

    // Add the connection
    to_gate->input_gates[to_gate->number_of_inputs++] = from_gate;
    return 1; // Connection created successfully
}

// Function to evaluate a gate
int evaluate_gate(Gate* g) {
    if (!g) return 0; // Return 0 if the gate is NULL
    if (g->evaluated) return g->output; // Return the output if already evaluated

    g->evaluated = 1; // Mark the gate as evaluated

    // Evaluate the gate based on its type
    switch (g->type) {
        case INPUT_GATE:
            return g->output; // Input gate's output is its own output

        case OUTPUT_GATE:
            if (g->number_of_inputs > 0) {
                g->output = evaluate_gate(g->input_gates[0]); // Evaluate the first input gate
            }
            break;

        case FLIPFLOP_GATE:
            if (g->number_of_inputs > 0) {
                int input = evaluate_gate(g->input_gates[0]); // Evaluate the input gate
                if (input == 0) {
                    g->output = g->former_out; // Maintain previous output if input is 0
                } else {
                    g->output = !g->former_out; // Toggle output if input is 1
                }
                g->former_out = g->output; // Update the former output
            }
            break;

        default:
            if (g->characteristic_function && g->number_of_inputs > 0) {
                int inputs[MAX_INPUTS];
                for (int i = 0; i < g->number_of_inputs; i++) {
                    inputs[i] = evaluate_gate(g->input_gates[i]); // Evaluate each input gate
                }
                g->output = g->characteristic_function(inputs, g->number_of_inputs); // Calculate the output
            }
    }

    return g->output; // Return the evaluated output
}

// Function to reset the evaluation flags for all gates
void reset_evaluation_flags(Gate** gates, int count) {
    if (!gates) return; // Return if the gates array is NULL
    for (int i = 0; i < count; i++) {
        if (gates[i]) {
            gates[i]->evaluated = 0; // Reset the evaluation flag for each gate
        }
    }
}

// Function to clean up (free) the memory allocated for gates
void cleanup_gates(Gate** gates, int count) {
    if (!gates) return; // Return if the gates array is NULL
    for (int i = 0; i < count; i++) {
        free(gates[i]); // Free each gate
    }
    free(gates); // Free the array of gates
}

// Function to resize the gate array when capacity is exceeded
Gate** resize_gate_array(Gate** gates, int* capacity) {
    int new_capacity = *capacity * 2; // Double the current capacity
    Gate** new_gates = realloc(gates, new_capacity * sizeof(Gate*)); // Reallocate memory
    if (!new_gates) return NULL; // Return NULL if allocation fails

    // Initialize new elements to NULL
    for (int i = *capacity; i < new_capacity; i++) {
        new_gates[i] = NULL;
    }

    *capacity = new_capacity; // Update the capacity
    return new_gates; // Return the resized array
}

int main() {
    // Open the circuit file
    FILE *circuit_file = fopen("circuit.txt", "r");
    if (!circuit_file) {
        printf("Error opening circuit file\n");
        return 1;
    }

    // Initialize gate arrays and their capacities
    int capacity = INITIAL_CAPACITY;
    Gate** input_gates = calloc(capacity, sizeof(Gate*));
    Gate** output_gates = calloc(capacity, sizeof(Gate*));
    Gate** other_gates = calloc(capacity, sizeof(Gate*));

    if (!input_gates || !output_gates || !other_gates) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int input_count = 0, output_count = 0, other_count = 0;
    char line[256];

    // Read the circuit file line by line
    while (fgets(line, sizeof(line), circuit_file)) {
        char cmd[20], type_str[20], name[20];
        if (sscanf(line, "%s", cmd) != 1) continue;

        if (strcmp(cmd, "GATE") == 0) {
            if (sscanf(line, "%s %s %s", cmd, type_str, name) != 3) continue;

            int type;
            if (strcmp(type_str, "INPUT") == 0) type = INPUT_GATE;
            else if (strcmp(type_str, "OUTPUT") == 0) type = OUTPUT_GATE;
            else if (strcmp(type_str, "AND") == 0) type = AND_GATE;
            else if (strcmp(type_str, "OR") == 0) type = OR_GATE;
            else if (strcmp(type_str, "NOT") == 0) type = NOT_GATE;
            else if (strcmp(type_str, "FLIPFLOP") == 0) type = FLIPFLOP_GATE;
            else continue;

            Gate* new_gate = create_gate(type, name);
            if (!new_gate) continue;

            Gate** target_array;
            int* count;

            // Determine which array to add the gate to based on its type
            switch (type) {
                case INPUT_GATE:
                    target_array = input_gates;
                    count = &input_count;
                    break;
                case OUTPUT_GATE:
                    target_array = output_gates;
                    count = &output_count;
                    break;
                default:
                    target_array = other_gates;
                    count = &other_count;
            }

            // Resize the array if the capacity is exceeded
            if (*count >= capacity) {
                Gate** new_array = resize_gate_array(target_array, &capacity);
                if (!new_array) {
                    free(new_gate);
                    continue;
                }
                if (target_array == input_gates) input_gates = new_array;
                else if (target_array == output_gates) output_gates = new_array;
                else other_gates = new_array;
            }

            target_array[(*count)++] = new_gate; // Add the new gate to the array

        } else if (strcmp(cmd, "CONNECTION") == 0) {
            char from_name[20], to_name[20];
            if (sscanf(line, "%s %s %s", cmd, from_name, to_name) != 3) continue;

            Gate* from_gate = find_gate(input_gates, input_count,
                                      output_gates, output_count,
                                      other_gates, other_count,
                                      from_name);

            Gate* to_gate = find_gate(input_gates, input_count,
                                    output_gates, output_count,
                                    other_gates, other_count,
                                    to_name);

            if (from_gate && to_gate) {
                create_connection(from_gate, to_gate);
            }
        }
    }

    fclose(circuit_file);

    // Open the input file
    FILE *input_file = fopen("input.txt", "r");
    if (!input_file) {
        printf("Error opening input file\n");
        cleanup_gates(input_gates, input_count);
        cleanup_gates(output_gates, output_count);
        cleanup_gates(other_gates, other_count);
        return 1;
    }

    // Read the input file line by line
    while (fgets(line, sizeof(line), input_file)) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character

        reset_evaluation_flags(input_gates, input_count);
        reset_evaluation_flags(output_gates, output_count);
        reset_evaluation_flags(other_gates, other_count);

        // Assign values to input gates
        for (int i = 0; i < input_count && line[i] != '\0'; i++) {
            input_gates[i]->output = (line[i] == '1') ? 1 : 0;
        }

        // Evaluate and print the outputs of output gates
        for (int i = 0; i < output_count; i++) {
            printf("%d", evaluate_gate(output_gates[i]));
        }
        printf("\n");
    }

    fclose(input_file);
    cleanup_gates(input_gates, input_count);
    cleanup_gates(output_gates, output_count);
    cleanup_gates(other_gates, other_count);

    return 0;
}

