/*************************************************************************
	> File Name: circular_buffer2.c
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Thu 19 Mar 2015 07:26:31 AM PDT
 ************************************************************************/

/* This approach replaces the CircularBuffer 'end' field with the 'count' field and changes these functions:  */

#include<stdio.h>
#include<malloc.h>

/* Opaque buffer element type. This would be defined by the application */
typedef struct { int value; } ElemType;

/* Circular buffer object */
typedef struct {
    int size;  /* maximum number of elements */
    int start; /* index of oldest element */
    int count;   /* the number of readable items in the buffer */
    ElemType* elems; /* vector of elements */
} CircularBuffer;

void cbInit(CircularBuffer* cb, int size)
{
    cb->size = size; 
    cb->start = 0;
    cb->count = 0;
    cb->elems = (ElemType*)calloc(cb->size, sizeof(ElemType));
}

void cbFree(CircularBuffer* cb)
{
    free(cb->elems); /* OK if null */
}

int cbIsFull(CircularBuffer* cb)
{
    return cb->count == cb->size; 
}

int cbIsEmpty(CircularBuffer* cb)
{
    return cb->count == 0;
}

/* Write an element, overwriting oldest element if buffer if full(or throw exception).App can choose to avoid the overwrite by checking cbIsFull(). */
void cbWrite(CircularBuffer* cb, ElemType* elem)
{
    int end = (cb->start + cb->count) % cb->size;
    cb->elems[end] = *elem;
    if (cb->count == cb->size)
    {
        cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
    }
    else
    {
        ++cb->count;
    }
}

/* Read oldest element. App must ensure !cbIsEmpty() first. */
void cbRead(CircularBuffer* cb, ElemType* elem)
{
    *elem = cb->elems[cb->start];
    cb->start = (cb->start + 1) % cb->size;
    --cb->count;
}

int main(void)
{
    CircularBuffer cb;
    ElemType elem = {0};
    int testBufferSize = 10; /* arbitrary size */
    cbInit(&cb, testBufferSize);

    /* Fill buffer with test elements 3 times */
    for (elem.value = 0; elem.value < 3 * testBufferSize; ++elem.value)
    {
        cbWrite(&cb, &elem);
    }

    /* Remove and print all elements */
    while (!cbIsEmpty(&cb))
    {
        cbRead(&cb, &elem);
        printf("%d, ", elem.value);
    }
    printf("\n");

    cbFree(&cb);
    return 0;

}
