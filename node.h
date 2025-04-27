#ifndef NODE_H
#define NODE_H

template <class t>
struct node
{
    t *data;
    node<t> *next;
    node<t> *prev;
    ~node()
    {
        delete data;
    }
};

#endif