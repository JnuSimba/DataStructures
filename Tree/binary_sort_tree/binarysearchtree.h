/*************************************************************************
	> File Name: binarysearchtree.h
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sat 29 Dec 2012 06:05:55 PM CST
 ************************************************************************/

#ifndef BST_H
#define BST_H

typedef struct node * link;
struct node {
	unsigned char item;
	link left, right;
};

link search(link t, unsigned char key);
link insert(link t, unsigned char key);
link delete(link t, unsigned char key);
void print_tree(link t);

#endif



