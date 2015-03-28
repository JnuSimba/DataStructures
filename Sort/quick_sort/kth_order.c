/*************************************************************************
	> File Name: quick_sort.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: 2012年12月24日 星期一 00时24分59秒
 ************************************************************************/

#include<stdio.h>
#define LEN 15
#define K 6


void swap(int * const p1, int * const p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

int  qsort(int k, int a[], int left, int right)
{
	int i, j, pivot;
	pivot = a[right];
	i = left; 
	j = right - 1;
	for (; ;) {
		for (; a[i] < pivot; i++);
		for (; a[j] > pivot; j--);
		if (i < j)
			swap(&a[i], &a[j]);
		else
			break;
	}

	swap(&a[i], &a[right]); //now i is the pivot index in the array
    			        //i.e. a[i] is the (i+1)th smallest item
	if (k == i-left+1)
		return a[i];
	else if (k < i-left+1) //target before pivot
		return qsort(k, a, left, i-1);
	else			//target after pivot
		return qsort((k-(i-left+1)), a, i+1, right);
	
}

int main(void)
{
	int arr[LEN] = {43, 423, 13, 6, 34, 64, 24, 69, 
					32, 28, 432, 641, 4365, 345, 624};
	
	printf("%d\n", qsort(K, arr, 0, LEN-1));

	return 0;
}



