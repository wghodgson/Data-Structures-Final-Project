#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "stackADT.h"
#include "node.h"
#include <stdexcept>
template <class t>
class linkedStack : public stackADT<t>
{
public:
    linkedStack(int = 100);
    linkedStack(const linkedStack<t> &);
    const linkedStack<t> &operator=(const linkedStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t top() const;
    t pop();
    ~linkedStack();

private:
    void copyStack(const linkedStack<t> &);
    node<t> *stackTop;
    int count;
    int maxCount;
};

template <class t>
linkedStack<t>::linkedStack(int)
{
    this->stackTop = nullptr;
    this->count = 0;
}

template <class t>
linkedStack<t>::linkedStack(const linkedStack<t> &othStack)
{
    stackTop = nullptr;
    count = 0;
    copyStack(othStack);
}

template <class t>
const linkedStack<t> &linkedStack<t>::operator=(const linkedStack<t> &othStack)
{
    if (this != &othStack)
    {
        copyStack(othStack);
    }
    return *this;
}

template <class t>
bool linkedStack<t>::isEmptyStack() const
{
    return stackTop == nullptr;
}

template <class t>
bool linkedStack<t>::isFullStack() const
{
    return false;
}

template <class t>
void linkedStack<t>::copyStack(const linkedStack<t> &othStack)
{
    node<t> *newNode;
    node<t> *current;
    node<t> *last;
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (othStack.isEmptyStack())
    {
        this->stackTop = nullptr;
        count = 0;
    }
    else
    {
        current = othStack.stackTop;
        this->stackTop = new node<t>;
        this->stackTop->data = new t(*(current->data));
        this->stackTop->next = nullptr; // Node uses next not link
        last = this->stackTop;
        current = current->next; // Node uses next not link
        while (current != nullptr)
        {
            newNode = new node<t>;
            newNode->data = new t(*(current->data));
            newNode->next = nullptr; // Node uses next not link
            last->next = newNode; // Node uses next not link
            last = newNode;
            current = current->next; // Node uses next not link
        }
        this->count = othStack.count;
    }
}

template <class t>
void linkedStack<t>::initializeStack()
{
    node<t> *temp;
    while (stackTop != nullptr)
    {
        temp = stackTop;
        stackTop = stackTop->next; // Node uses next not link
        delete temp;
    }
    count = 0;
}

template <class t>
linkedStack<t>::~linkedStack()
{
    initializeStack();
}

template <class t>
void linkedStack<t>::push(const t &newItem)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newItem);
    newNode->next = stackTop; // Node uses next not link
    stackTop = newNode;
    count++;
}

template <class t>
t linkedStack<t>::pop()
{
    node<t> *temp;
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack underflow. Cannot remove from an empty stack.");
    }
    t copyT(*(stackTop->data));
    temp = stackTop;
    stackTop = stackTop->next; // Node uses next not link
    delete temp;
    count--;
    return copyT;
}

template <class t>
t linkedStack<t>::top() const
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return *(stackTop->data);
}

#endif