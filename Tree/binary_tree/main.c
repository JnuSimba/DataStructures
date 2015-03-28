/*************************************************************************
	> File Name: main.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sat 29 Dec 2012 03:56:23 PM CST
 ************************************************************************/

#include<stdio.h>
#include "binarytree.h"
/* 对一个地址先后进行两次free()操作就会引起这种错误代码
 * *** glibc detected *** ./main: double free or corruption (fasttop)
 */

void print_item(link p)
{
	printf("%d", p->item);
}

int main(void)
{
	unsigned char pre_seq[] = { 4, 2, 1, 3, 6, 5, 7 };
	unsigned char in_seq[] = { 1, 2, 3, 4, 5, 6, 7 };
	link root = init(pre_seq, in_seq, 7);

	pre_order(root, print_item);
	putchar('\n');
	in_order(root, print_item);
	putchar('\n');
	post_order(root, print_item);
	putchar('\n');

	printf("count=%d depth=%d\n", count(root), depth(root));
	destroy(root);
	return 0;
}


