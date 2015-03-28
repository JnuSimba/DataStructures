#include<iostream>
using namespace std;

#define MAXSIZE 100

typedef int ElemType;
/* ���Ա�ľ�̬����洢�ṹ */
typedef struct Node
{
	ElemType data;
	int cur; //Ϊ0ʱ��ʾ��ָ��
} StaticLinkList[MAXSIZE];

/* ��һά����array�и���������һ����������array[0].curΪͷָ�룬"0"��ʾ��ָ�� */
bool InitList(StaticLinkList array)
{
	cout<<"InitList..."<<endl;
	for (int i = 0; i < MAXSIZE - 1; i++)
	{
		array[i].cur = i + 1;
	}

    array[MAXSIZE - 2].cur = 0;  /* ���һ��Ԫ��Ҳ�ǲ����õģ������ڶ���Ԫ�ص�curΪ0 */
	array[MAXSIZE - 1].cur = 0;/* Ŀǰ��̬����Ϊ�գ����һ��Ԫ�ص�curΪ0 */

	return true;
}
/* �����ÿռ�����ǿգ��򷵻ط���Ľ���±꣬���򷵻�0 */
int Malloc_SLL(StaticLinkList array)
{
	int k = array[0].cur;
	if (k)
		array[0].cur = array[k].cur;/* ��һ���������������� */

	return k;
}
/*  ���±�Ϊpos�Ŀ��н����յ��������� */
void Free_SLL(StaticLinkList array, int pos)
{
	array[pos].cur = array[0].cur; /* �ѵ�һ��Ԫ�ص�curֵ����Ҫɾ���ķ���cur */
	array[0].cur = pos;	/* ��Ҫɾ���ķ����±긳ֵ����һ��Ԫ�ص�cur */
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
/*  ��L�е�pos��Ԫ��֮ǰ�����µ�����Ԫ��Elem  */
bool ListInsert(StaticLinkList array, int pos, ElemType Elem)
{
	cout<<"Insert List from pos: "<<pos<<" Item "<<Elem<<endl;
	if (pos < 1 || pos > ListLength(array) + 1)
		return false;
	
	int k = MAXSIZE - 1;
	int i = Malloc_SLL(array); /* ��ÿ��з������±� */
	
	if (i)
	{
		array[i].data = Elem;

		for (int l = 1; l <= pos - 1; l++)
			k = array[k].cur;

		array[i].cur = array[k].cur;/* �ѵ�pos��Ԫ��֮ǰ��cur��ֵ����Ԫ�ص�cur */
		array[k].cur = i;/* ����Ԫ�ص��±긳ֵ����pos��Ԫ��֮ǰԪ�ص�cur */
		return true;
	}
	
	return false;
}
/*  ɾ����array�е�pos������Ԫ��   */
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
