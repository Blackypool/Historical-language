#include "distuct.h"


void fell_a_root(struct leaf **root)
{
    if(*root != NULL)
    {
        if((*root)->left != NULL)
            cleaner(&((*root)->left));
        
        if((*root)->right != NULL)
            cleaner(&((*root)->right));
    }

    if(*root != NULL)
    {
        free(*root);
        *root = NULL;
    }
}


void cleaner(struct leaf **left_right)
{
    if(*left_right == NULL)
        return ;

    if((*left_right)->left != NULL)
        cleaner(&(*left_right)->left);
    
    if((*left_right)->right != NULL)
        cleaner(&(*left_right)->right);

    if(*left_right != NULL)
    {    
        free(*left_right);
        *left_right = NULL;
    }
}
