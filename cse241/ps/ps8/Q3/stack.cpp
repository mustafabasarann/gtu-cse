#include <iostream>
#include "stack.h"

using namespace std;

// ==============================
//         main function
// ==============================

int main()
{
    Stack<int> s;
    s.push(4);
    s.push(10);
    s.push(54);

    try
    {
        cout << s.pop() << endl;
        cout << s.pop() << endl;
        cout << s.pop() << endl; // Buraya kadar normal
        cout << s.pop() << endl; // This will throw an exception
    }
    catch (PopEmptyStackException)
    {
        cout << "Tried to pop an empty stack!" << endl;
    }

    return 0;
}