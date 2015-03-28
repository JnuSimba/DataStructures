#include<iostream>
using namespace std;

void swap1(int *left, int *right)
{
    int temp = *left;
    *left = *right;
    *right = temp;
}

void swap2(int &left, int &right)
{
    int temp = left;
    left = right;
    right = left;
}

void swap3(int &left, int &right)
{
    if (&left != &right) 
    {
        left ^= right;
        right ^= left;
        left ^= right;
    }
}

/*****************************************************************/

void BubbleSort1(int arr[], int num)
{
    int i, j;
    for (i = 0; i < num; i++)
    {
        for (j = 1; j < num - i; j++)
        {
            if (arr[j - 1] > arr[j])
                swap1(&arr[j - 1], &arr[j]);
        }
    }
}

void BubbleSort2(int arr[], int num)
{
    int k = num;
    int j;
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (j = 1; j < k; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                swap1(&arr[j - 1], &arr[j]);
                flag = true;
            }
        }
        k--;
    }
}

void BubbleSort3(int arr[], int num)
{
    int k, j;
    int flag = num;
    while (flag > 0)
    {
        k = flag;
        flag = 0;
        for (j = 1; j < k; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                swap1(&arr[j - 1], &arr[j]);
                flag = j;
            }
        }
    }
}
/*************************************************************************/

/**************************************************************************/

void InsertionSort(int arr[], int num)
{
    int temp;
    int i, j;
    for (i = 1; i < num; i++)
    {
        temp = arr[i];
        for (j = i; j > 0 && arr[j - 1] > temp; j--)
            arr[j] = arr[j - 1];
        arr[j] = temp;
    }
}

/****************************************************************************/

void ShellSort(int *arr, int N)
{
    int i, j, increment;
    int tmp;
    for (increment = N / 2; increment > 0; increment /= 2)
    {
        for (i = increment; i < N; i++)
        {
            tmp = arr[i];
            for (j = i; j >= increment; j -= increment)
            {
                if (arr[j - increment] > tmp)
                    arr[j] = arr[j - increment];
                else
                    break;
            }
            arr[j] = tmp;
        }

    }
}

/**************************************************************************/


void SelectSort(int arr[], int num)
{
    int i, j, Mindex;
    for (i = 0; i < num; i++)
    {
        Mindex = i;
        for (j = i + 1; j < num; j++)
        {
            if (arr[j] < arr[Mindex])
                Mindex = j;
        }

        swap1(&arr[i], &arr[Mindex]);
    }
}

/********************************************************************************/


/*lpos is the start of left half, rpos is the start of right half*/
void merge(int a[], int tmp_array[], int lpos, int rpos, int rightn)
{
    int i, leftn, num_elements, tmpos;

    leftn = rpos - 1;
    tmpos = lpos;
    num_elements = rightn - lpos + 1;

    /*main loop*/
    while (lpos <= leftn && rpos <= rightn)
        if (a[lpos] <= a[rpos])
            tmp_array[tmpos++] = a[lpos++];
        else
            tmp_array[tmpos++] = a[rpos++];

    while (lpos <= leftn) /*copy rest of the first part*/
        tmp_array[tmpos++] = a[lpos++];
    while (rpos <= rightn) /*copy rest of the second part*/
        tmp_array[tmpos++] = a[rpos++];

    /*copy array back*/
    for (i = 0; i < num_elements; i++, rightn--)
        a[rightn] = tmp_array[rightn];
}


void msort(int a[], int tmp_array[], int left, int right)
{
    int center;

    if (left < right)
    {
        center = (right + left) / 2;
        msort(a, tmp_array, left, center);
        msort(a, tmp_array, center + 1, right);
        merge(a, tmp_array, left, center + 1, right);
    }
}



void merge_sort(int a[], int n)
{
    int *tmp_array;
    tmp_array = (int *)malloc(n * sizeof(int));

    if (tmp_array != NULL)
    {
        msort(a, tmp_array, 0, n - 1);
        free(tmp_array);
    }

    else
        printf("No space for tmp array!\n");
}

/************************************************************************************/
#define leftChild(i) (2*(i) + 1)

void percDown(int *arr, int i, int N)
{
    int tmp, child;
    for (tmp = arr[i]; leftChild(i) < N; i = child)
    {
        child = leftChild(i);
        if (child != N - 1 && arr[child + 1] > arr[child])
            child++;
        if (arr[child] > tmp)
            arr[i] = arr[child];
        else
            break;
    }
    arr[i] = tmp;
}

void HeapSort(int *arr, int N)
{
    int i;
    for (i = N / 2; i >= 0; i--)
        percDown(arr, i, N);
    for (i = N - 1; i > 0; i--)
    {
        swap1(&arr[0], &arr[i]);
        percDown(arr, 0, i);
    }
}


int main(void)
{
    int arr[] = { 9, 2, 5, 8, 3, 4, 7, 1, 6, 10};
    HeapSort(arr, 10);
    for (int i = 0; i < 10; i++)
        cout << arr[i] << ' ';
    cout << endl;

    return 0;
}

