/*************************************************************************
	> File Name: doublylinkedlist.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Fri 28 Dec 2012 08:07:21 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "doublylinkedlist.h"

struct node tailsentinel;
struct node headsentinel = {0, NULL, &tailsentinel};
struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;


link make_node(unsigned char item)
{
	link p =  malloc(sizeof(*p));
	p->item = item;
	p->prev = p->next = NULL;
	printf("make node from Item %d\n",item);
	return p;
}

void free_node(link p)
{
	printf("free node ...\n");
	free(p);
}

link search(unsigned char key)
{
	link p;
	printf("search by key %d\n", key);
	for (p = head->next; p != tail; p = p->next)
		if (p->item == key)
			return p;
	return NULL;
}

void insert(link p)
{
	printf("insert node from head ...\n");
	p->next = head->next;
	head->next->prev = p;
	head->next = p;
	p->prev = head;
}

void deletep(link p)
{
	printf("delete node from ptr ...\n");
	p->prev->next = p->next;
	p->next->prev = p->prev;
}

void traverse(void (*visit)(link))
{
	link p;
	printf("doublylinkedlist traverse ...\n");
	for (p = head->next; p != tail; p = p->next)
		visit(p);
	printf("\n");
}

void destroy(void)
{
	link q, p = head->next;
	printf("destory doublylinkedlist ...\n");
	head->next = tail;
	tail->prev = head;
	while (p != tail) {
		q = p;
		p = p->next;
		free_node(q);
	}
}


void enqueue(link p)
{
	printf("enqueue from head ...\n");
	insert(p);
}

link dequeue(void)
{	
	if (tail->prev == head)
		return NULL;
	else {
			link p = tail->prev;
			printf("dequeue from tail ...\n");
			deletep(p);
			return p;
	}
}


