#include "PFArrayD.h"
#include <iostream>
using namespace std;

OutOfRange::OutOfRange(string thisMessage, int thisIndex) 
    : message(thisMessage), index(thisIndex) {}

string OutOfRange::getMessage() const {
    return message;
}

int OutOfRange::getIndex() const {
    return index;
}

PFArrayD::PFArrayD() : capacity(50), used(0) {
    a = new double[capacity];
}

PFArrayD::PFArrayD(int capacityValue) : capacity(capacityValue), used(0) {
    if (capacity <= 0) {
        cout << "Capacity must be positive." << endl;
        exit(1);
    }
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaObject) 
    : capacity(pfaObject.capacity), used(pfaObject.used) {
    a = new double[capacity];
    for (int i = 0; i < used; i++) {
        a[i] = pfaObject.a[i];
    }
}

void PFArrayD::addElement(double element) {
    if (used >= capacity) {
        throw OutOfRange("Attempt to add element to a full array", -1);
    }
    a[used] = element;
    used++;
}

double& PFArrayD::operator[](int index) { 
    if (index < 0 || index >= used) {
        throw OutOfRange("out of range", index);
    }
    return a[index];
}

PFArrayD& PFArrayD::operator=(const PFArrayD& rightSide) {
    if (this == &rightSide) {
        return *this;
    }
    
    if (capacity != rightSide.capacity) {
        delete [] a;
        a = new double[rightSide.capacity];
        capacity = rightSide.capacity;
    }
    
    used = rightSide.used;
    for (int i = 0; i < used; i++) {
        a[i] = rightSide.a[i];
    }
    
    return *this;
}

PFArrayD::~PFArrayD() {
    delete [] a;
}