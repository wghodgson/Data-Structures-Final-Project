#ifndef UNORDERED_H
#define UNORDERED_H
#include "linkedList.h"

template <class t>
class unorderedLinkedList : public linkedListType<t>
{
public:
    enum directionType
    {
        FORWARD,
        BACKWARD
    };
    unorderedLinkedList(directionType = FORWARD);
    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    bool search(const t &searchItem) const;
    t &operator[](int index);
    void insertionSort();
    void mergeSort();

private:
    directionType direction;
    void insertFirst(const t &newInfo);
    void insertLast(const t &newInfo);
    void recMergeSort(node<t> *&head);
    void divideList(node<t> *left, node<t> *&right);
    node<t> *mergeList(node<t> *left, node<t> *right);
};

template <class t>
unorderedLinkedList<t>::unorderedLinkedList(directionType d) : direction(d) {}

template <class t>
void unorderedLinkedList<t>::insert(const t &newData)
{
    if (direction == FORWARD)
    {
        insertLast(newData);
    }
    else
    {
        insertFirst(newData);
    }
}

template <class t>
void unorderedLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    node<t> *trailCurrent;
    bool found;
    if (this->isEmptyList())
    {
        throw std::out_of_range("Cannot delete from empty list");
    }
    else
    {
        if (*(this->head->data) == deleteItem)
        {
            current = this->head;
            this->head = this->head->next;
            this->count--;
            if (this->head == nullptr)
            {
                this->tail = nullptr;
            }
            delete current;
        }
        else
        {
            found = false;
            trailCurrent = this->head;
            current = this->head->next;
            while (current != nullptr && !found)
            {
                if (*(current->data) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->next;
                }
                else
                {
                    found = true;
                }
            }
            if (found)
            {
                trailCurrent->next = current->next;
                this->count--;
                if (this->tail == current)
                {
                    this->tail = trailCurrent;
                }
                delete current;
            }
            else
            {
                throw std::out_of_range("Item not found in list. Cannot delete");
            }
        }
    }
}

template <class t>
bool unorderedLinkedList<t>::search(const t &searchItem) const
{
    node<t> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->next;
        }
    }
    return found;
}

template <class t>
void unorderedLinkedList<t>::insertFirst(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->head->prev = newNode;
        newNode->next = this->head;
        this->head = newNode;
    }
    this->count++;
}

template <class t>
void unorderedLinkedList<t>::insertLast(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        newNode->prev = this->tail;
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->count++;
}

template <class t>
t &unorderedLinkedList<t>::operator[](int index)
{
    node<t> *current = this->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return *(current->data);
}

/* template <class t>
void unorderedLinkedList<t>::insertionSort()
{
    node<t> *firstOutOfOrder = this->head->next;
    while (firstOutOfOrder != nullptr)
    {
        if (*(firstOutOfOrder->data) < *(firstOutOfOrder->prev->data))
        {
            node<t> *temp = firstOutOfOrder;
            node<t> *locationBefore = firstOutOfOrder->prev;
            node<t> *locationAfter = firstOutOfOrder->next;
            firstOutOfOrder = firstOutOfOrder->prev;
            locationAfter->prev = locationBefore;
            locationBefore->next = locationAfter;
            do
            {
                locationBefore = locationBefore->prev;
                locationAfter = locationAfter->prev;

            } while (locationBefore != nullptr && *(temp->data) < *(locationBefore->data));
            temp->prev = locationBefore;
            temp->next = locationAfter;
            if (locationBefore == nullptr)
            {
                this->head = temp;
            }
        }
        firstOutOfOrder = firstOutOfOrder->next;
    }

     for (int firstOutOfOrder = 1; firstOutOfOrder < list.length(); ++firstOutOfOrder)
    {
        if (list[firstOutOfOrder] < list[firstOutOfOrder - 1])
        {
            t temp = list[firstOutOfOrder];
            int location = firstOutOfOrder;
            do
            {
                list[location] = list[location - 1];
                location--;
            } while (location > 0 && list[location - 1] > temp);
            list[location] = temp;
        }
    }
} */

template <class t>
void unorderedLinkedList<t>::mergeSort()
{
    recMergeSort(this->head);
    if (this->head == nullptr)
    {
        this->tail = nullptr;
    }
    else
    {
        this->tail = this->head;
        while (this->tail->next != nullptr)
        {
            this->tail = this->tail->next;
        }
    }
}

template <class t>
void unorderedLinkedList<t>::recMergeSort(node<t> *&head)
{
    node<t> *otherHead;
    if (head != nullptr)
    {
        if (head->next != nullptr)
        {
            divideList(head, otherHead);
            recMergeSort(head);
            recMergeSort(otherHead);
            head = mergeList(head, otherHead);
        }
    }
}

template <class t>
void unorderedLinkedList<t>::divideList(node<t> *left, node<t> *&right)
{
    node<t> *middle;
    node<t> *current;
    if (left == nullptr || left->next == nullptr)
    {
        right = nullptr;
    }
    else
    {
        middle = left;
        current = left->next;
        if (current != nullptr)
        {
            current = current->next;
        }
        while (current != nullptr)
        {
            middle = middle->next;
            current = current->next;
            if (current != nullptr)
            {
                current = current->next;
            }
        }
        right = middle->next;
        middle->next = nullptr;
    }
}

template <class t>
node<t> *unorderedLinkedList<t>::mergeList(node<t> *left, node<t> *right)
{
    node<t> *lastSmall;
    node<t> *newHead;
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;
    if (*(left->data) <= *(right->data))
    {
        newHead = left;
        left = left->next;
    }
    else
    {
        newHead = right;
        right = right->next;
    }
    lastSmall = newHead;
    while (left != nullptr && right != nullptr)
    {
        if (*(left->data) <= *(right->data))
        {
            lastSmall->next = left;

            left = left->next;
        }
        else
        {
            lastSmall->next = right;
            right = right->next;
        }

        lastSmall = lastSmall->next;
    }
    if (left == nullptr)
    {
        lastSmall->next = right;
    }
    else
    {
        lastSmall->next = left;
    }
    return newHead;
}
#endif