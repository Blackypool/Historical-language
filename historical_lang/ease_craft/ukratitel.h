#ifndef SOKRATITEL_H
#define SOKRATITEL_H

#include "M_Diff.h"

#define Le_af_arg struct leaf* leaf
typedef struct leaf* (*ukrot_func)(struct leaf* leaf, int *sche);


struct ukrat_enum
{
    size_t enu_m_of_oper;

    ukrot_func u_func;
};

void too_easy(Le_af_arg);

void rekrut_for_ukrat(Le_af_arg, int *sche);
Le_af ukratitel(Le_af_arg, int *sche);

typ_of_x sravn(typ_of_x arg);

Le_af free_left(Le_af_arg);
Le_af free_right(Le_af_arg);

//вдруг первый -- корень

Le_af u_pow(Le_af_arg, int *sche);
Le_af u_div(Le_af_arg, int *sche);
Le_af u_sub(Le_af_arg, int *sche);
Le_af u_mul(Le_af_arg, int *sche);
Le_af u_add(Le_af_arg, int *sche);

//отрицательные чисоа схавать бы


#endif