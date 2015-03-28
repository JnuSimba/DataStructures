/*************************************************************************
	> File Name: quick_sort.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: 2012年12月24日 星期一 00时24分59秒
 ************************************************************************/
/* 快速排序的基本思想:通过一趟排序将待排记录分割成独立的两部分,
 * 其中一部分记录的关键字都比另一部分记录的关键字要小,
 * 则可分别对这两部分继续进行排序,以达到整个序列有序的目的 
 * 时间复杂度为O(nlogn)
 */
 
#include<stdio.h>
#define LEN 15
#define CUTOFF 3
/*用c++则可以写成引用*/
void swap(int * const p1, int * const p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void insertion_sort(int a[], int n)
{
	int i, j;
	int tmp;
	for (i = 1; i < n; i++) {
		tmp = a[i];
		for (j = i; j > 0 && a[j-1] > tmp; j--)
			a[j] = a[j-1];
		a[j] = tmp;
	}
}


/* return median of left, center, and right */
/* order these and hide the pivot */
int median3(int a[], int left, int right)
{
	int center = (left + right) / 2;
	if (a[left] > a[center])
		swap(&a[left], &a[center]);
	if (a[left] > a[right])
		swap(&a[left], &a[right]);
	if (a[center] > a[right])
		swap(&a[center], &a[right]);

	/* invariant: a[left] <= a[center] <= a[right] */
	swap(&a[center], &a[right-1]); //将中位数作为pivot且放置在right-1处
	return a[right-1];				//返回pivot
}

void qsort(int a[], int left, int right)
{
	int i, j, pivot;
	if (left + CUTOFF <= right) { /*因为要递归调用，如果不截断判断则会导致数组访问越界
									进而出现段错误 */
	/* left, left+1, ..., right-2, right-1, right 最极限的情况就是保证
	 * left与right中间至少有一个值，即CUTOFF最小要等于2,否则出现段错误
	 * CUTOFF=2保证可以取中位数 
	 * 当CUTOFF=1时不出现段错误，但运行结果是错误的 */
		pivot = median3(a, left, right);
		i = left; 
		j = right - 1;

		for (; ;) {
			while (a[++i] < pivot) {} //median函数已经比较了left和right，pivot当前位置为right-1
			while (a[--j] > pivot) {} //故从left+1和right-2开始比较
			if (i < j)
				swap(&a[i], &a[j]);
			else
				break;
		}

	swap(&a[i], &a[right-1]);

	qsort(a, left, i-1);
	qsort(a, i+1, right);
	
	}
	else /* do an insertion sort on the subarray */
		insertion_sort(a+left, right-left+1);

}

int main(void)
{
	int i; 
	int arr[LEN] = {43, 423, 13, 6, 34, 64, 24, 69, 
					32, 28, 432, 641, 4365, 345, 624};
	qsort(arr,0, LEN-1);
	for (i = 0; i < LEN; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}



