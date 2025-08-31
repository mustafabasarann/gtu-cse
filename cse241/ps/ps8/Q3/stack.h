//stack.h
//
//A template-based class for a stack based on StackSavitch
// from chapter 17.2 of Absolute C++.

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
using namespace std;

class PopEmptyStackException
{
public:
    PopEmptyStackException() {}
    string getMessage() const { return "Attempted to pop from an empty stack!"; }
};

template<class T>
class Stack
{
public:
    Stack();

    Stack(const Stack<T>& aStack);

    ~Stack();

    void push(T stackElement);

    T pop();

    bool isEmpty() const;

    void makeEmpty();

    Stack<T>& operator=(const Stack<T>& rightSide);


private:
    T* stackArray;
    int maxSize;
    int topIndex;
    void capacity(int newCapacity);
};

template<class T>
Stack<T>::Stack() : maxSize(10), topIndex(-1)
{
    stackArray = new T[maxSize];
}

template<class T>
Stack<T>::Stack(const Stack<T>& aStack)
    : maxSize(aStack.maxSize), topIndex(aStack.topIndex)
{
    stackArray = new T[maxSize];
    for (int i = 0; i <= topIndex; i++)
        stackArray[i] = aStack.stackArray[i];
}

template<class T>
Stack<T>::~Stack()
{
    delete[] stackArray;
}

template<class T>
void Stack<T>::push(T stackElement)
{
    if (topIndex >= maxSize - 1)
        capacity(2 * maxSize);
    
    topIndex++;
    stackArray[topIndex] = stackElement;
}

template<class T>
T Stack<T>::pop()
{
    if (isEmpty())
        throw PopEmptyStackException();
        
    T result = stackArray[topIndex];
    topIndex--;
    return result;
}

template<class T>
bool Stack<T>::isEmpty() const
{
    return (topIndex == -1);
}

template<class T>
void Stack<T>::makeEmpty()
{
    topIndex = -1;
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rightSide)
{
    if (this == &rightSide)
        return *this;
        
    if (maxSize != rightSide.maxSize)
    {
        delete[] stackArray;
        maxSize = rightSide.maxSize;
        stackArray = new T[maxSize];
    }
    
    topIndex = rightSide.topIndex;
    for (int i = 0; i <= topIndex; i++)
        stackArray[i] = rightSide.stackArray[i];
        
    return *this;
}

template<class T>
void Stack<T>::capacity(int newCapacity)
{
    if (newCapacity <= maxSize)
        return;
        
    T* temp = new T[newCapacity];
    for (int i = 0; i <= topIndex; i++)
        temp[i] = stackArray[i];
        
    delete[] stackArray;
    stackArray = temp;
    maxSize = newCapacity;
}

#endif 