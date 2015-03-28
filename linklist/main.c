/*************************************************************************
	> File Name: main.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Fri 28 Dec 2012 01:22:24 PM CST
 ************************************************************************/

#include<stdio.h>
#include "linkedlist.h"

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
	push(p);
	p = make_node(200);
	push(p);
	p = make_node(250);
	push(p);
	
	reverse();//链表反转

	while ((p = pop())) {
	/* 如果不加外面一圈括号，会发出警告warning: suggest parentheses around assignment used as truth value
	 * 理由：在C语言中，非0即代表TRUE，反之为FALSE。上面的语句以p的值是否为NULL用于最后的判断。但是由于长期的编程实践告诉我们，
	 * 人们经常在“=”和“==”的使用上出现手误，所以gcc编译器为此要求我们明确地告诉编译器它是“=”而不是“==”，是故意，而非手误
	 */
	/* #define NULL (void *)0 */
	/* 返回值与sideeffect。 赋值语句的返回值是本身*/
		print_item(p);
		free_node(p);
	}

	return 0;
}


