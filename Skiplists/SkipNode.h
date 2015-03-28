/*************************************************************************
	> File Name: SkipNode.h
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sun 22 Mar 2015 02:39:27 AM PDT
 ************************************************************************/

#ifndef SKIP_LIST_NODE_H_
#define SKIP_LIST_NODE_H_

#include <iostream>
using namespace std;

struct Product
{
    float cost;
    int quantity;
    int location;
    public:
        Product(float co, int qu, int lo):
            cost(co), quantity(qu), location(lo) {}
    friend ostream &operator<<(ostream &os, const Product &pro);
};


typedef Product productData;

ostream &operator<<(ostream &os, const Product &pro)
{
    os << pro.cost << "/" << pro.quantity << "/" << pro.location;
    return os;
}

template<class Key, class Obj>
class SkipList;

template <class Key, class Obj>
class SkipNode
{
    public:
        SkipNode(Key*, Obj*, int);
        SkipNode(int);
        ~SkipNode();

        Key* getKey(void);
        Obj* getObj(void);
        int  getHgt(void);
        SkipNode** fwdNodes;

    private:
        int nodeHeight;
        Key* key;
        Obj* obj;
};

template<class Key, class Obj>
SkipNode<Key, Obj>::~SkipNode()
{
    delete key;
    delete obj;
    delete [] fwdNodes;
}

template<class Key, class Obj>
SkipNode<Key, Obj>::SkipNode(Key* k, Obj* o, int h)
{
    nodeHeight = h;
    key = k;
    obj = o;
    fwdNodes = new SkipNode<Key, Obj>* [h+1];
    for (int x = 1; x <= nodeHeight; x++)
        fwdNodes[x] = (SkipNode<Key, Obj>*)NULL;
}

// only for the list's head node
template<class Key, class Obj>
SkipNode<Key, Obj>::SkipNode(int h)
{
    nodeHeight = h;
    key = (Key*)NULL;
    obj = (Obj*)NULL;
    fwdNodes = new SkipNode<Key, Obj>* [h+1];
    for (int x = 1; x <= nodeHeight; x++)
        fwdNodes[x] = (SkipNode<Key, Obj>*)NULL;
}

template<class Key, class Obj>
Key* SkipNode<Key, Obj>::getKey(void)
{
    return key;
}

template<class Key, class Obj>
Obj* SkipNode<Key, Obj>::getObj(void)
{
    return obj;
}

template<class Key, class Obj>
int SkipNode<Key, Obj>::getHgt(void)
{
    return nodeHeight;
}

#endif //SKIP_LIST_NODE

// end of File
