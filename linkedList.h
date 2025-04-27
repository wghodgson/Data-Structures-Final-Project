#ifndef LINKED_H
#define LINKED_H

#include <iostream>
#include <stdexcept>
#include "node.h"
#include "linkedListIterator.h"

template <class t>
class linkedListType
{
public:
    linkedListType();
    linkedListType(const linkedListType<t> &otherList);
    const linkedListType<t> &operator=(const linkedListType<t> &);
    ~linkedListType();
    void destroyList();
    bool isEmptyList() const;
    int length() const;
    t front() const;
    t back() const;
    virtual void insert(const t &newInfo) = 0;
    virtual void deleteNode(const t &deleteItem) = 0;
    virtual bool search(const t &searchItem) const = 0;
    linkedListIterator<t> begin();
    linkedListIterator<t> end();
    void print(std::ostream &, std::string = " ") const;
    // friend std::ostream &operator<<(std::ostream &, const linkedListType<t> &);

protected:
    node<t> *head;
    node<t> *tail;
    int count;

private:
    void copyList(const linkedListType<t> &otherList);
};

template <class t>
linkedListType<t>::linkedListType()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class t>
linkedListType<t>::linkedListType(const linkedListType<t> &otherList)
{
    head = nullptr;
    tail = nullptr;
    count = 0;
    copyList(otherList);
}

template <class t>
const linkedListType<t> &linkedListType<t>::operator=(const linkedListType<t> &otherList)
{
    if (this != &otherList) // avoid self-copy
    {
        copyList(otherList);
    }
    return *this;
}

template <class t>
void linkedListType<t>::copyList(const linkedListType<t> &fromList)
{
    node<t> *newNode;
    node<t> *current;
    if (!isEmptyList())
    {
        destroyList();
    }
    if (fromList.isEmptyList())
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    else
    {
        current = fromList.head;
        count = fromList.count;
        this->head = new node<t>;
        // don't do this shallow copy this->head->data = fromList.head.data;
        this->head->data = new t(*(current->data));
        this->head->next = nullptr;
        this->tail = this->head;
        current = current->next;
        while (current != nullptr)
        {
            newNode = new node<t>;
            newNode->data = new t(*(current->data));
            newNode->next = nullptr;
            tail->next = newNode;
            tail = tail->next;
            current = current->next;
        }
    }
}

template <class t>
linkedListType<t>::~linkedListType()
{
    destroyList();
}

template <class t>
void linkedListType<t>::destroyList()
{
    if (!isEmptyList())
    {
        node<t> *temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
}

template <class t>
bool linkedListType<t>::isEmptyList() const
{
    return count == 0 || head == nullptr;
}

template <class t>
t linkedListType<t>::front() const
{
    if (isEmptyList())
    {
        throw std::out_of_range("Cannot get first item of an empty list");
    }
    return *(head->data);
}

template <class t>
t linkedListType<t>::back() const
{
    if (isEmptyList())
    {
        throw std::out_of_range("Cannot get last item of an empty list");
    }
    return *(tail->data);
}

template <class t>
int linkedListType<t>::length() const
{
    return count;
}

template <class t>
std::ostream &operator<<(std::ostream &out, const linkedListType<t> &list)
{
    if (!list.isEmptyList())
    {
        node<t> *current;
        current = list.head;
        while (current != nullptr)
        {
            out << *(current->data) << std::endl;
            current = current->next;
        }
    }
    return out;
}

template <class t>
linkedListIterator<t> linkedListType<t>::begin()
{
    return linkedListIterator<t>(head);
}

template <class t>
linkedListIterator<t> linkedListType<t>::end()
{
    return linkedListIterator<t>();
}

template <class t>
void linkedListType<t>::print(std::ostream &out, std::string sep) const
{
    if (!isEmptyList())
    {
        node<t> *current;
        current = head;
        while (current != nullptr)
        {
            out << *(current->data) << sep;
            current = current->next;
        }
    }
}

#endif