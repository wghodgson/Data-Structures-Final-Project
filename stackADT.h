#ifndef STACKADT_H
#define STACKADT_H

template <class t>
class stackADT
{
public:
    virtual void initializeStack() = 0;
    virtual bool isFullStack() const = 0;
    virtual bool isEmptyStack() const = 0;
    virtual void push(const t &) = 0;
    virtual t top() const = 0;
    virtual t pop() = 0;
};

#endif