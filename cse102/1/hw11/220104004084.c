#include "customDict.h"


int main() {

    CustomDict* dict = create_dict();

    if (!read_csv(dict, "data.csv")) {
        printf("CSV dosyası okunamadı.\n");
        return 1;
    }

    print_dict(dict);
    printf("*****************************************************************\n");
    Value newValue;
    int newValues[] = {10};
    newValue.i = (int*)malloc(sizeof(int) * 1);
    newValue.i[0] = newValues[0];
    set_value(dict, " age", &newValue, 'i', 1);
    sort_dict(dict);
    print_dict(dict);
     printf("*****************************************************************\n");
    Value value1;
    value1.i = (int*)malloc(sizeof(int) * 3);
    value1.i[0] = 1;
    value1.i[1] = 2;
    value1.i[2] = 3;
    add_item(dict, " age", &value1, 'i', 3);
   
    sort_dict(dict);
    print_dict(dict);
    printf("*****************************************************************\n");
    
    delete_item(dict," age");
        sort_dict(dict);
    print_dict(dict);
    
    free_dict(dict);
    }

