#include "read_tree.h"
//в лексическом анализе надо сразу указывать испольщуется функция или инициалиируется
//то есть func->fact->param -- init
// fact->param -- in use

//в функции хранить указатель на переменные?!?!??!?

//PUSHREG DX FOR FUNC
#define PR_ASM \
        Asm_expression(fp, leaf->left, ast); \
        Asm_expression(fp, leaf->right, ast);

#define Debug \
        // fprintf(stderr, "\n====FUNC_%s====  type = -%zu-\n\n", __func__, leaf->type);


static struct znaki translit[] = {

    {"ADD\n", ADD_C},
    {"POW\n", POW_C},
    {"DIV\n", DIV_C},
    {"MUL\n", MUL_C},
    {"SUB\n", SUB_C},

};


int asm_main(FILE* fp, Le_af root, ar_get)
{
    ast->Adress_next = 0;
    ast->func_num = 0;

    Asm_expression(fp, root, ast);

    fprintf(fp, "HLT");

    return 1;
}


int asm_post_or(Le_af leaf)
{
    Debug;

    for(int i = 0; i < (int)(sizeof(translit) / sizeof(translit[0])); ++i)
        if(leaf->value.oper == (size_t)translit[i].e_num)
            return i;

    return -1;
}


void operat_ptinting(FILE* fp, Le_af leaf, ar_get)
{
    Debug;

    int i = asm_post_or(leaf);
    if(i != -1)
    {
        PR_ASM; //требующие постордер функции
        fprintf(fp, "%s", translit[i].value);
        return ;
    }

    Asm_another(fp, leaf, ast); //остальные оперции
}


void Asm_another(FILE* fp, Le_af leaf, ar_get)
{
    if(leaf == NULL)
        return ;

    if(leaf->value.oper == ZAPYTAYA)
        return ;

    Debug;

        if(leaf->type == OPERAT)
        {
            //fprintf(stderr, "\n\n OPERAT poteralsa with enum == %zu \n\n\n", leaf->value.oper);
            switch(leaf->value.oper)
            {
                case TOCHKA_ZAP:
                    PR_ASM;
                break;

                case USER_OPER:
                    user_oper_init(fp, leaf, ast); //инициализация функции пользователя
                break;

                case IF_C:
                    Asm_if_cmd(fp, leaf, ast);
                break;

                case RET_C:
                    Asm_expression(fp, leaf->left, ast);
                    fprintf(fp, "POPREG DX\n");
                    fprintf(fp, "RET\n");
                    stack_pop(&ast->var_ble_tabl);
                break;

                case WHILE_C:
                    Asm_while_cmd(fp, leaf, ast);
                break;

                case ELSE_C:
                    fprintf(stderr, "\nOKAK else without if_eckiy?!\n\n");
                break;

                case IN_IT:
                    Asm_init(arg_s);
                break;

                case RAVNO:
                    Asm_ass_ignment(arg_s);
                break;

                case LOG_AND:
                    Asm_logical_and(arg_s);
                break;

                case LOG_OR:
                    Asm_logical_or(arg_s);
                break;

                case PRINT_F:
                    Asm_expression(fp, leaf->left, ast);
                    fprintf(fp, "OUT\n");
                break;

                case SQRT_C:
                    Asm_expression(fp, leaf->left, ast);
                    fprintf(fp, "SQRT\n");
                break;

                case SCAN_C:
                    fprintf(fp, "INT\n");
                    fprintf(fp, "PUSHREG BX\n");
                    fprintf(fp, "POPREG BX\n");

                case EQUAL_C:
                case L_E_bigger:
                case L_bigger_R:
                case L_E_smaller:
                case L_smaller_R:
                case N_EQUAL_C:

                bear_gammy_jump_func(fp, leaf, ast);

                break;

                default:
                    fprintf(stderr, "\n%zu unluck Asm_another Asm_another Asm_another\n\n", leaf->value.oper);
                break;
            }
        }
}


void user_oper_init(Arg_s)
{
    Debug;
    (ast->func_num)++;
    //leaf == func == operat
    //leaf->left == name of func
    //leaf->right == connect
    //connect->left->left->left == params
    //connect->right == body

    Le_af name_of_func = leaf->left;
    Le_af connect = leaf->right;
    Le_af body = connect->right;

    int func_id = ast->init_num;
    (ast->init_num)++;

    /////save func_name
    ast->userz_func[func_id].name = strdup(name_of_func->value.us_op);

    //ffor seeing params
    table_name* param_array = (table_name*)calloc((size_t)ast->max_num, sizeof(table_name));
    AsserT(param_array == NULL, );

    //func factorial (param1 param2) {body}

    //////////////////
    Le_af param = connect->left;
    int i = 0;
    while(param != NULL) //колво парам
    {
        param_array[i].name = strdup(param->value.x);
        param_array[i].num_param = i;
        param_array[i].adress = -1;

        param = param->left;
        ++i;
    }

    ast->userz_func[func_id].size_tabl = (size_t)i;  //num of params
    ast->userz_func[func_id].init_params = param_array;  //massiva wiyh info about params
    //////////////////
    
    ast->userz_func[func_id].adress = ast->func_num;  //адресс функции == номер метки на будущее
    
    int start_of_func = (ast->func_num);
    (ast->func_num)++;
    
    int end_of_func = (ast->func_num);
    (ast->func_num)++;

    // func
    fprintf(fp, "JMP :%d\n", end_of_func);  //init перепрыгиваем внутри основного кода 
    fprintf(fp, ":%d\n", start_of_func); //lable    //сюда будет колл

    // (
    func_open_space(connect, ast, i, func_id);   //парамс чек+ инит адреса
    // )

    // {
    Asm_expression(fp, body, ast);      //body
    fprintf(fp, "JMP :%d\n", end_of_func); //в конец     уже есть ретерн 
    // }

    fprintf(fp, ":%d\n", end_of_func);
}


void func_open_space(Le_af leaf, ar_get, int how_much_func, int num_func)
{
    Debug;

    /////leaf == connect;      all params in ->left
    // need new steck

    table_name* new_space = (table_name*)calloc((size_t)ast->max_num, sizeof(table_name));
    AsserT(new_space == NULL, );

    int i_i = 0;
    if(ast->var_ble_tabl.size == 1) //не может быть больше in time init func
    {
        table_name* reserve = stack_pop(&ast->var_ble_tabl);
        for(; i_i < ast->max_num && reserve[i_i].name != NULL; ++i_i)
        {
            new_space[i_i].adress = reserve[i_i].adress;
            new_space[i_i].est_net = reserve[i_i].est_net;
            new_space[i_i].name = strdup(reserve[i_i].name);
            new_space[i_i].size_tabl = reserve[i_i].size_tabl;
            new_space[i_i].num_param = -1;
        }
        stack_push(&ast->var_ble_tabl, reserve);
    }

    //если надо было перекопировали всю предыдущую облась видимости
    //так как мы не можем инициализировать функцию в других места кроме глобальных значит перекопироваться должеон именно глобальный стек если он есть а если есть только 1 стек то он точно глобальный
    
    Le_af cur = leaf->left;
    for(int i = 0; i < how_much_func; ++i) //добавляем новые элементы инициализированные внутри вызова то есть в круглых скобочках
    {
        ast->userz_func[num_func].init_params[i].adress = ast->Adress_next;

        new_space[i_i].adress = ast->Adress_next;
        (ast->Adress_next)++;

        new_space[i_i].est_net = LOCAL;
        new_space[i_i].name = strdup(cur->value.x);

        cur = cur->left;
        ++i_i;
    }

    new_space[0].size_tabl = (size_t)i_i;

    stack_push(&ast->var_ble_tabl, new_space);
}


void Asm_init(Arg_s)
{
    Debug;

    Le_af ass_ignment = leaf->left;
    Le_af val = ass_ignment->left;

    char* name_var = strdup(val->value.x);


    int global_nado = 0; 
    int size_stk = (int)ast->var_ble_tabl.size;

    if(size_stk == 0)
        global_nado = GLOBAL;

    if(size_stk > 1)
        global_nado = LOCAL;

    if(size_stk == 1)
    {
        table_name *chek_gl_li = stack_pop(&ast->var_ble_tabl);

        global_nado = chek_gl_li[0].est_net;

        stack_push(&ast->var_ble_tabl, chek_gl_li);
    }
    //chek global is already

    
    if(size_stk > 0)//if >0 значит просто добавляем элемент с меткой глобала/local in nado
    {
        table_name *add_in_local = stack_pop(&ast->var_ble_tabl);
        int num = (int)add_in_local[0].size_tabl;

        add_in_local[num].name = strdup(name_var); //пополняем стек
        add_in_local[num].est_net = global_nado;
        add_in_local[num].adress = ast->Adress_next;

        (ast->Adress_next)++;

        add_in_local[0].size_tabl = (size_t)(num + 1);
        
        stack_push(&ast->var_ble_tabl, add_in_local); //comeback
    }

    if(size_stk == 0) //new steck
    {
        table_name *new_stk = (table_name*)calloc((size_t)ast->max_num, sizeof(table_name));
        AsserT(new_stk == NULL, );

        new_stk[0].est_net = GLOBAL;
        new_stk[0].size_tabl = 1;
        new_stk[0].name = strdup(name_var);
        new_stk[0].adress = (ast->Adress_next);
        
        (ast->Adress_next)++;

        stack_push(&ast->var_ble_tabl, new_stk);
    }

    free(name_var);

    Asm_expression(fp, ass_ignment, ast);
}


void Asm_ass_ignment(Arg_s)
{
    Debug;

    char* name = strdup(leaf->left->value.x);
    int adr = where_you_from(ast, name);
    if(adr < 0)
    {
        fprintf(stderr, "\nadr < 0) in Asm_ass_ignment(Arg_s) \n\n");
        return ;
    }

    Asm_expression(fp, leaf->right, ast); //in steck val of var

    fprintf(fp, "PUSH %d\n", adr);
    fprintf(fp, "POPREG AX\n");
    fprintf(fp, "POPM [AX]\n");

    free(name);
}


void Asm_expression(Arg_s)
{
    if(leaf == NULL)
        return ;

    if(leaf->type == Z_NAK && leaf->value.oper == ZAPYTAYA)
        return ;
    

    Debug;

    switch (leaf->type)
    {
        case NUMBER:
            fprintf(fp, "PUSH %.0lf\n", leaf->value.num);
        break;

        case VARIA:
            var_printing(fp, leaf, ast);
        break;

        case OPERAT:
            operat_ptinting(fp, leaf, ast);
        break;

        case USER_OPER: //alresdy in use
            func_user_ptinting(fp, leaf, ast);
        break;

        case Z_NAK:
            PR_ASM;
        break;

        default:
            fprintf(stderr, "\n Asm_expression case ruined\n\n");
        break;
    }
}


void var_printing(FILE* fp, Le_af leaf, ar_get)
{
    Debug;

    char* name = strdup(leaf->value.x);
    int adr = where_you_from(ast, name);
    if(adr < 0)
    {
        fprintf(stderr, "\nadr < 0) in Asm_ass_ignment(Arg_s) \n\n");
        return ;
    }

    fprintf(fp, "PUSH %d\n", adr);
    fprintf(fp, "POPREG AX\n");
    fprintf(fp, "PUSHM [AX]\n");

    free(name);
}


void func_user_ptinting(FILE* fp, Le_af leaf, ar_get)
{
    Debug;

    const char* func_name = leaf->value.us_op;
    int func_id = searching_func(func_name, ast);
    if(func_id == -1)
    {
        fprintf(stderr, "\nfunc_user_ptinting===( func not found)===\n\n");
        return ;
    }

    int num_in_f = (int)ast->userz_func[func_id].size_tabl;  //сколько функция принимает параметров смотрим
    table_name* params = ast->userz_func[func_id].init_params;  //маас сив с данными о нужных функциях

    int i = 0;
    Asm_get_args_(fp, leaf->left, ast, num_in_f, params, &i);


    fprintf(fp, "CALL :%d\n", ast->userz_func[func_id].adress );

    fprintf(fp, "PUSHREG DX\n"); //return is popreg == all good
}


void Asm_get_args_(FILE* fp, Le_af leaf, ar_get, int num_in_f, table_name* params, int *i)
{
    Debug;

    if(leaf == NULL || *i == num_in_f)
        return ;

    if(leaf->type == Z_NAK && leaf->value.oper == ZAPYTAYA)
    {
        Asm_get_left_args_(fp, leaf->left, ast, params, *i);
        (*i)++;

        Asm_get_args_(fp, leaf->right, ast, num_in_f, params, i);
    }

    else
    {
        Asm_get_left_args_(fp, leaf, ast, params, *i);
        (*i)++;
    }
}


void Asm_get_left_args_(FILE* fp, Le_af leaf, ar_get, table_name* params, int i)
{
    Debug;

    Asm_expression(fp, leaf, ast);

    fprintf(fp, "PUSH %d\n", params[i].adress);
    fprintf(fp, "POPREG AX\n");
    fprintf(fp, "POPM [AX]\n");
}


void Asm_if_cmd(FILE* fp, Le_af leaf, ar_get)
{
    Debug;

    (ast->func_num)++;

    int end_if = (ast->func_num);
    (ast->func_num)++;

    int start_else = (ast->func_num);
    (ast->func_num)++;

    Asm_expression(fp, leaf->left, ast); //resultat usloviya ifa

    if(leaf->right->type == OPERAT && leaf->right->value.oper == ELSE_C)
    {
        // if(
        fprintf(fp, "PUSH 0\n"); //compare with zero
        fprintf(fp, "JE :%d\n", start_else); //if == 0 ->> else jump to else
        // )
        
        // {
        Asm_expression(fp, leaf->right->left, ast);
        fprintf(fp, "JMP :%d\n", end_if);
        // }

        //else
        // {
        fprintf(fp, ":%d\n", start_else);
        Asm_expression(fp, leaf->right->right, ast);
        fprintf(fp, "JMP :%d\n", end_if);
        // }
    }

    else  //without else
    {
        // if(
        fprintf(fp, "PUSH 0\n"); //compare with zero
        fprintf(fp, "JE :%d\n", end_if); //if == 0 ->> jump to endif
        // )


        // {
        Asm_expression(fp, leaf->right, ast);
        fprintf(fp, "JMP :%d\n", end_if);
        // }
    }

    fprintf(fp, ":%d\n", end_if);
}


void Asm_while_cmd(FILE* fp, Le_af leaf, ar_get)
{
    Debug;

    (ast->func_num)++;

    int sam_while = (ast->func_num);
    (ast->func_num)++;

    int end_while = (ast->func_num);
    (ast->func_num)++;

    fprintf(fp, "JMP :%d\n", sam_while);
    fprintf(fp, ":%d\n", sam_while);

    // while(
    Asm_expression(fp, leaf->left, ast); //resultat usloviya ifa
    fprintf(fp, "PUSH 0\n"); //compare with zero
    fprintf(fp, "JE :%d\n", end_while); //if == 0 ->> jump out
    // )

    // {
    Asm_expression(fp, leaf->right, ast);
    fprintf(fp, "JMP :%d\n", sam_while);
    // }

    fprintf(fp, "JMP :%d\n", end_while);
    fprintf(fp, ":%d\n", end_while);
}


void Asm_logical_or(FILE* fp, Le_af leaf, ar_get)// переписать бы
{
    Debug;

    (ast->func_num)++;

    int true_labl = (ast->func_num);
    (ast->func_num)++;

    int end_lbl = (ast->func_num);
    (ast->func_num)++;

    Asm_expression(fp, leaf->left, ast);  //in steck left param 
    fprintf(fp, "PUSH 0\n");
    fprintf(fp, "JNE :%d\n", true_labl);


    Asm_expression(fp, leaf->right, ast); //right
    fprintf(fp, "PUSH 0\n");
    fprintf(fp, "JNE :%d\n", true_labl);


    fprintf(fp, "PUSH 0\n");
    fprintf(fp, "JMP :%d\n", end_lbl);


    fprintf(fp, ":%d\n", true_labl);
    fprintf(fp, "PUSH 1\n");
    fprintf(fp, "JMP :%d\n", end_lbl);

    fprintf(fp, ":%d\n", end_lbl);
}


void Asm_logical_and(FILE* fp, Le_af leaf, ar_get)
{
    Debug;

    (ast->func_num)++;

    int false_label = (ast->func_num);
    (ast->func_num)++;

    int end_label = (ast->func_num);
    (ast->func_num)++;

    Asm_expression(fp, leaf->left, ast);  //in steck left param 
    fprintf(fp, "PUSH 0\n");
    fprintf(fp, "JE :%d\n", false_label);

    Asm_expression(fp, leaf->right, ast); //right
    fprintf(fp, "PUSH 0\n");
    fprintf(fp, "JE :%d\n", false_label);

    fprintf(fp, "PUSH 1\n");
    fprintf(fp, "JMP :%d\n", end_label);

    fprintf(fp, ":%d\n", false_label);
    fprintf(fp, "PUSH 0\n");
    fprintf(fp, "JMP :%d\n", end_label);

    fprintf(fp, ":%d\n", end_label);
}


static struct znaki jumpers[] = {

    {"JE ", EQUAL_C},

    {"JAE ", L_E_bigger},
    {"JA ", L_bigger_R},

    {"JBE ", L_E_smaller},
    {"JB ", L_smaller_R},
    
    {"JNE ", N_EQUAL_C},

};

void bear_gammy_jump_func(FILE* fp, Le_af leaf, ar_get)
{            
    Asm_expression(fp, leaf->left,  ast); ///////////////////////////////
    Asm_expression(fp, leaf->right, ast);

    (ast->func_num)++;
    int end_of_JJ = (ast->func_num);

    (ast->func_num)++;

    int true_usl = (ast->func_num);
    (ast->func_num)++;

    for(int i = 0; i < (int)(sizeof(jumpers) / sizeof(jumpers[0])); ++i)
        if(leaf->value.oper == (size_t)jumpers[i].e_num)
            fprintf(fp, "%s:%d\n", jumpers[i].value, true_usl);


    fprintf(fp, "PUSH 0\n");
    fprintf(fp, "JMP :%d\n", end_of_JJ);
    
    fprintf(fp, ":%d\n", true_usl);
    fprintf(fp, "PUSH 1\n");
    fprintf(fp, "JMP :%d\n", end_of_JJ);

    fprintf(fp, ":%d\n", end_of_JJ);
}


int where_you_from(ar_get, char* name_var)
{
    table_name* reserve_stk = stack_pop(&ast->var_ble_tabl);
    for(int i = 0; i < ast->max_num && reserve_stk[i].name != NULL; ++i)
    {
        if(strcmp(name_var, reserve_stk[i].name) == 0)
        {
            stack_push(&ast->var_ble_tabl, reserve_stk);
            return reserve_stk[i].adress;
        }
    }
    stack_push(&ast->var_ble_tabl, reserve_stk);
    return -1;
}


int searching_func(const char* func_name, ar_get)
{
    for(int i = 0; i < ast->max_func_num && ast->userz_func[i].name != NULL; ++i)
        if(strcmp(func_name, ast->userz_func[i].name) == 0)
            return i;

    return -1;
}
