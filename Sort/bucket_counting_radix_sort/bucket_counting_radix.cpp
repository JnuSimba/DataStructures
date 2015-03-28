#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

/*****************计数排序*******************************/
void  CountSort(int *arr, int num)
{
    int mindata = arr[0];
    int maxdata = arr[0];
    for (int i = 1; i < num; i++)
    {
        if (arr[i] > maxdata)
            maxdata = arr[i];
        if (arr[i] < mindata)
            mindata = arr[i];
    }
    
    int size = maxdata - mindata + 1;
    //申请空间并初始化为0
    int *pCount = (int *)malloc(sizeof(int) * size);
    memset(pCount, 0, sizeof(int)*size);

    //记录排序计数，每出现一次在对应位置加1
    for (int i = 0; i < num; i++)
        ++pCount[arr[i]-mindata];

    //确定不比该位置大的数据个数
    for (int i = 1; i < size; i++)
        pCount[i] += pCount[i - 1]; //加上前一个的计数

    int *pSort = (int *)malloc(sizeof(int) * num);
    memset((char*)pSort, 0, sizeof(int) * num);

    //从末尾开始拷贝是为了重复数据首先出现的排在前面，即稳定排序
    for (int i = num - 1; i >= 0; i--)
    {
        //包含自己需要减1，重复数据循环回来也需要减1
        --pCount[arr[i]-mindata];
        pSort[pCount[arr[i]-mindata]] = arr[i];
    }
    //拷贝到原数组
    for (int i = 0; i < num; i++)
        arr[i] = pSort[i];

    free(pCount);
    free(pSort);

}

/*****************桶排序*****************************/
struct Node
{
    int key_;
    struct Node *next_;
    Node(int key)
    {
        key_ = key;
        next_ = NULL;
    }
};

#define bucket_size 10 //与数组元素个数相等

void buck_sort(int arr[], int num)
{
    Node *bucket_table[bucket_size];
    memset(bucket_table, 0, sizeof(bucket_table));

    //建立每一个头节点,头节点的key保存当前桶的数据量
    for (int i = 0; i < bucket_size; i++)
        bucket_table[i] = new Node(0);
    
    int maxValue = arr[0];
    for (int i = 1; i < num; i++)
    {
        if (arr[i] > maxValue)
            maxValue = arr[i];
    }

    for (int j = 0; j < num; j++)
    {
        Node *ptr = new Node(arr[j]);//其余节点的key保存数据

        //映射函数计算桶号
        // index = (value * number_of_elements) / (maxvalue + 1)
        int index = (arr[j] * bucket_size) / (maxValue + 1);
        Node *head = bucket_table[index];
        //该桶还没有数据
        if (head->key_ == 0)
        {
            bucket_table[index]->next_ = ptr;
            (bucket_table[index]->key_)++;

        }
        else
        {
            //找到合适的位置插入
            while (head->next_ != NULL && head->next_->key_ <= ptr->key_)
                head = head->next_;
            ptr->next_ = head->next_;
            head->next_ = ptr;
            (bucket_table[index]->key_)++;
        }

    }

    //将桶中的数据拷贝回原数组
    int m, n;
    for (m = 0, n = 0;  n < num && m < bucket_size; m++, n++)
    {
        Node *ptr = bucket_table[m]->next_;
        while (ptr != NULL)
        {
            arr[n] = ptr->key_;
            ptr = ptr->next_;
            n++;
        }
        n--;
    }

    //释放分配的动态空间
    for (m = 0; m < bucket_size; m++)
    {
        Node *ptr = bucket_table[m];
        Node *tmp = NULL;
        while (ptr != NULL)
        {
            tmp = ptr->next_;
            delete ptr;
            ptr = tmp;
        }

    }

}


/****************************************************/



/******************** 基数排序LSD*********************/

void base_sort_ISD(int *arr, int num)
{
    Node *buck[10]; // 创建一个链表数组
    Node *tail[10]; //保存每条链表尾节点指针集合，
    //这样插入buck数组时就不用每次遍历到末尾
    int  i, MaxValue, kth, high, low;
    Node *ptr;
    for(MaxValue = arr[0], i = 1; i < num; i++)
        MaxValue = max(MaxValue, arr[i]);

    memset(buck, 0, sizeof(buck));
    memset(tail, 0, sizeof(buck));

    for(low = 1; high = low * 10, low < MaxValue; low *= 10)
    {
        //只要没排好序就一直排序
        for(i = 0; i < num; i++)
        {
            //往桶里放
            kth = (arr[i] % high) / low;//取出数据的某一位，作为桶的索引
            ptr = new Node(arr[i]); //创建新节点

            //接到末尾
            if (buck[kth] != NULL)
            {
                tail[kth]->next_ = ptr;
                tail[kth] = ptr;
            }
            else
            {
                buck[kth] = ptr;
                tail[kth] = ptr;
            }

        }
        //把桶中的数据放回数组中（同条链表是从头到尾）
        for (kth = 0, i = 0; kth < num; i++)
        {
            while (buck[i] != NULL)
            {
                arr[kth++] = buck[i]->key_;
                ptr = buck[i];
                buck[i] = buck[i]->next_;
                delete ptr;
            }
        }

        memset(tail, 0, sizeof(buck));

    }

}
/**************************************************************/

int main(void)
{

    int arr1[] = {10, 15, 11, 20, 15, 18, 19, 12, 14, 17};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    CountSort(arr1, size1);
    for (int i = 0; i < size1; i++)
        printf("%d ", arr1[i]);
    printf("\n");

    int arr2[] = {54, 8, 216, 512, 27, 729, 0, 1, 343, 125};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    base_sort_ISD(arr2, size2);
    for (int i = 0; i < size2; i++)
        printf("%d ", arr2[i]);
    printf("\n");

    int arr3[] = {49, 38, 65, 97, 76, 13, 27, 49, 132, 134};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    buck_sort(arr3, size3);
    for (int i = 0; i < size3; i++)
        printf("%d ", arr3[i]);
    printf("\n");

    return 0;
}

