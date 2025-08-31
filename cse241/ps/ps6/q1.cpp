
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

class DynamicStringArray {
public:
    DynamicStringArray() {
        dynamicArray = nullptr;
        size = 0;
    }

    DynamicStringArray(const DynamicStringArray& otherObj) {
        size = otherObj.size;
        dynamicArray = new string[size];
        for (int i = 0; i < size; i++) {
            dynamicArray[i] = otherObj.dynamicArray[i];
        }
    }

    DynamicStringArray& operator=(const DynamicStringArray& rightSide) {
        if (this != &rightSide) {
            delete[] dynamicArray;
            size = rightSide.size;
            dynamicArray = new string[size];
            for (int i = 0; i < size; i++) {
                dynamicArray[i] = rightSide.dynamicArray[i];
            }
        }
        return *this;
    }

    ~DynamicStringArray() {
        delete[] dynamicArray;
    }

    void addEntry(string newEntry) {
        string* newArray = new string[size + 1];
        for (int i = 0; i < size; i++) {
            newArray[i] = dynamicArray[i];
        }
        newArray[size] = newEntry;
        delete[] dynamicArray;
        dynamicArray = newArray;
        size++;
    }

    bool deleteEntry(string newEntry) {
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (dynamicArray[i] == newEntry) {
                index = i;
                break;
            }
        }
        if (index == -1) return false;

        string* newArray = new string[size - 1];
        for (int i = 0, j = 0; i < size; i++) {
            if (i != index) {
                newArray[j++] = dynamicArray[i];
            }
        }
        delete[] dynamicArray;
        dynamicArray = newArray;
        size--;
        return true;
    }

    string getEntry(int index) {
        if (index < 0 || index >= size) return "";
        return dynamicArray[index];
    }

    int getSize() {
        return size;
    }

private:
    string* dynamicArray;
    int size;
};

// Main

int main()

{

    DynamicStringArray names;
 
    // List of names

    names.addEntry("Frank");

    names.addEntry("Wiggum");

    names.addEntry("Nahasapeemapetilon");

    names.addEntry("Quimby");

    names.addEntry("Flanders");
 
    cout << "List of names:" << endl;

    for (int i = 0; i < names.getSize(); i++)

        cout << names.getEntry(i) << endl;

    cout << endl;
 
    // Add and remove some names

    names.addEntry("Spuckler");

    cout << "After adding a name:" << endl;

    for (int i = 0; i < names.getSize(); i++)

        cout << names.getEntry(i) << endl;

    cout << endl;
 
    names.deleteEntry("Nahasapeemapetilon");

    cout << "After removing a name:" << endl;

    for (int i = 0; i < names.getSize(); i++)

        cout << names.getEntry(i) << endl;

    cout << endl;
 
    names.deleteEntry("Skinner");

    cout << "After removing a name that isn't on the list:" << endl;

    for (int i = 0; i < names.getSize(); i++)

        cout << names.getEntry(i) << endl;

    cout << endl;
 
    names.addEntry("Muntz");

    cout << "After adding another name:" << endl;

    for (int i = 0; i < names.getSize(); i++)

        cout << names.getEntry(i) << endl;

    cout << endl;
 
    // Remove all of the names by repeatedly deleting the last one

    while (names.getSize() > 0) {

        names.deleteEntry(names.getEntry(names.getSize() - 1));

    }
 
    cout << "After removing all of the names:" << endl;

    for (int i = 0; i < names.getSize(); i++)

        cout << names.getEntry(i) << endl;

    cout << endl;
 
    names.addEntry("Burns");

    cout << "After adding a name:" << endl;

    for (int i = 0; i < names.getSize(); i++)

        cout << names.getEntry(i) << endl;

    cout << endl;
 
    cout << "Testing copy constructor" << endl;

    DynamicStringArray names2(names);

    names.deleteEntry("Burns");

    cout << "Copied names:" << endl;

    for (int i = 0; i < names2.getSize(); i++)

        cout << names2.getEntry(i) << endl;

    cout << endl;
 
    cout << "Testing assignment" << endl;

    DynamicStringArray names3 = names2;

    names2.deleteEntry("Burns");

    cout << "Copied names:" << endl;

    for (int i = 0; i < names3.getSize(); i++)

        cout << names3.getEntry(i) << endl;

    cout << endl;
 
    cout << "Enter a character to exit." << endl;

    char wait;

    cin >> wait;

    return 0;

}
 
