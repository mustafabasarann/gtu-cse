#ifndef SET_CPP
#define SET_CPP

#include "set.h"

template <class T>
Set<T>::Set() {}

template <class T>
void Set<T>::add(T newItem) {
    for (const auto& item : data) {
        if (item == newItem) return; 
    }
    data.push_back(newItem);
}

template <class T>
int Set<T>::getSize() {
    return data.size();
}

template <class T>
T* Set<T>::getArray() {
    T* array = new T[data.size()];
    for (size_t i = 0; i < data.size(); ++i) {
        array[i] = data[i];
    }
    return array;
}
#include <iostream>

#include "set.h"
 
using namespace std;
 
int main()

{

    Set<int> s1;

    Set<string> s2;

    int *intArray = NULL;

    string *stringArray = NULL;

    int i;
 
    s1.add(10);

    s1.add(20);

    s1.add(15);

    s1.add(20);

    intArray = s1.getArray();

    cout << "Set one has " << s1.getSize() << " items. Here they are: " << endl;
 
    for (int i = 0; i < s1.getSize(); ++i)

    {

        cout << intArray[i] << endl;

    }
 
    if (intArray != NULL)

        delete[] intArray;
 
    s2.add("butter");

    s2.add("hamburgers");

    s2.add("pizza");

    s2.add("hotdogs");

    s2.add("pizza");
 
    stringArray = s2.getArray();
 
    cout << " Set two has " << s2.getSize() << " items. Here they are: " << endl;
 
    for (int i = 0; i < s2.getSize(); ++i)

    {

        cout << stringArray[i] << " ";

    }
 
    if (stringArray != NULL)

        delete[] stringArray;
 
    return 0;

}
 

#endif

