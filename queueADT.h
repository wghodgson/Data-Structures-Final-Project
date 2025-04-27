#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdexcept>

template <class t>
class queueADT
{
    virtual bool isEmptyQueue() const = 0;
    virtual bool isFullQueue() const = 0;
    virtual void initializeQueue() = 0;
    virtual t front() const = 0;
    virtual t back() const = 0;
    virtual void enqueue(const t &queueElement) = 0;
    virtual t dequeue() = 0;
};

#endif