#ifndef LINKEDI_H
#define LINKEDI_H
#include "node.h"

template <class t>
class linkedListIterator
{
public:
    linkedListIterator();
    linkedListIterator(node<t> *);
    t &operator*();
    linkedListIterator<t> operator++();
    bool operator==(const linkedListIterator<t> &) const;
    bool operator!=(const linkedListIterator<t> &) const;
    linkedListIterator<t> operator+(int x);

private:
    node<t> *current;
};
template <class t>
linkedListIterator<t>::linkedListIterator()
{
    current = nullptr;
}
template <class t>
linkedListIterator<t>::linkedListIterator(node<t> *ptr)
{
    current = ptr;
}
template <class t>
t &linkedListIterator<t>::operator*()
{
    if (current != nullptr)
    {
        return *(current->data);
    }
    else
    {
        throw std::runtime_error("Nullptr in iterator");
    }
}
template <class t>
linkedListIterator<t> linkedListIterator<t>::operator++()
{
    if (current != nullptr)
    {
        current = current->next;
    }
    return *this;
}

template <class t>
bool linkedListIterator<t>::operator==(const linkedListIterator<t> &right) const
{

    return (current == right.current);
}

template <class t>
bool linkedListIterator<t>::operator!=(const linkedListIterator<t> &right) const
{
    return (current != right.current);
}

template <class t>
linkedListIterator<t> linkedListIterator<t>::operator+(int x)
{
    node<t> *temp = current;
    for (int i = 0; i < x && temp != nullptr; i++)
    {
        temp = temp->next;
    }
    return linkedListIterator<t>(temp);
}

#endif