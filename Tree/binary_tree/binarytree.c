/*************************************************************************
	> File Name: binarytree.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sat 29 Dec 2012 03:37:20 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "binarytree.h"

static link make_node(unsigned char item)
{
	link p = malloc(sizeof(*p));
	p->item = item;
	p->left = p->right = NULL;
	return p;
}

static void free_node(link p)
{
	free(p);
}

link init(unsigned char VLR[], unsigned char LVR[],
			int n)
{
	link t;
	int k;
	if (n <= 0)
		return NULL;
	for (k = 0; VLR[0] != LVR[k]; k++);
	t = make_node(VLR[0]);
	t->left = init(VLR+1, LVR, k);
	t->right = init(VLR+1+k, LVR+1+k, n-k-1);
	return t;
}

void pre_order(link t, void (*visit)(link))
{
	if (!t)
		return;
	visit(t);
	pre_order(t->left, visit);
	pre_order(t->right, visit);
}

void in_order(link t, void (*visit)(link))
{
	if (!t)
		return;
	in_order(t->left, visit);
	visit(t);
	in_order(t->right, visit);
}

void post_order(link t, void (*visit)(link))
{
	if (!t)
		return;
	post_order(t->left, visit);
	post_order(t->right, visit);
	visit(t);
}

int count(link t)
{
	if (!t)
		return 0;
	return 1 + count(t->left) + count(t->right);
}

int depth(link t)
{
	int dl, dr;
	if (!t)
		return 0;
	dl = depth(t->left);
	dr = depth(t->right);
	return 1 + (dl > dr ? dl : dr);
}

void destroy(link t)
{
	post_order(t, free_node);
}





