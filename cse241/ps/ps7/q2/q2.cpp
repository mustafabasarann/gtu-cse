#include <iostream>

#include <string>

using namespace std;

template<class T, class V>

class Pair {

public:

    Pair() : first(T()), second(V()) {}

    Pair(T firstValue, V secondValue) : first(firstValue), second(secondValue) {}
 
    void setFirst(T newValue) {

        first = newValue;

    }
 
    void setSecond(V newValue) {

        second = newValue;

    }
 
    T getFirst() const {

        return first;

    }
 
    V getSecond() const {

        return second;

    }
 
private:

    T first;

    V second;

};
 
int main()

{

    Pair<char, char> p('A', 'B');

    cout << "First is " << p.getFirst() << endl;

    p.setFirst('Z');

    cout << "First changed to " << p.getFirst() << endl;

    cout << "The pair is: " << p.getFirst() << ", " << p.getSecond()
<< endl;
 
    Pair<int, string> p2(34, "Bill");

    Pair<string, int> p3("Bill", 34);

    cout << "The pair is: " << p2.getFirst() << ", " << p2.getSecond()
<< endl;
 
    return 0;

}

 
