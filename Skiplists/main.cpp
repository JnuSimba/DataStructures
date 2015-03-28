/*************************************************************************
	> File Name: main.cpp
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sun 22 Mar 2015 06:10:10 PM PDT
 ************************************************************************/

#include<iostream>
#include "SkipList.h"
using namespace std;

int main(void)
{
    int* maxKey = new int(99);
    SkipList<int, productData>* aSkipList = 
        new SkipList<int, productData>((float)0.5, 4, maxKey);
   
    int* aKey = new int(87);
    productData* prod = new productData(100, 200, 300);
    aSkipList->insert(aKey, prod);

    aKey = new int(25);
    prod = new productData(50, 100, 300);
    aSkipList->insert(aKey, prod);
    
    productData* pr = NULL;
    if (pr = aSkipList->retrieve(aKey))
        cout << "retrieve item " << *aKey << ":" << *pr << endl;
    else
        cout <<" item not found!" << endl;

    if (aSkipList->remove(aKey))
        cout<<"remove item success!"<< endl;
    else
        cout <<"remove item fail!" << endl;

    aSkipList->dump();

    delete aSkipList;

    return 0;    
}

