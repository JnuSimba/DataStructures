/*************************************************************************
	> File Name: quick_sort.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: 2012年12月24日 星期一 00时24分59秒
 ************************************************************************/

#include<stdio.h>
#define LEN 15

void swap(int * const p1, int * const p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void qsort(int a[], int left, int right)
{
	int i, j, pivot;
	pivot = a[right];
	i = left;
	j = right - 1;

	if (left < right) { /*必须加判断，否则会无限循环下去，进而可能栈帧溢出而导致段错误*/

		for (; ;) {
			for (; a[i] < pivot; i++);
			for (; a[j] > pivot; j--);
			if (i < j)
				swap(&a[i], &a[j]);
			else
				break;
		}

	swap(&a[i], &a[right]);

	qsort(a, left, i-1);
	qsort(a, i+1, right);
	
	}
}

int main(void)
{
	int i; 
	int arr[LEN] = {43, 423, 13, 6, 34, 64, 24, 69, 
					32, 28, 432, 641, 4365, 345, 624};
	qsort(arr, 0, LEN-1);
	for (i = 0; i < LEN; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}



