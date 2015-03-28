
/* linkedlist.c */
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
/* 不能将head 定义写在头文件,因为main.c也会包含头文件，每个.c文件生成一个.o文件
 * 这样会导致在两个文件都定义了head,虽然是同名，但链接时是不同的符号，
 * 故操作的不是同一个链表
 * 但有一种特殊情况，可以将变量外部声明写在头文件，如extern int top;
 * 注意extern不能省略，否则当包含头文件的main.c展开时等于重新定义一个变量top，
 * 而此时linkedlist.c也定义了一个int top,因为没有加static修饰,故两个top都是有外部链接属性的
 * 这样会造成一个变量定义了多次,链接出错
 * 可以声明多次但只可以定义一次
 */

static link head = NULL;

link make_node(unsigned char item)
{
    link p = malloc(sizeof(*p));
    p->item = item;
    p->next = NULL;
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
    for (p = head; p; p = p->next)
	if (p->item == key)
	    return p;
    return NULL;
}

void insert(link p)
{
	printf("insert node from head ...\n");
    p->next = head;
    head = p;
}

/*
void delete(link p)
{
	link pre;
	printf("delete node from ptr ...\n");
	if (p == head) {
		head = p->next;
		return;
	}
	for (pre = head; pre; pre = pre->next) 
		if (pre->next == p) {
			pre->next = p->next;
			return;
		}
}
*/

void deletep(link p)
{
    link *pnext;
	printf("delete node from ptr ...\n");
    for (pnext = &head; *pnext; pnext = &(*pnext)->next)
	if (*pnext == p) {
	    *pnext = p->next;
	    return;
	}
}

void traverse(void (*visit) (link))
{
    link p;
	printf("linkedlist traverse ...\n");
    for (p = head; p; p = p->next)
		visit(p);
}

void reverse(void)
{
	link pnode = head;
    link pprev = NULL;
	printf("reverse linkedlist ...\n");
    while (pnode != NULL) {
	// get the next node, and save it at pNext
	link pnext = pnode->next;
	// reverse the linkage between nodes
	pnode->next = pprev;
	// move forward on the the list
	pprev = pnode;
	pnode = pnext;
    
	}
	head = pprev;
}

void destroy(void)
{
    link q, p = head;
	printf("destory linkedlist ...\n");
    head = NULL;
    while (p) {
	q = p;
	p = p->next;
	free_node(q);
    }
}

void push(link p)
{
	printf("push item from head ...\n");
    insert(p);
}

link pop(void)
{
    if (head == NULL)
	return NULL;
    else {
	link p = head;
	printf("pop item from head ...\n");
	head = head->next;
	return p;
    }
}
