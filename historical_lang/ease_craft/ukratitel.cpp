#include "ukratitel.h"

Le_af create_and_destroy(Le_af_arg, typ_of_x num);


static struct ukrat_enum calc[] = {

    {OPER_add, u_add},
     {OPER_sub, u_sub},
      {OPER_mul, u_mul},
       {OPER_div, u_div},
        {OPER_pow, u_pow},

};


#define FALIBILITY 0.000001
typ_of_x sravn(typ_of_x arg)
{
    if (fabs(arg) < 0 + FALIBILITY)
        return 0;

    if ( 1 - FALIBILITY < arg && arg < 1 + FALIBILITY)
        return 1;

    return 23;
}


void too_easy(Le_af_arg)
{
    int sche = 9;
    int constik = 11;
    while(sche != constik)
    {
        sche = constik;

        rekrut_for_ukrat(leaf, &sche);
    }
}

void rekrut_for_ukrat(Le_af_arg, int *sche)
{
    if(leaf == NULL) 
        return ;

    if(leaf->left != NULL)
    {
        leaf->left = ukratitel(leaf->left, sche);
        rekrut_for_ukrat(leaf->left, sche);
    }

    if(leaf->right != NULL)
    {
        leaf->right = ukratitel(leaf->right, sche);
        rekrut_for_ukrat(leaf->right, sche);
    }
}

Le_af ukratitel(Le_af_arg, int *sche)
{
    if(leaf != NULL)
    {
        switch(leaf->type)
        {
            case OPERAT:
            {
                size_t num_of_op = sizeof(calc) / sizeof(calc[0]);

                for(size_t i = 0; i < num_of_op; ++i)
                    if (leaf->value.oper == calc[i].enu_m_of_oper)
                        return calc[i].u_func(leaf, sche);

                break;
            }

            default: 
                return leaf;
        }
    }

    return leaf;
}


Le_af free_left(Le_af_arg)
{
    if(leaf->prev == NULL)  //first element
    {
        Le_af right = leaf->right;

        if(right != NULL)
            right->prev = NULL;

        fell_a_root(&(leaf->left));

        free(leaf);
        leaf = NULL;
        
        return right;
    }

    if(leaf->prev->left == leaf) //если наш лиf левый относительно своего предыдущего
        leaf->prev->left = leaf->right;

    else leaf->prev->right = leaf->right;

    if(leaf->right != NULL)
        leaf->right->prev = leaf->prev; //предыдущий у правого == предыдщуий у лифа

    Le_af right = leaf->right;
    fell_a_root(&(leaf->left));
    free(leaf);
                
    return right;
}

Le_af free_right(Le_af_arg)
{//поменять целиком основный лиф поменять у него райт например целиком на старый и не придется превы менять
    if(leaf->prev == NULL)  //first element
    {
        Le_af left = leaf->left;

        if(left != NULL)
            left->prev = NULL;

        fell_a_root(&(leaf->right));

        free(leaf);
        leaf = NULL;

        return left;
    }

    if(leaf->prev->left == leaf) //если наш лит левый относительно своего предыдущего
        leaf->prev->left = leaf->left;

    else leaf->prev->right = leaf->left;

    if(leaf->left != NULL)
        leaf->left->prev = leaf->prev; //предыдущий у правого == предыдщуий у лифа

    Le_af left = leaf->left;
    fell_a_root(&(leaf->right));
    free(leaf);

    return left;
}

void i_am_your_father(Le_af_arg, Le_af new_node)
{
    AsserT(leaf == NULL, );
    AsserT(new_node == NULL, );

    if(leaf->prev == NULL)
        return;

    new_node->prev = leaf->prev;

    if(leaf->prev->left == leaf)
        leaf->prev->left = new_node;

    else leaf->prev->right = new_node; 
}


Le_af u_add(Le_af_arg, int *sche)
{
    if(leaf->left->type == NUMBER && leaf->right->type == NUMBER)
    {
        (*sche)++;
        return create_and_destroy(leaf, leaf->left->value.num + leaf->right->value.num);
    }

    if(leaf->left->type == NUMBER)
        switch((int)sravn(leaf->left->value.num)) //преобразовываем левое значение в инт
        {
            case 0: //if left == 0:
                (*sche)++;
                return free_left(leaf);

            default: return leaf;
        }

    if(leaf->right->type == NUMBER)
        switch((int)sravn(leaf->right->value.num))//
        {
            case 0:
                (*sche)++;
                return free_right(leaf);
            
            default: return leaf;
        }

    return leaf;
}

Le_af u_mul(Le_af_arg, int *sche)
{   
    if(leaf->left->type == NUMBER && leaf->right->type == NUMBER)
    {
        (*sche)++;
        return create_and_destroy(leaf, leaf->left->value.num * leaf->right->value.num);
    }

    if(leaf->left->type == NUMBER)
        switch((int)sravn(leaf->left->value.num)) //преобразовываем левое значение в инт
        {
            case 0:
                (*sche)++;
                return create_and_destroy(leaf, 0);

            case 1:
                (*sche)++;
                return free_left(leaf);

            default: return leaf;
        }

    if(leaf->right->type == NUMBER)
        switch((int)sravn(leaf->right->value.num)) //преобразовываем левое значение в инт
        {
            case 0:
                (*sche)++;
                return create_and_destroy(leaf, 0);

            case 1:
                (*sche)++;
                return free_right(leaf);

            default: return leaf;
        }

    return leaf;
}

Le_af u_sub(Le_af_arg, int *sche)
{   
    if(leaf->left->type == NUMBER && leaf->right->type == NUMBER)
    {
        (*sche)++;
        return create_and_destroy(leaf, leaf->left->value.num - leaf->right->value.num);
    }

    if(leaf->left->type == NUMBER)
        switch((int)sravn(leaf->left->value.num))
        {
            case 0:
            {
                leaf->value.oper = OPER_mul;

                leaf->left->value.num = -1;

                (*sche)++;

                return leaf;
            }

            default: return leaf;
        }

    if(leaf->right->type == NUMBER)//all_good
        switch((int)sravn(leaf->right->value.num))
        {
            case 0:
                (*sche)++;
                return free_right(leaf);

            default: return leaf;
        }

    return leaf;
}

Le_af u_div(Le_af_arg, int *sche)
{   
    if(leaf->left->type == NUMBER && leaf->right->type == NUMBER)
    {
        if((int)sravn(leaf->right->value.num) == 0)
            return create_and_destroy(leaf, 88888888);

        (*sche)++;
        
        return create_and_destroy(leaf, leaf->left->value.num / leaf->right->value.num);
    }

    if(leaf->left->type == NUMBER)
        switch((int)sravn(leaf->left->value.num))
        {
            case 0:
                (*sche)++;
                return create_and_destroy(leaf, 0);

            default: return leaf;
        }

    if(leaf->right->type == NUMBER)//all_good
        switch((int)sravn(leaf->right->value.num))
        {
            case 0:
                (*sche)++;
                fprintf(stderr, "fucking kid\n");
                return create_and_destroy(leaf, 88888888);

            case 1:
                (*sche)++;
                return free_right(leaf);

            default: return leaf;
        }

    return leaf;
}

Le_af u_pow(Le_af_arg, int *sche)
{   
    if(leaf->left->type == NUMBER && leaf->right->type == NUMBER)
    {
        (*sche)++;
        return create_and_destroy(leaf, (int)pow(leaf->left->value.num, leaf->right->value.num));
    }

    if(leaf->left->type == NUMBER)
        switch((int)sravn(leaf->left->value.num))
        {
            case 0:
            {
                if(leaf->right->type == NUMBER)
                    if((int)sravn(leaf->right->value.num) == 0)
                    {
                        (*sche)++;
                        return create_and_destroy(leaf, 1);
                    }

                (*sche)++;

                return create_and_destroy(leaf, 0);
            }

            case 1:
                (*sche)++;
                return create_and_destroy(leaf, 1);

            default: return leaf;
        }

    if(leaf->right->type == NUMBER)//all_good
        switch((int)sravn(leaf->right->value.num))
        {
            case 0:
                (*sche)++;
                return create_and_destroy(leaf, 1);

            case 1:
                (*sche)++;
                return free_right(leaf);

            default: return leaf;
        }

    return leaf;
}


Le_af create_and_destroy(Le_af_arg, typ_of_x num)
{
    Le_af new_node = alloca_for_type(num);
    i_am_your_father(leaf, new_node);
    fell_a_root(&leaf);

    return new_node;
}
