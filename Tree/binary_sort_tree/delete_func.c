link FindMin(link T)
{
    if (T != NULL)
        while (T->left != NULL)
            T = T->left;

    return T;
}

link delete(unsigned char X, link T)
{
    link tmp;
    if (T == NULL)
    {
        printf("Tree is empty!\n");
        return NULL;
    }

    if (X < T->key) //go left
        T->left = delete(X, T->left);
    else if (X > T->key) // go right
        T->right = delete(X, T->right);

    /* found elem to be deleted*/
    else if (T->left && T->right) //have two children
    {
        // replace with smallest in right subtree
        tmp = FindMin(T->right);
        T->key = tmp->key;
        T->right = delete(T->key, T->right);
    }
    else //one or zero children
    {
        tmp = T;
        if (T->left == NULL)
            T = T->right;
        else if (T->right == NULL)
            T = T->left;
        free(tmp);
    }

    return T;
}
