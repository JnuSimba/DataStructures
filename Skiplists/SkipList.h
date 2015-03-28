/*************************************************************************
	> File Name: SkipList.h
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sun 22 Mar 2015 04:39:27 AM PDT
 ************************************************************************/

#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include<iostream>
#include "SkipNode.h"
#include "RandomHeight.h"

using namespace std;

template<class Key, class Obj>
class SkipList
{
    public:
        SkipList(float, int, Key*);
        ~SkipList();

        bool insert(Key*, Obj*);
        bool remove(Key*);
        Obj* retrieve(Key*);
        void dump(void);

    private:
        SkipNode<Key, Obj>* head;
        SkipNode<Key, Obj>* tail;
        float probability;
        int maxHeight; // skiplist maxheight, that is head and tail's height
        int curHeight; // skiplist element nodes's maxheight
        RandomHeight* randGen;
};

template<class Key, class Obj>
SkipList<Key, Obj>::SkipList(float p, int m, Key* k)
{
    curHeight = 1;
    maxHeight = m;
    probability = p;
    randGen = new RandomHeight(m, p);

    // create head and tail and attach them
    head = new SkipNode<Key, Obj>(maxHeight);
    tail = new SkipNode<Key, Obj>(k, (Obj*)NULL, maxHeight);
    for (int x = 1; x <= maxHeight; x++)
        head->fwdNodes[x] = tail;
}


template<class Key, class Obj>
SkipList<Key, Obj>::~SkipList()
{
    // walk 0 level nodes and delete all
    SkipNode<Key, Obj>* tmp;
    SkipNode<Key, Obj>* nxt;
    tmp = head;
    while (tmp)
    {
        nxt = tmp->fwdNodes[1];
        delete tmp;
        tmp = nxt;
    }

    delete randGen;
}

template<class Key, class Obj>
bool SkipList<Key, Obj>::insert(Key* k, Obj* o)
{
    int lvl = 0, h = 0;
    // The updateVec pointers always point to the most previous node prior 
    // to the insertion/deletion point at each level.
    SkipNode<Key, Obj>*  updateVec[maxHeight+1];
    SkipNode<Key, Obj>* tmp = head;
    Key* cmpKey = NULL;

    // figure out where new node goes
    for (h = curHeight; h >= 1; h--)
    {
        cmpKey = tmp->fwdNodes[h]->getKey();
        while (*cmpKey < *k)
        {
            tmp = tmp->fwdNodes[h];
            cmpKey = tmp->fwdNodes[h]->getKey();
        }

        updateVec[h] = tmp; // tmp points to *k's predecessor that <= *k 
    }
    tmp = tmp->fwdNodes[1];
    cmpKey = tmp->getKey();

    // if duplicate, return false
    if (*cmpKey == *k)
    {
        return false;
    }
    else
    {// perform an insert
        lvl = randGen->newLevel();
        if (lvl > curHeight)
        {
            for (int i = curHeight + 1; i <= lvl; i++)
                updateVec[i] = head; // the head points to the tail at all unused levels
            curHeight = lvl;
        }

        // insert new element
        tmp = new SkipNode<Key, Obj>(k, o, lvl);
        for (int i = 1; i <= lvl; i++)
        {
            tmp->fwdNodes[i] = updateVec[i]->fwdNodes[i];
            updateVec[i]->fwdNodes[i] = tmp;
        }
    }
    
    return true;

}

template<class Key, class Obj>
bool SkipList<Key, Obj>::remove(Key* k)
{
    SkipNode<Key, Obj>* updateVec[maxHeight+1];
    SkipNode<Key, Obj>* tmp = head;
    Key* cmpKey = NULL;

    // find the node we need to delete
    for (int h = curHeight; h > 0; h--)
    {
        cmpKey = tmp->fwdNodes[h]->getKey();
        while (*cmpKey < *k)
        {
            tmp = tmp->fwdNodes[h];
            cmpKey = tmp->fwdNodes[h]->getKey();
        }
        updateVec[h] = tmp;
    }
    tmp = tmp->fwdNodes[1];
    cmpKey = tmp->getKey();

    if (*cmpKey == *k)
    {
        for (int i = 1; i <= curHeight; i++)
        {
            if (updateVec[i]->fwdNodes[i] != tmp)
                break;
            updateVec[i]->fwdNodes[i] = tmp->fwdNodes[i];
        }
        delete tmp;

        while ( (curHeight > 1) && (head->fwdNodes[curHeight]->getKey() == tail->getKey()) )
            curHeight--; // the head points to the tail at all unused levels
        return true;
    }
    else
    {
        return false;
    }
}

template<class Key, class Obj>
Obj* SkipList<Key, Obj>::retrieve(Key* k)
{
    int h = 0;
    SkipNode<Key, Obj>* updateVec[maxHeight+1];
    SkipNode<Key, Obj>* tmp = head;
    Key* cmpKey;

    // find the key and return the node
    for (h = curHeight; h >= 1; h--)
    {
        cmpKey = tmp->fwdNodes[h]->getKey();
        while (*cmpKey < *k)
        {
            tmp = tmp->fwdNodes[h];
            cmpKey = tmp->fwdNodes[h]->getKey();
        }
        updateVec[h] = tmp;
    }

    tmp = tmp->fwdNodes[1];
    cmpKey = tmp->getKey();
    if (*cmpKey == *k)
        return tmp->getObj();
    else
        return (Obj*)NULL;
}

template<class Key, class Obj>
void SkipList<Key, Obj>::dump(void)
{
    SkipNode<Key, Obj>* tmp;
    tmp = head;
    while (tmp != tail)
    {
        if (tmp == head)
            cout << "There' the head node!" <<endl;
        else
            // Your key class must support "<<"
            cout << "Next node holds key:value " <<(*tmp->getKey())
                <<":"<<(*tmp->getObj())<<endl;
        tmp = tmp->fwdNodes[1];
    }
    cout << "There's the tail Node!"<<endl;
}

#endif
//end of file
