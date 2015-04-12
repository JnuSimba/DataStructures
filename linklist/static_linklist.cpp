#include<iostream>
using namespace std;

#define MAXSIZE 100

typedef int ElemType;
/* 线性表的静态链表存储结构 */
typedef struct Node
{
	ElemType data;
	int cur; //为0时表示无指向
} StaticLinkList[MAXSIZE];

/* 将一维数组array中各分量链成一个备用链表，array[0].cur为头指针，"0"表示空指针 */
bool InitList(StaticLinkList array)
{
	cout<<"InitList..."<<endl;
	for (int i = 0; i < MAXSIZE - 1; i++)
	{
		array[i].cur = i + 1;
	}

        array[MAXSIZE - 2].cur = 0;  /* 最后一个元素也是不可用的，倒数第二个元素的cur为0 */
	array[MAXSIZE - 1].cur = 0;/* 目前静态链表为空，最后一个元素的cur为0 */

	return true;
}
/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SLL(StaticLinkList array)
{
	int k = array[0].cur;
	if (k)
		array[0].cur = array[k].cur;/* 下一个分量用来做备用 */

	return k;
}
/*  将下标为pos的空闲结点回收到备用链表 */
void Free_SLL(StaticLinkList array, int pos)
{
	array[pos].cur = array[0].cur; /* 把第一个元素的cur值赋给要删除的分量cur */
	array[0].cur = pos;	/* 把要删除的分量下标赋值给第一个元素的cur */
}

int ListLength(StaticLinkList array)
{
	int i = array[MAXSIZE - 1].cur;
	int j = 0;
	while(i)
	{
		i = array[i].cur;
		++j;
	}
	return j;
}
/*  在L中第pos个元素之前插入新的数据元素Elem  */
bool ListInsert(StaticLinkList array, int pos, ElemType Elem)
{
	cout<<"Insert List from pos: "<<pos<<" Item "<<Elem<<endl;
	if (pos < 1 || pos > ListLength(array) + 1)
		return false;
	
	int k = MAXSIZE - 1;
	int i = Malloc_SLL(array); /* 获得空闲分量的下标 */
	
	if (i)
	{
		array[i].data = Elem;

		for (int l = 1; l <= pos - 1; l++)
			k = array[k].cur;

		array[i].cur = array[k].cur;/* 把第pos个元素之前的cur赋值给新元素的cur */
		array[k].cur = i;/* 把新元素的下标赋值给第pos个元素之前元素的cur */
		return true;
	}
	
	return false;
}
/*  删除在array中第pos个数据元素   */
bool ListDelete(StaticLinkList array, int pos)
{
	cout<<"Delete List from pos: "<<pos<<endl;
	if (pos < 1 || pos > ListLength(array))
		return false;

	int k = MAXSIZE - 1;

	for (int l = 1; l <= pos - 1; l++)
		k = array[k].cur;
	
	int j = array[k].cur;
	array[k].cur = array[pos].cur;

	Free_SLL(array, j);

	return true;
}

bool ListTraverse(StaticLinkList array)
{
	cout<<"List Traverse : "<<endl;
	int k = MAXSIZE - 1;
	while (array[k].cur != 0)
	{
		k = array[k].cur;
		cout<<array[k].data<<' ';
	}

	cout<<endl;
	return true;
}


int main(void)
{
	StaticLinkList SSL;
	InitList(SSL);
	for (int i = 1; i < 5; i++)
		ListInsert(SSL, i, i);
	ListTraverse(SSL);

	ListDelete(SSL, 3);
	ListTraverse(SSL);
	cout<<"List Length : "<<ListLength(SSL)<<endl;

	return 0;
}
