/*************************************************************************
	> File Name: main2.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Fri 28 Dec 2012 08:18:57 PM CST
 ************************************************************************/

#include<stdio.h>
#include "doublylinkedlist.h"

void print_item(link p)
{
	printf("print item %d \n",p->item);
}

int main(void)
{
	link p = make_node(10);
	insert(p);
	p = make_node(5);
	insert(p);
	p = make_node(90);
	insert(p);
	p = search(5);
	deletep(p);
	free_node(p);
	traverse(print_item);
	destroy();
	printf("..................\n");

	p = make_node(100);
	enqueue(p);
	p = make_node(200);
	enqueue(p);
	p = make_node(250);
	enqueue(p);
	while ((p = dequeue())) {
		print_item(p);
		free_node(p);
	}

	return 0;
}


