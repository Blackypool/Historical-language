#include "seeing_zone.h"


Le_af Get_intit_var(ar_get)
{   
    DE_Bug;

    Le_af init = &CUR_ent; //init

    (ast->pose)++;
    if(CUR_ent.type != VARIA)
    {
        fprintf(stderr, "\nwhat you are initing br\n\n");
        return NULL;
    }

    // fprintf(stderr, "\nI want add --%s--\n\n", CUR_ent.value.x);

    char* name_var = strdup(CUR_ent.value.x);
    Le_af var = &CUR_ent;
    (ast->pose)++;

    int global_nado = 0; 
    int size_stk = (int)ast->var_ble_tabl.size;

    if(size_stk == 0)//Если стек пустой значит точно Глобал ведь при инициализации функции он бы создался
        global_nado = GLOBAL;

    if(size_stk > 1)
        global_nado = LOCAL;

    if(size_stk == 1)     //Если в стеке 1 массив структур и в нем лежит Глобал, значит мы в Глобал 
    {                                   //ведь единственный стек с глобальными переменнными создается в глобальной области видимости
        table_name *chek_gl_li = stack_pop(&ast->var_ble_tabl);

        global_nado = chek_gl_li[0].est_net; //in macross GLOBAL = 1,  LOCAL = 0;

        stack_push(&ast->var_ble_tabl, chek_gl_li); //comeback
    }

    //chek global is already
    if(size_stk > 0)//if >0 значит просто добавляем элемент с меткой глобала
    {
        table_name *add_in_local = stack_pop(&ast->var_ble_tabl);
        int num = (int)add_in_local[0].size_tabl;

        add_in_local[num].name = name_var; //пополняем стек
        add_in_local[num].est_net = global_nado;

        add_in_local[0].size_tabl = (size_t)(num + 1);
        
        stack_push(&ast->var_ble_tabl, add_in_local); //comeback

        // fprintf(stderr, "\n add salam in size>0\n\n");
    }

    if(size_stk == 0) //new steck
    {
        table_name *new_stk = (table_name*)calloc((size_t)ast->max_num, sizeof(table_name));
        AsserT(new_stk == NULL, NULL);

        new_stk[0].est_net = GLOBAL;
        new_stk[0].size_tabl = 1;
        new_stk[0].name = name_var;

        stack_push(&ast->var_ble_tabl, new_stk);

        // fprintf(stderr, "\n add salam in size == 0");
    }

    //add in steck, next = obrabotka

    if(CUR_ent.type != OPERAT || CUR_ent.value.oper != RAVNO)
    {
        fprintf(stderr, "\nravno is netu in Get_intit_var\n\n");
        free(name_var);
        return NULL;
    }
    
    Le_af ravno = &CUR_ent;
    (ast->pose)++;

    Le_af value = Get_solo_string(ast);
    AsserT(value == NULL, NULL);

    ravno->left = var;
    ravno->right = value;

    
    if(!(CUR_ent.type == Z_NAK && CUR_ent.value.oper == TOCHKA_ZAP))
    {
        free(name_var);
        fprintf(stderr, "\nTOCHKA_ZAP is netu in Get_intit_var\n\n");
        return NULL;
    }

    Le_af tchkazap = &CUR_ent;
    (ast->pose)++;

    tchkazap->left = init;

    init->left = ravno;

    return tchkazap;
}


int being_before_li(ar_get, const char* what_the_name)
{
    for(int i = 0; i < ast->max_func_num && ast->userz_func[i].name != NULL; ++i)
        if(strcmp(ast->userz_func[i].name, what_the_name) == 0)
            return i;

    return -1;
}


int see_var_li(ar_get)
{    
    // fprintf(stderr, "\nsee_var_li Stack size: %zd\n\n", ast->var_ble_tabl.size);

    int proverka = 0;
    if(CUR_ent.type == USER_OPER)
    {
        int b_e = being_before_li(ast, CUR_ent.value.us_op);//проверка не была инициализирована до = плохо
        if(b_e == -1)
        {
            fprintf(stderr, "\nUSER_OPER is not opredeleno in ==see_var_li==\n\n");
            return -1;
        }
    }

    if(CUR_ent.type == VARIA)
    {
        if(ast->var_ble_tabl.size != 0)
        {
            table_name* reserve_stk = stack_pop(&ast->var_ble_tabl); //достаем предыдущую память и копируем глобальные перемнные
            for(int i = 0; i < ast->max_num && reserve_stk[i].name != NULL; ++i)
            {
                if(strcmp(CUR_ent.value.x, reserve_stk[i].name) == 0)
                {
                    stack_push(&ast->var_ble_tabl, reserve_stk);
                    return i;
                }
            }
            fprintf(stderr, "\nnot found varia in steck\n\n");
            stack_push(&ast->var_ble_tabl, reserve_stk);
            return -1;
        }

        else 
        {
            fprintf(stderr, "alooo steck is have zero params");
            return -1;
        }
    }

    return proverka;
}
