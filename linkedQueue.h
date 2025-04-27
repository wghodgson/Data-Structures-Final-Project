#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
#include "queueADT.h"
#include "node.h"

template <class t>
class linkedQueue : public queueADT<t>
{
public:
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    t front() const;
    t back() const;
    void enqueue(const t &queueElement);
    t dequeue();
    linkedQueue();
    linkedQueue(const linkedQueue<t> &);
    const linkedQueue<t> &operator=(const linkedQueue<t> &);
    ~linkedQueue();

protected:
    node<t> *queueFront;
    node<t> *queueRear;
    void copyQueue(const linkedQueue<t> &);
};

template <class t>
bool linkedQueue<t>::isEmptyQueue() const
{
    return this->queueFront == nullptr;
}

template <class t>
bool linkedQueue<t>::isFullQueue() const
{
    return false;
}

template <class t>
void linkedQueue<t>::initializeQueue()
{
    node<t> *current;
    while (!isEmptyQueue())
    {
        current = this->queueFront;
        this->queueFront = this->queueFront->next;
        delete current;
        current = nullptr;
    }
    this->queueRear = nullptr;
}

template <class t>
t linkedQueue<t>::front() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot view an item in an empty queue.");
    }
    return *(queueFront->data);
}

template <class t>
t linkedQueue<t>::back() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot view an item in an empty queue.");
    }
    return *(queueRear->data);
}

template <class t>
void linkedQueue<t>::enqueue(const t &queueElement)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(queueElement);
    newNode->next = nullptr;
    if (this->isEmptyQueue())
    {
        this->queueFront = newNode;
        this->queueRear = newNode;
    }
    else
    {
        this->queueRear->next = newNode;
        this->queueRear = newNode;
    }
}

template <class t>
t linkedQueue<t>::dequeue()
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot remove from an empty queue.");
    }
    node<t> *temp;
    temp = this->queueFront;
    this->queueFront = this->queueFront->next;
    t returnItem(*(temp->data));
    delete temp;
    return returnItem;
}

template <class t>
linkedQueue<t>::linkedQueue()
{
    this->queueFront = nullptr;
    this->queueRear = nullptr;
}

template <class t>
linkedQueue<t>::linkedQueue(const linkedQueue<t> &othQueue)
{
    this->queueFront = nullptr;
    this->queueRear = nullptr;
    copyQueue(othQueue);
}

template <class t>
void linkedQueue<t>::copyQueue(const linkedQueue<t> &othQueue)
{
    this->initializeQueue();
    node<t> *current;
    current = othQueue.queueFront;
    while (current != nullptr)
    {
        this->enqueue(*(current->data));
        current = current->next;
    }
}

template <class t>
const linkedQueue<t> &linkedQueue<t>::operator=(const linkedQueue<t> &othQueue)
{
    if (this != &othQueue)
    {
        copyQueue(othQueue);
    }
    return *this;
}

template <class t>
linkedQueue<t>::~linkedQueue()
{
    initializeQueue();
}

#endif