/*************************************************************************
	> File Name: main2.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sat 29 Dec 2012 06:22:57 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "binarysearchtree.h"

#define RANGE 100
#define N 6

void print_item(link p)
{
	printf("%d", p->item);
}

int main(void)
{
	int i, key;
	link root = NULL;
	srand(time(NULL));
	for (i = 0; i < N; i++) {
		root = insert(root, rand() % RANGE); /* 第一次循环root从NULL变成根节点值，接下去
												的循环虽然迭代root，但在插入节点过程中root的值始终不变 */
		printf("root = 0x%x\n", (unsigned int)root);
	}

	printf("\t\\tree");
	print_tree(root);
	printf("\n\n");
	
	while (root) {
		key = rand() % RANGE;
		if (search(root, key)) {
			printf("delete %d in tree\n", key);
			root = delete(root, key); /* root虽然迭代，但返回的仍是先前的值，即根节点的值保持不变
										 直到全部节点被删除，root变成NULL即0x0 */
		    printf("root = 0x%x\n", (unsigned int)root);
			
			printf("\t\\tree");
			print_tree(root); /* 传递给函数的一直是根节点的值，直到树清空，root变成NULL */
			printf("\n\n");
		}
	}
	return 0;
}


