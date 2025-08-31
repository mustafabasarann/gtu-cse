#include <iostream>
#include <string>
using namespace std;
 
class Student {
public:
    Student();
    ~Student();
    void InputData();
    void OutputData();
    void ResetClasses();
    Student& operator=(const Student& rightSide);
 
private:
    string name;
    int numClasses;
    string* classList;
    void res();
};
 
// Constructor
Student::Student() {
    name = "";
    numClasses = 0;
    classList = nullptr;
}
 
// Destructor
Student::~Student() {
    res();
}
 
// Helper to release memory
void Student::res() {
    if (classList != nullptr) {
        delete[] classList;
        classList = nullptr;
    }
}
 
// Input data from user
void Student::InputData() {
    res(); // temizle eski verileri
 
    cout << "Enter student name: ";
    getline(cin, name);
 
    cout << "Enter number of classes: ";
    cin >> numClasses;
    cin.ignore(); // cin >> sonrası newline temizleme
 
    if (numClasses > 0) {
        classList = new string[numClasses];
        for (int i = 0; i < numClasses; i++) {
            cout << "Enter name of class " << i + 1 << ": ";
            getline(cin, classList[i]);
        }
    }
}
 
// Output data to screen
void Student::OutputData() {
    cout << "Student name: " << name << endl;
    cout << "Number of classes: " << numClasses << endl;
    if (numClasses > 0 && classList != nullptr) {
        for (int i = 0; i < numClasses; i++) {
            cout << "- " << classList[i] << endl;
        }
    }
}
 
// Reset classes
void Student::ResetClasses() {
    res();
    numClasses = 0;
}
 
// Assignment operator
Student& Student::operator=(const Student& rightSide) {
    if (this != &rightSide) {
        res(); // mevcut verileri temizle
        name = rightSide.name;
        numClasses = rightSide.numClasses;
        if (numClasses > 0) {
            classList = new string[numClasses];
            for (int i = 0; i < numClasses; i++) {
                classList[i] = rightSide.classList[i];
            }
        } else {
            classList = nullptr;
        }
    }
    return *this;
}
 
// MAIN
int main() {
    Student s1, s2;
 
    s1.InputData(); // Input data for student 1
    cout << "Student 1's data:" << endl;
    s1.OutputData();
    cout << endl;
 
    s2 = s1; // Assign s1 to s2
    cout << "Student 2's data after assignment from student 1:" << endl;
    s2.OutputData();
    cout << endl;
 
    s1.ResetClasses(); // Reset s1
    cout << "Student 1's data after reset:" << endl;
    s1.OutputData();
    cout << endl;
 
    cout << "Student 2's data, should still have original classes:" << endl;
    s2.OutputData();
    cout << endl;
 
    return 0;
}
