#include "chitalka_main.h"

    
Le_af Get_G(ar_get)
{
    DE_Bug;

    Le_af leaf = NULL;
    Le_af prev = NULL;
    Le_af root = NULL;

    while(CUR_ent.type != (size_t)END_OF_FILE)
    {
        // if(CUR_ent.type == USER_OPER)
        // {
        //     leaf = Get_F_user(ast);

        //     if(leaf == NULL)
        //         leaf = Get_Chain(ast);
        // }

        // else 
        leaf = Get_Chain(ast);

        if(leaf == NULL)
            return NULL;

        if(prev == NULL)
            root = leaf;

        else prev->right = leaf;

        prev = leaf;
    }

    return root;
}


Le_af Get_E(ar_get)
{
    DE_Bug;

    Le_af leaf = Get_T(ast);

    while(CUR_ent.type == OPERAT && (CUR_OPER == ADD_C || CUR_OPER == SUB_C))
    {
        Le_af leaf_opera = &CUR_ent;
        (ast->pose)++;
                
        Le_af leaf_2 = Get_T(ast);

        leaf_opera->left = leaf;
        leaf_opera->right = leaf_2;

        leaf = leaf_opera;
    }

    return leaf;
}


Le_af Get_T(ar_get)
{
    DE_Bug;

    Le_af leaf = Get_Degree(ast);

    while(CUR_ent.type == OPERAT && (CUR_OPER == MUL_C || CUR_OPER == DIV_C))
    {                
        Le_af leaf_opera = &CUR_ent;
        (ast->pose)++;
             
        Le_af leaf_2 = Get_Degree(ast);

        leaf_opera->left = leaf;
        leaf_opera->right = leaf_2;

        leaf = leaf_opera;
    }

    return leaf;
}


Le_af Get_P(ar_get)
{
    DE_Bug;

    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_L)
    {
        (ast->pose)++;

        Le_af leaf = Get_logical_OR(ast);
            
        if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R)
            (ast->pose)++;

        return leaf;
    }
        
    if(CUR_ent.type == USER_OPER)
        return Get_F_user(ast);

    if(CUR_ent.type == VARIA)
    {
        OBLAST_SEE;

        Le_af leaf = &CUR_ent;
        (ast->pose)++;
        return leaf;
    } // return Get_param(ast);

    return Get_N(ast);
}


Le_af Get_N(ar_get)
{
    DE_Bug;

    if(CUR_ent.type != NUMBER)
        return NULL;

    Le_af leaf = &CUR_ent;

    (ast->pose)++;
    return leaf;
}


Le_af Get_default_func(ar_get)
{    
    DE_Bug;

    Le_af new_node = &CUR_ent;
    (ast->pose)++;

    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_L)
    {
        (ast->pose)++;

        new_node->left = Get_logical_OR(ast); //read logical viragenie

        if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R)
            (ast->pose)++;

        else 
        {
            fprintf(stderr, "\n) RRR not found in Get_F in Get_default_func %s:%d\n\n", __FILE__, ast->pose);
            return NULL;
        }
    }

    else 
    {
        fprintf(stderr, "\n( LLL not found in Get_F in Get_default_func %s:%d\n\n", __FILE__, ast->pose);
        return NULL;
    }

    new_node->right = Get_defolt_Block(ast);

    return new_node;
}


Le_af Get_while(ar_get)
{
    DE_Bug;

    Le_af connect_leaf = create_connection_node();

    Le_af while_leaf = Get_default_func(ast);
    AsserT(while_leaf == NULL, NULL);

    connect_leaf->left = while_leaf;

    return connect_leaf;
}


Le_af Get_if(ar_get)
{
    DE_Bug;

    Le_af connect_leaf = create_connection_node();

    Le_af new_node_if = &CUR_ent; //сам if_ецкий
    (ast->pose)++;

    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_L)
    {
        // fprintf(stderr, "\nwe are in if^\n\n");
        (ast->pose)++;

        new_node_if->left = Get_logical_OR(ast); //read logical viragenie

        if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R)
            (ast->pose)++;

        else 
        {
            fprintf(stderr, "\n) RR not found in Get_F in SKOB_krug %s:%d\n\n", __FILE__, ast->pose);
            free(connect_leaf);
            return NULL;
        }
    }

    else 
    {
        fprintf(stderr, "\n( LL not found in Get_F in SKOB_krug %s:%d\n\n", __FILE__, ast->pose);
        free(connect_leaf);
        return NULL;
    }

    Le_af after_else_but_for_if = Get_defolt_Block(ast); //блок ифа

    if(CUR_ent.type == OPERAT && CUR_OPER == ELSE_C)
    {
        Le_af else_c = &CUR_ent;
        (ast->pose)++; //слева у елса параметры если иф

        Le_af right_else = Get_defolt_Block(ast); //block for else
        AsserT(right_else == NULL, NULL);

        new_node_if->right = else_c;

        else_c->right = right_else;

        else_c->left = after_else_but_for_if;
    }

    else new_node_if->right = after_else_but_for_if;

    connect_leaf->left = new_node_if;

    return connect_leaf;
}


Le_af Get_param(ar_get)
{
    DE_Bug;

    // fprintf(stderr, "\nGet_param: creating new steck for function params\n\n");

    if(CUR_ent.type != VARIA)
    {
        fprintf(stderr, "\n in Get_param arguments_is not found\n\n");
        return NULL;
    }
    
    table_name *str_uct = (table_name*)calloc((size_t)(ast->max_num + 10), sizeof(table_name));
    AsserT(str_uct == NULL, NULL);

    int i_i = 0;
    ast->var_num = 0;

    if(ast->var_ble_tabl.size != 0)
    {
        fprintf(stderr, "\nCopying global vars \n\n");

        table_name* reserve_stk = stack_pop(&ast->var_ble_tabl); //достаем предыдущую память и копируем глобальные перемнные

        for(i_i = 0; i_i < ast->max_num && reserve_stk[i_i].name != NULL; ++i_i)
        {
            if(reserve_stk[i_i].est_net == GLOBAL)
            {
                str_uct[i_i].name = strdup(reserve_stk[i_i].name);
                str_uct[i_i].est_net = GLOBAL;
                str_uct[i_i].size_tabl = reserve_stk[i_i].size_tabl;

                (ast->var_num)++;
            }

            else
            {
                fprintf(stderr, "\ncant init if you are not in global\n\n");
                return NULL;
            }
        }

        //скопировали предыдущую global область видимости and cashback old
        stack_push(&ast->var_ble_tabl, reserve_stk);
    }


    Le_af first_node = &CUR_ent;
    Le_af cure = first_node;

    // str_uct[i_i] = {.est_net = LOCAL, .name = strdup(CUR_ent.value.x), .size_tabl = (size_t)ast->var_num};

    str_uct[i_i].est_net = LOCAL;
    str_uct[i_i].name = strdup(CUR_ent.value.x);
    str_uct[i_i].size_tabl = (size_t)ast->var_num;

    // fprintf(stderr, "\n add param[%d]: --%s-- (LOCAL)\n\n", i_i, str_uct[i_i].name);

    i_i++;

    (ast->var_num)++;
    
    (ast->pose)++;

    while(!(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R))
    {
        if(CUR_ent.type == VARIA)
        {
            Le_af new_varia = &CUR_ent;

            cure->left = new_varia;

            str_uct[i_i] = {.est_net = LOCAL, .name = strdup(CUR_ent.value.x), .size_tabl = (size_t)ast->var_num};
            i_i++;
            (ast->var_num)++;
                
            cure = new_varia;

            (ast->pose)++;
        }

        else 
        {
            fprintf(stderr, "\n woooow Get_param without varia schock\n\n");
            return NULL;
        }
    }

    str_uct[0].size_tabl = (size_t)ast->var_num;

    // fprintf(stderr, "\nstack_push with %zu variables to stack\n\n", str_uct[0].size_tabl);
    // fprintf(stderr, "  Stack size before stack_push: %zd\n", ast->var_ble_tabl.size);

    stack_push(&ast->var_ble_tabl, str_uct); //обновляем область видимости

    // fprintf(stderr, "\nStack size after stack_push: %zd\n\n", ast->var_ble_tabl.size);

    return first_node;
}


Le_af Get_Degree(ar_get)
{
    DE_Bug;

    Le_af left = Get_P(ast);

        while(CUR_ent.type == OPERAT && (CUR_OPER == POW_C))
        {
            Le_af leaf_opera = &CUR_ent;

            (ast->pose)++;
            
            leaf_opera->right = Get_P(ast);
            leaf_opera->left  = left;

            left = leaf_opera;
        }

    return left;
}


Le_af Get_F_user(ar_get)
{
    DE_Bug;

    if(ast->pose >= ast->max_pose)
    {
        fprintf(stderr, "Get_F_user: out of bounds\n");
        return NULL;
    }

    Le_af connect_1 = create_connection_node();


    Le_af func_op = create_func_T_node();

    int start_pos_of_func = (ast->pose);

    Le_af leaf_us = &CUR_ent; //func
    char* name_of_funs = strdup(CUR_ent.value.us_op);
    (ast->pose)++;


    Le_af cnct_2 = create_connection_node();


    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_L)
    {
        (ast->pose)++;

        int p_roverka = ast->pose; //после открывающейся скобочки   
        while(!(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R) && (ast->pose) < ast->max_pose)
                (ast->pose)++; 
        
        (ast->pose)++; //некст после кркуглой
        if(ast->pose < ast->max_pose && (ast->tok_mas[(ast->pose)].type == Z_NAK && ast->tok_mas[(ast->pose)].value.oper == SKOB_figu_L))  //значит это объявдение функции
        {
            (ast->pose) = p_roverka;
            int b_e = being_before_li(ast, name_of_funs);//проверка была инициализирована до = плохо

            if(b_e != -1)
            {
                fprintf(stderr, "\nin Get_F_user double func inizialization^ its peregruzka\n\n");
                return NULL;
            }
            
            
            Le_af param_s = Get_param(ast); //вызываем чтение только юзерских вариа //обработка аргуемнтов


            ast->userz_func[ast->func_num].name = strdup(name_of_funs); //инициализированные функции
            ast->userz_func[ast->func_num].size_tabl = (size_t)ast->var_num; //считаем в гетпарамс 
            ast->func_num++;

            if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R)
                (ast->pose)++;

            else fprintf(stderr, "\n) not found in Get_F_user in ')' %s:%d\n\n", __FILE__, ast->pose);


            Le_af body_f = Get_Block_for_us_func(ast); //фтгурное тело


            connect_1->left = func_op;

            func_op->left = leaf_us;
            func_op->right = cnct_2;

            cnct_2->left = param_s;
            cnct_2->right = body_f;

            return connect_1;
        }

        else 
        {
            ast->pose = start_pos_of_func;
            return NULL;
        }

    }

    else 
    {
        fprintf(stderr, "\n( not found in Get_F_user in SKOB_krug = '(' %s:%d\n\n", __FILE__, ast->pose);
        return NULL;
    }

}


Le_af Get_Call(ar_get)
{
    DE_Bug;
    OBLAST_SEE;
    Le_af leaf_is_func = &CUR_ent;

    (ast->pose)++;
    if(!(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_L))
    {
        fprintf(stderr, "\n( LLL not found in Get_Call in ')' %s:%d\n\n", __FILE__, ast->pose);
        return NULL;
    }
    (ast->pose)++;

    Le_af args_of_func = Get_args(ast);
    leaf_is_func->left = args_of_func;

    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R)
    {
        (ast->pose)++;
        return leaf_is_func;
    }

    else fprintf(stderr, "\n) RRR not found in Get_Call in ')' %s:%d\n\n", __FILE__, ast->pose);

    return NULL;
}


Le_af Get_args(ar_get)
{
    DE_Bug;

    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R)
        return pusto(ast);

    Le_af leaf_args = Get_logical_OR(ast);//проверка области видимости производится внутри

    while(!(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_krug_R))
    {
        if(CUR_ent.type == Z_NAK && CUR_OPER == ZAPYTAYA)
        {
            Le_af leaf = &CUR_ent; //новая нода это запятая связующая
            (ast->pose)++;

            leaf->right = Get_logical_OR(ast); //справа следующая + загоняем ее в стек так как она нова локальная
            leaf->left = leaf_args; //левая -- первый параметр
            
            leaf_args = leaf;
        }

        else fprintf(stderr, "\n woooow Get_args without ',' == schock\n\n");
    }
    //если это не число значит проверяем на область вилимости тонее если это вариа

    return leaf_args;
}


Le_af Get_Chain(ar_get)
{
    DE_Bug;

    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_figu_R)
    {
        // fprintf(stderr, "\nfirst try Get_Chain catch SKOB_figu_R and return NULL\n\n");
        return NULL;
    }
    
    Le_af first_leaf = Get_another(ast);
    if(first_leaf == NULL)
    {
        if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_figu_R)
        {
            // fprintf(stderr, "\nsecond try Get_Chain catch SKOB_figu_R and return NULL\n\n");
            return NULL;
        }
    
        return NULL;
    }

    Le_af cur = first_leaf;

    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_figu_R)
    {
        // fprintf(stderr, "\nGet_Chain catch SKOB_figu_R and return first_leaf\n\n");
        return first_leaf;
    }
    
    
    while(!(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_figu_R))
    {    
     
        Le_af next_leaf = Get_another(ast);
        if(next_leaf == NULL)
        {
            if(CUR_ent.type == Z_NAK && CUR_ent.value.oper == SKOB_figu_R)
                break;

            //fprintf(stderr, "\nGet_Chain catch NULL next_leaf = Get_another(ast\n\n");
            return first_leaf;
        }

        cur->right = next_leaf;
        cur = next_leaf;
    }

    // if(CUR_ent.type == Z_NAK && CUR_ent.value.oper == SKOB_figu_R)
    //     fprintf(stderr, "\n} RRR found in Get_Chain\n\n");
    
    return first_leaf;
}


Le_af Get_another(ar_get)
{
    DE_Bug;
    Le_af leaf = NULL;


    if(CUR_ent.type == OPERAT && CUR_OPER == IF_C)
        leaf = Get_if(ast);


    else if(CUR_ent.type == OPERAT && CUR_OPER == WHILE_C)
            leaf = Get_while(ast);


    else if(CUR_ent.type == OPERAT && CUR_OPER == RET_C)
            leaf = Get_ret(ast);


    else if(CUR_ent.type == OPERAT && CUR_OPER == IN_IT)
            leaf = Get_intit_var(ast);


    else if(CUR_ent.type == OPERAT && CUR_OPER == PRINT_F)
            leaf = Get_printf(ast);


    else if(CUR_ent.type == OPERAT && CUR_OPER == SQRT_C)
            leaf = Get_printf(ast);

    
    else if(CUR_ent.type == USER_OPER)
        {
            leaf = Get_F_user(ast);

            if(leaf == NULL)
            {
                leaf = Get_Call(ast);//func_user in use
                AsserT(leaf == NULL, NULL);

                if(CUR_ent.type == Z_NAK && CUR_OPER == TOCHKA_ZAP)
                {        
                    Le_af znak = &CUR_ent; 
                    znak->left = leaf;
                    (ast->pose)++;

                    leaf = znak;
                }

                else 
                {
                    fprintf(stderr, "\ntochka_zap is not found in line, %s:%d\n\n", __FILE__, __LINE__);
                    return NULL;
                }
            }

            return leaf;
        }

        
    else if(CUR_ent.type == VARIA)
            leaf = Get_param_in_gde_to(ast); // == asignment


    else 
        {
            leaf = Get_logical_OR(ast);


            if(leaf != NULL)
            {
                if(CUR_ent.type == Z_NAK && CUR_OPER == TOCHKA_ZAP)
                {        
                    Le_af znak = &CUR_ent; 
                    (ast->pose)++;

                    znak->left = leaf;

                    return znak;
                }

                else 
                {
                    fprintf(stderr, "\n TOCHKA_ZAP is not found\n\n");
                    return NULL;
                }

            }
        }

    return leaf;
}


Le_af Get_printf(ar_get)
{
    DE_Bug;

    Le_af pr_int = &CUR_ent;
    (ast->pose)++;

    pr_int->left = Get_solo_string(ast);

    if(CUR_ent.type == Z_NAK && CUR_OPER == TOCHKA_ZAP)
    {        
        Le_af znak = &CUR_ent; 
        (ast->pose)++;

        znak->left = pr_int;

        return znak;
    }

    return NULL;
}


Le_af Get_solo_string(ar_get)
{
    DE_Bug;

    Le_af leaf = &CUR_ent;

    if(leaf->type == USER_OPER)
    {
        leaf = Get_Call(ast);//func_user in use
        AsserT(leaf == NULL, NULL);
    }

    else if(CUR_ent.type == OPERAT && CUR_OPER == SCAN_C)
         {
            leaf = &CUR_ent;
            (ast->pose)++;
         }

    else if(CUR_ent.type == OPERAT && CUR_OPER == SQRT_C)
         {
            leaf = &CUR_ent;
            (ast->pose)++;

            leaf->left = Get_solo_string(ast);
         }
         
    else
        leaf = Get_logical_OR(ast);


    return leaf;
}


Le_af Get_param_in_gde_to(ar_get)
{
    DE_Bug;
    OBLAST_SEE;

    Le_af var = &CUR_ent;
    (ast->pose)++;

    if(!(CUR_ent.type == OPERAT && CUR_OPER == RAVNO))
        return var;

    Le_af ravno = &CUR_ent;
    (ast->pose)++;

    Le_af value = Get_solo_string(ast);

    ravno->left = var;
    ravno->right = value;

    if(!(CUR_ent.type == Z_NAK && CUR_OPER == TOCHKA_ZAP))
    {
        fprintf(stderr, "\n TOCHKA_ZAP нету в Get_param_in_gde_to \n\n");
        return ravno;
    }
    
    Le_af tochkazap =  &CUR_ent;
    (ast->pose)++;
    
    tochkazap->left = ravno;
    
    return tochkazap;
}


Le_af Get_ret(ar_get)
{
    DE_Bug;

    Le_af reter = &CUR_ent;
    (ast->pose)++;

    Le_af re_val = Get_logical_OR(ast);
    AsserT(re_val == NULL, NULL); //обязательно функции что-то возвращают

    reter->left = re_val;

    if(!(CUR_ent.type == Z_NAK && CUR_OPER == TOCHKA_ZAP))
    {
        fprintf(stderr, "\n tochka zap is otsutsctvuet in Get_ret\n\n");
        return NULL;
    }

    Le_af tchka_zap = &CUR_ent;
    (ast->pose)++;

    tchka_zap->left = reter;

    stack_pop(&ast->var_ble_tabl);

    return tchka_zap;
}


Le_af Get_logical_OR(ar_get)
{
    DE_Bug;
    OBLAST_SEE;

    Le_af leaf_left = Get_logical_AND(ast);

    while(CUR_ent.type == Z_NAK && CUR_OPER == LOG_OR)
    {
        Le_af leaf = &CUR_ent;
        (ast->pose)++;

        Le_af leaf_right = Get_logical_AND(ast);

        leaf->left = leaf_left;
        leaf->right = leaf_right;

        leaf_left = leaf;
    }

    return leaf_left;
}


Le_af Get_logical_AND(ar_get)
{
    DE_Bug;
    OBLAST_SEE;
    
    Le_af leaf_left = Get_logical_EQAally(ast);

    while(CUR_ent.type == Z_NAK && CUR_OPER == LOG_AND)
    {
        Le_af leaf = &CUR_ent;
        (ast->pose)++;

        Le_af leaf_right = Get_logical_EQAally(ast);

        leaf->left = leaf_left;
        leaf->right = leaf_right;

        leaf_left = leaf;
    }

    return leaf_left;
}


Le_af Get_logical_EQAally(ar_get)
{
    DE_Bug;
    OBLAST_SEE;

    Le_af leaf_left = Get_comparison(ast);

    while(CUR_ent.type == Z_NAK && (CUR_OPER == EQUAL_C || CUR_OPER == N_EQUAL_C))
    {
        Le_af leaf = &(CUR_ent);
        (ast->pose)++;

        Le_af leaf_right = Get_comparison(ast);

        leaf->left = leaf_left;
        leaf->right = leaf_right;

        leaf_left = leaf;
    }

    return leaf_left;
}


Le_af Get_comparison(ar_get)
{
    DE_Bug;
    OBLAST_SEE;

    Le_af leaf_left = Get_E(ast);

    while(CUR_ent.type == Z_NAK && (CUR_OPER == L_bigger_R || CUR_OPER == L_smaller_R \
                                  || CUR_OPER == L_E_bigger || CUR_OPER == L_E_smaller))
    {
        Le_af leaf = &(CUR_ent);
        (ast->pose)++;

        Le_af leaf_right = Get_E(ast);

        leaf->left = leaf_left;
        leaf->right = leaf_right;

        leaf_left = leaf;
    }

    return leaf_left;
}


Le_af Get_defolt_Block(ar_get)  //для ифа и вайла копируем пердыдущую облысть видимости в новую и добавляем еще при выозде стекпоп 
{                               //для функции -- просто обновляем последний массив в стеке
    DE_Bug;

    //fprintf(stderr, "\nGet_defolt_Block: stack size before = %zd\n\n", ast->var_ble_tabl.size);

    ///while___
    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_figu_L)
    {
        (ast->pose)++; //skip skobki

        if(ast->var_ble_tabl.size != 0)
        {
            // fprintf(stderr, "\n copy_steck size != 0\n\n");

            table_name* cope_steck = stack_pop(&ast->var_ble_tabl);
            int num = (int)cope_steck[0].size_tabl;

            table_name* new_stk = (table_name*)calloc((size_t)ast->max_num, sizeof(table_name));
            AsserT(new_stk == NULL, NULL);

            for(int i = 0; i < num; ++i)
            {
                new_stk[i].est_net = cope_steck[i].est_net;
                new_stk[i].name = strdup(cope_steck[i].name);
                new_stk[i].size_tabl = cope_steck[i].size_tabl;

                // fprintf(stderr, "\nCopy var[%d]: -%s-\n\n", i, new_stk[i].name);
            }

            new_stk[0].size_tabl = (size_t)num;

            stack_push(&ast->var_ble_tabl, cope_steck);
            stack_push(&ast->var_ble_tabl, new_stk);


            // fprintf(stderr, "\nNew stack pushed, total size now = %zd\n\n", ast->var_ble_tabl.size);
            

            Le_af leaf = Get_Chain(ast);


            if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_figu_R)
                (ast->pose)++;
            
            else
            {
                stack_pop(&ast->var_ble_tabl);
                fprintf(stderr, "\nSKOB_figu_R is not found after block\n\n");
                return NULL;
            }

            stack_pop(&ast->var_ble_tabl);//удаляем область видимости

            //fprintf(stderr, "\nBlock ended  stack_pop  size now = %zd\n\n", ast->var_ble_tabl.size);

            return leaf;
        }

        else fprintf(stderr, "\nsteck is zero for if/while\n\n");
    }
    fprintf(stderr, "SKOB_figu_LLL is not find in Get_defolt_Block\n\n line %d", __LINE__);

    return NULL;
}


Le_af Get_Block_for_us_func(ar_get)  //для ифа и вайла копируем пердыдущую облысть видимости в новую и добавляем еще при выозде стекпоп 
{                               //для функции -- просто обновляем последний массив в стеке а при выходе вытаскиваем 
    DE_Bug;

    if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_figu_L)
    {
        (ast->pose)++; //skip skobki

        Le_af leaf = Get_Chain(ast);

        // stack_pop(&ast->var_ble_tabl);//удаляем область видимости
        if(CUR_ent.type == Z_NAK && CUR_OPER == SKOB_figu_R)
            (ast->pose)++;

        else fprintf(stderr, "\nGet_Block_for_us_func SKOB_figu_R uined\n\n");

        return leaf;
    }
    fprintf(stderr, "SKOB_figu_LLL is not find in Get_Block_for_us_func\n\n line %d", __LINE__);

    return NULL;
}


Le_af create_connection_node()
{
    Le_af cnct = (Le_af)calloc(1, sizeof(leaf));
    AsserT(cnct == NULL, NULL);

    cnct->left = NULL;
    cnct->right = NULL;
    cnct->prev = NULL;

    cnct->lines_in_Rim = 0;
    cnct->type = CONECTION;
    cnct->value.oper = CONNEC_T;

    return cnct;
}


Le_af create_func_T_node()
{
    Le_af cnct = (Le_af)calloc(1, sizeof(leaf));
    AsserT(cnct == NULL, NULL);

    cnct->left = NULL;
    cnct->right = NULL;
    cnct->prev = NULL;

    cnct->lines_in_Rim = 0;
    cnct->type = OPERAT;
    cnct->value.oper = FUNC_C;

    return cnct;
}


Le_af pusto(ar_get)
{
    Le_af pustota = &CUR_ent;

    pustota->type = NO_ARGS;
    pustota->value.x = "no args";

    return pustota;
}


int pre_order_print(Le_af root, ar_get)
{
    FILE* fp = fopen(ast->file_name, "w");
    AsserT(fp == NULL, -1);

    dump_tree(fp, root);

    fclose(fp);

    return 0;
}


void dump_tree(FILE* fp, Le_af leaf)
{
    if(leaf == NULL)
    {
        fprintf(fp, " nil");
        return ;
    }

    fprintf(fp, "(");

    switch(leaf->type)
    {

        case Z_NAK:
            fprintf(fp, "op: \"%s\" ", what__printf(leaf));
        break;

        case OPERAT:
            fprintf(fp, "op: \"%s\" ", what__printf(leaf));
        break;

        case VARIA:
            fprintf(fp, "var: \"%s\" ", leaf->value.x);
        break;

        case CONECTION:
            fprintf(fp, "cnct: \"cnct\" ");
        break;

        case USER_OPER:
            fprintf(fp, "func: \"%s\" ", leaf->value.us_op);
        break;

        case NUMBER:
            fprintf(fp, "num: \"%.0lf\" ", leaf->value.num);
        break;

        default: 
            fprintf(fp, " unluck");
        break;

    }

    dump_tree(fp, leaf->left );
    dump_tree(fp, leaf->right);

    fprintf(fp, ")");
}


static struct command_s translit[] = {
    
    {"if", IF_C},
    {"else", ELSE_C},
    {"while", WHILE_C},
    {"return", RET_C},
    {"+", ADD_C},
    {"^", POW_C},
    {"/", DIV_C},
    {"in", SCAN_C},
    {"print", PRINT_F},
    {"sqrt", SQRT_C},

    {"*", MUL_C},

    {"-", SUB_C},
    {"init", IN_IT},
    {"=", RAVNO},
    {"func", FUNC_C},
    {";", TOCHKA_ZAP},

    {"(", SKOB_krug_L},
    {")", SKOB_krug_R},
    {"{", SKOB_figu_L},
    {"}", SKOB_figu_R},
    {"==", EQUAL_C},
    {",", ZAPYTAYA},

    {">=", L_E_bigger},
    {">", L_bigger_R},

    {"<=", L_E_smaller},
    {"<", L_smaller_R},
    
    {"!=", N_EQUAL_C},
    {"∧", LOG_AND},
    {"!∧", LOG_OR},

};

const char* what__printf(Le_af leaf)
{
    for(int i = 0; i < (int)(sizeof(translit) / sizeof(translit[0])); ++i)
        if(leaf->value.oper == translit[i].e_num)
            return translit[i].value;

    return "unluck i dont know this func";
}
