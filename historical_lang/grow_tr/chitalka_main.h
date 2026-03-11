#ifndef CHITALKA_MAIN_H
#define CHITALKA_MAIN_H

#include "../M_Diff.h"

struct chitaemka
{
    const char* type_of_opera;

    size_t enu_m_of_oper;
};

Le_af Get_G(ar_get);

Le_af Get_E(ar_get);

Le_af Get_T(ar_get);

Le_af Get_P(ar_get);

Le_af Get_N(ar_get);

Le_af Get_default_func(ar_get);

Le_af Get_while(ar_get);

Le_af Get_if(ar_get);

Le_af Get_param(ar_get);

Le_af Get_Degree(ar_get);

Le_af Get_F_user(ar_get);

Le_af Get_Call(ar_get);

Le_af Get_args(ar_get);

Le_af Get_another(ar_get);

Le_af Get_param_in_gde_to(ar_get);

Le_af Get_ret(ar_get);

Le_af Get_logical_OR(ar_get);

Le_af Get_logical_AND(ar_get);

Le_af Get_logical_EQAally(ar_get);

Le_af Get_comparison(ar_get);

Le_af Get_defolt_Block(ar_get);

Le_af Get_Block_for_us_func(ar_get);

Le_af pusto(ar_get);

const char* what__printf(Le_af leaf);

int pre_order_print(Le_af root, ar_get);

void dump_tree(FILE* fp, Le_af leaf);

Le_af Get_Chain(ar_get);

Le_af create_connection_node();

Le_af create_func_T_node();

Le_af Get_solo_string(ar_get);

Le_af Get_printf(ar_get);


#endif