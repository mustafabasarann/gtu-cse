#ifndef SET_H
#define SET_H

#include <vector>
using namespace std;

template <class T>
class Set {
public:
    Set();
    void add(T newItem);
    int getSize();
    T* getArray(); 

private:
    vector<T> data;
};

#include "set.cpp" 

#endif

