/*************************************************************************
	> File Name: doublylinkedlist.h
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Fri 28 Dec 2012 08:02:35 PM CST
 ************************************************************************/

#ifndef DOUBLYLINKEDLIST_H
#define	DOUBLYLINKEDLIST_H

typedef struct node* link;

 struct node {
	unsigned char item;
	link prev;
	link next;
};

link make_node(unsigned char item);
void free_node(link p);
link search(unsigned char key);
void insert(link p);
void deletep(link p);
void traverse(void (*visit)(link));
void destroy(void);
void enqueue(link p);
link dequeue(void);

#endif



