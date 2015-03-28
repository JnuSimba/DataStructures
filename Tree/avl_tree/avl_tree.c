#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *AVLNodePtr;

struct AVLNode
{
    int element;
    AVLNodePtr left;
    AVLNodePtr right;
    int height;
};

void makeempty(AVLNodePtr T)
{
    if (T == NULL)
        return;
    else
    {
        makeempty(T->left);
        makeempty(T->right);
        free(T);
    }
}

static int height(AVLNodePtr p)
{
    if (p == NULL)
        return -1;
    else
        return p->height;
}

static int Max(int ln, int rn)
{
    return ln > rn ? ln : rn;
}

/* return pointer to the new root */
static AVLNodePtr singlerotateLL(AVLNodePtr k2)
{
    AVLNodePtr k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = Max(height(k2->left), height(k2->right)) + 1;
    k1->height = Max(height(k1->left), k2->height) + 1;
    return k1;
}

static AVLNodePtr singlerotateRR(AVLNodePtr k1)
{
    AVLNodePtr k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = Max(height(k1->left), height(k1->right)) + 1;
    k2->height = Max(k1->height, height(k2->right)) + 1;
    return k2;
}

static AVLNodePtr doublerotateRL(AVLNodePtr k3)
{
    k3->left = singlerotateRR(k3->left);
    return singlerotateLL(k3);
}

static AVLNodePtr doublerotateLR(AVLNodePtr k3)
{
    k3->right = singlerotateLL(k3->right);
    return singlerotateRR(k3);
}


AVLNodePtr insert(int X, AVLNodePtr T)
{
    if (T == NULL)
    {
        /* create and return a one-node tree */
        T = (AVLNodePtr)malloc(sizeof(struct AVLNode));
        if (T == NULL)
        {
            printf("out of space!");
            exit(1);
        }
        else
        {
            T->element = X;
            T->height = 0;
            T->left = T->right = NULL;
        }
    }

    else if (X < T->element)
    {
        T->left = insert(X, T->left);
        if (height(T->left) - height(T->right) == 2)
        {
            if (X < T->left->element)
                T = singlerotateLL(T);
            else
                T = doublerotateRL(T);
        }
    }

    else if (X > T->element)
    {
        T->right = insert(X, T->right);
        if (height(T->right) - height(T->left) == 2)
        {
            if (X > T->right->element)
                T = singlerotateRR(T);
            else
                T = doublerotateLR(T);
        }
    }
    /* else X is in the tree already; we'll do nothing */
    T->height = Max(height(T->left), height(T->right)) + 1;
    return T;
}

void inorder(AVLNodePtr T)
{
    if (T == NULL)
        return;
    else
    {
        inorder(T->left);
        printf("%d ", T->element);
        inorder(T->right);
    }
}

int main(void)
{
    int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
    AVLNodePtr T = NULL;
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        T = insert(arr[i], T);

    inorder(T);
    makeempty(T);
    return 0;
}

