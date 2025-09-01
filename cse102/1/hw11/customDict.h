#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    int* i;
    float* f;
    double* d;
    char* c;
} Value;

typedef struct {
    char *key;
    Value value;
    char type;
    int size;
} Item;

typedef struct {
    Item* items;
    int capacity;
    int size;
} CustomDict;

char* my_strdup(const char* src) {
    size_t len = strlen(src) + 1;
    char* dst = (char*)malloc(len);
    if (dst) {
        strcpy(dst, src);
    }
    return dst;
}

CustomDict* create_dict() {
    CustomDict* dict = (CustomDict*)malloc(sizeof(CustomDict));
    dict->items = NULL;
    dict->capacity = 0;
    dict->size = 0;
    return dict;
}

void add_item(CustomDict* dict, char* key, Value* value, char type, int size) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            dict->items[i].value = *value;
            dict->items[i].size = size; 
            dict->items[i].type = type; 
            return;
        }
    }
    if (dict->size == dict->capacity) {
        dict->capacity = dict->capacity == 0 ? 1 : dict->capacity * 2;
        dict->items = (Item*)realloc(dict->items, dict->capacity * sizeof(Item));
    }

    dict->items[dict->size].key = my_strdup(key);
    dict->items[dict->size].value = *value;
    dict->items[dict->size].type = type;
    dict->items[dict->size].size = size; 
    dict->size++;
}

void delete_item(CustomDict* dict, char* key) {
    int i, j;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
      
            free(dict->items[i].key);
            if (dict->items[i].type == 'i') {
                free(dict->items[i].value.i);
            } else if (dict->items[i].type == 'f') {
                free(dict->items[i].value.f);
            } else if (dict->items[i].type == 'd') {
                free(dict->items[i].value.d);
            } else if (dict->items[i].type == 'c') {
                free(dict->items[i].value.c);
            }

       
            for (j = i; j < dict->size - 1; j++) {
                dict->items[j] = dict->items[j + 1];
            }

            dict->size--;
            return;
        }
    }
    printf("Invalid Key: %s\n", key);
}

void sort_dict(CustomDict* dict){
    int i, j;
    for (i = 0; i < dict->size; i++) {
        for (j = 0; j < dict->size; j++) {
            if (strcmp(dict->items[i].key, dict->items[j].key) < 0) {
                Item temp = dict->items[i];
                dict->items[i] = dict->items[j];
                dict->items[j] = temp;
            }
        }
    }
}

int read_csv(CustomDict* dict, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }
    char* token;
    char line[1024];
    
    while (fgets(line, sizeof(line), file)) {
        char* type = strtok(line, ",");
        char* key = strtok(NULL, ",");
        Value value;
        int size = 0;

        if (strcmp(type, "int") == 0) {
            value.i = (int*)malloc(sizeof(int) * 100);
            while ((token = strtok(NULL, ","))) {
                value.i[size++] = atoi(token);
            }
            add_item(dict, key, &value, 'i', size);
        } else if (strcmp(type, "float") == 0) {
            value.f = (float*)malloc(sizeof(float) * 100);
            while ((token = strtok(NULL, ","))) {
                value.f[size++] = atof(token);
            }
            add_item(dict, key, &value, 'f', size);
        } else if (strcmp(type, "double") == 0) {
            value.d = (double*)malloc(sizeof(double) * 100);
            while ((token = strtok(NULL, ","))) {
                value.d[size++] = atof(token);
            }
            add_item(dict, key, &value, 'd', size);
        } else if (strcmp(type, "char") == 0) {
            value.c = (char*)malloc(sizeof(char) * 100);
            while ((token = strtok(NULL, ","))) {
                value.c[size++] = token[0];
            }
            add_item(dict, key, &value, 'c', size);
        }
    }

    fclose(file);
    return 1;
}

void print_dict(CustomDict* dict) {
    int i, j;
    for (i = 0; i < dict->size; i++) {
        if (dict->items[i].type == 'i') {
            for (j = 0; j < dict->items[i].size; j++) {
                printf("Key: %s    Value: %d\n", dict->items[i].key, dict->items[i].value.i[j]);
            }
        } else if (dict->items[i].type == 'f') {
            for (j = 0; j < dict->items[i].size; j++) {
                printf("Key: %s    Value: %f\n", dict->items[i].key, dict->items[i].value.f[j]);
            }
        } else if (dict->items[i].type == 'd') {
            for (j = 0; j < dict->items[i].size; j++) {
                printf("Key: %s    Value: %lf\n", dict->items[i].key, dict->items[i].value.d[j]);
            }
        } else if (dict->items[i].type == 'c') {
            for (j = 0; j < dict->items[i].size; j++) {
                printf("Key: %s    Value: %c\n", dict->items[i].key, dict->items[i].value.c[j]);
            }
        }
    }

}

void set_value(CustomDict* dict, char* key, Value* value, char type, int size) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            if (dict->items[i].type == 'i') {
                free(dict->items[i].value.i);
            } else if (dict->items[i].type == 'f') {
                free(dict->items[i].value.f);
            } else if (dict->items[i].type == 'd') {
                free(dict->items[i].value.d);
            } else if (dict->items[i].type == 'c') {
                free(dict->items[i].value.c);
            }
            dict->items[i].value = *value;
            dict->items[i].type = type;
            dict->items[i].size = size;
            return;
        }
    }
    printf("Invalid Key: %s\n", key);
}

void free_dict(CustomDict* dict) {
    int i;
    for (i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        if (dict->items[i].type == 'i') {
            free(dict->items[i].value.i);
        }
        if (dict->items[i].type == 'f') {
            free(dict->items[i].value.f);
        }
        if (dict->items[i].type == 'd') {
            free(dict->items[i].value.d);
        }
        if (dict->items[i].type == 'c') {
            free(dict->items[i].value.c);
        }
    }
    free(dict->items);
    free(dict);
}



