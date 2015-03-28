/*************************************************************************
	> File Name: binarysearchtree.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sat 29 Dec 2012 06:08:08 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "binarysearchtree.h"

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

link search(link t, unsigned char key)
{
	if (!t)
		return NULL;
	if (t->item > key)
		return search(t->left, key);
	if (t->item < key)
		return search(t->right, key);
	/* if (t->item == key) */
	return t;
}

link insert(link t, unsigned char key)
{
	if (!t)
		return make_node(key);
	if (t->item > key) /* insert to left subtree */
		t->left = insert(t->left, key);
	else /* if (t->item <= key), insert to right subtree */
		t->right = insert(t->right, key);
	return t;
}


link delete(link t, unsigned char key)
{
	link p;
	if (!t)
		return NULL;
	if (t->item > key) /* delete from left subtree */
		t->left = delete(t->left, key);
	else if (t->item < key) /* delete from right subtree */
		t->right = delete(t->right, key);
	else { /* if (t->item == key) */
			if (t->left == NULL && t->right == NULL) { /* 如果此时(递归)找到的节点已经是没有子树的树叶则直接释放空间
														  并置t为NULL并由return返回，(即将上一层指向此节点的指针置为NULL)，防止野指针 */
				/* if t is a leaf node */
				free_node(t);
		 		t =  NULL;
			} 
			else if (t->left) {/* if t has left subtree */
				/* replace t with the rightmost node in left subtree */
				/* 如果想要删除的节点有左子树，则找到左子树下边最靠右的节点(已无右子树) */
				for (p = t->left; p->right; p = p->right);
				t->item = p->item; /* 将左子树下最靠右的节点值赋予想要删除的节点 */
		 		t->left = delete(t->left, t->item); /* 以左子树的根指针作为根节点，递归找到最靠右节点
													   若此时节点已无子树则满足地一个if条件，直接释放空间
													   若还有左子树，则按相同原则递归进行换值后删除下一个最靠右节点 */
			} 
			/* 当找到要删除的节点时，优先考虑将左子树下最靠右节点的值换上来
			 * 如果没有左子树，则将右子树下最靠左节点的值换上来 */
			else {/* if t has right subtree */
				/* replace t with the leftmost node in right subtree */
				for (p = t->right; p->left; p = p->left);
				t->item = p->item;
		 		t->right = delete(t->right, t->item);
			}
	}
	return t;
}

void print_tree(link t)
{
	if (t) {
		printf("(");
		printf("%d", t->item);
		print_tree(t->left);
		print_tree(t->right);
		printf(")");
	}
	else
		printf("()");
}



