#include "../M_Diff.h"

struct A_S_T* lex_ana(char* name_of_compile_file)
{
    //////////////  заполняем базу исторических событий
    int err = history_base_upgrad();
    AsserT(err != 0, NULL);


    //////////////  читаем файл
    size_t number_char = 0;
    char* text_rim = file_pointer_read(&number_char, name_of_compile_file);   //весь код целиком
    // for(size_t i = 0; i < number_char; ++i)
    //     fprintf(stderr, "Позиция %zu: символ '%c'\n", i, text_rim[i]);
        

    //////////////  iniciali_z_ation
    leaf* toke_nize = (leaf*)calloc(number_char, sizeof(leaf));
    AsserT(toke_nize == NULL, NULL);
    int pose_tz = 0;

    
    //////////////
    int max_varia = 0; //считаем сколько переменные встретились раз
    int max_func = 0;
    int good = 0; //написал ли в конце "помни:"
    for(size_t i = 0; i < number_char; ++i)
    {
        // fprintf(stderr, "Позиция %zu: символ '%c'\n", i, text_rim[i]);
        skip_spasec(text_rim, &i);
        skip_comments(text_rim, &i);

        if(i >= number_char)
            break;

        // if(text_rim[i] == '(' || text_rim[i] == ')' || text_rim[i] == '{' || text_rim[i] == '}' || text_rim[i] == '=' || text_rim[i] == ';')
        // {
        //     // printf("%c", text_rim[i]);
        //     its_schto_to(toke_nize, &pose_tz, &i, text_rim[i]);
        //     continue;
        // }

        if(text_rim[i] == '$')
        {
            its_number_time(text_rim, &i, toke_nize, &pose_tz);
            continue;
        }

        char* ans_que = create_word(text_rim, &i, ' ');
        if(strcasecmp(ans_que, "remember:") == 0 || strcasecmp(ans_que, "помни:") == 0)
        {
            // fprintf(stderr, "\nпомни\n\n");
            good++;
            its_over(ans_que, toke_nize, &pose_tz, &i, text_rim);
            break;
        }

        if(strcasecmp(ans_que, "init") == 0 || strcasecmp(ans_que, "инит") == 0)
        {
            // fprintf(stderr, "\ninit found\n\n");
            its_initi(toke_nize, &pose_tz, &i);

            free(ans_que);
            ans_que = NULL;
            continue;
        }

        if(func_defolt_or_user(toke_nize, &pose_tz, &i, ans_que) == OPERAT)
        {
            max_func++;
            free(ans_que);
            ans_que = NULL;
            continue;
        }

        if(check_znaki(toke_nize, &pose_tz, &i, ans_que) == Z_NAK)
        {
            free(ans_que);
            ans_que = NULL;
            continue;
        }

        its_val_time(ans_que, toke_nize, &pose_tz, &i, &max_varia);
        free(ans_que);
        ans_que = NULL;

    }

    //////////////  ломаем код если нет ключевого слова
    if(good == 0)
    {
        printf("\nEOF otsutstvuet\n");
        // Destroy_Rimeni(toke_nize, pose_tz);
    }
    change_architectura(toke_nize, pose_tz);

    
    struct A_S_T* ast = (struct A_S_T*)calloc(1, sizeof(A_S_T));

    ast->tok_mas = toke_nize;
    ast->max_pose = pose_tz;
    ast->pose = 0;

    ast->max_num = max_varia + 10;
    ast->var_ble_tabl = {0};
    ast->var_num = 0;

    ast->func_num = 0;
    ast->max_func_num = max_func;/////////надо считалку подключить
    ast->userz_func = (table_name*)calloc((size_t)ast->max_func_num, sizeof(table_name));

    ast->file_name = toke_nize[pose_tz - 1].value.x;
    // fprintf(stderr, "\n\n%s\n\n\n", ast->file_name);

    for(int i = 0; i < ast->max_pose; ++i)
    {
        //if(toke_nize[i].type == OPERAT)
            // fprintf(stderr, "________token________[%d] = -%s-\n\n", i, what_need_printf(toke_nize, i));//toke_nize[i].value.oper);//
    }
    return ast;
}


void skip_comments(char* text_rim, size_t* now)
{
    // size_t i = *now;

    // char* ans_que = create_word(text_rim, now, '!');
    // (*now)++;

    if(strncmp(&text_rim[*now], "non ad rem!", 11) == 0)
    {
        *now = *now + 11;

        while(text_rim[*now] != '!')
            (*now)++;

        (*now)++;
    }

    // else (*now) = i;

    // free(ans_que);
}


void skip_spasec(char* text_rim, size_t* now)
{
    while(text_rim[*now] != '\0' && \
          (text_rim[*now] == ' ' || text_rim[*now] == '\n' || text_rim[*now] == '\t' || text_rim[*now] == '|' || \
                text_rim[*now] == '&' || text_rim[*now] == '/' || text_rim[*now] == '\\'))
        (*now)++;
}


char* create_word(char* text_rim, size_t* now, const char type_word)
{
    skip_spasec(text_rim, now);

    if(text_rim[*now] == '\0')
        return NULL;

    size_t start = *now;
    
    while(text_rim[*now] != '\0' && text_rim[*now] != type_word && text_rim[*now] != '$' && text_rim[*now] != '\n')
    {  
        if((unsigned char)text_rim[*now] >= 0xD0)
            *now = *now + 2;
        
        else 
            (*now)++; 
    }


    size_t len = *now - start;

    char* ans_que = (char*)calloc(len + 1, sizeof(char));
    AsserT(ans_que == NULL, NULL);

    // strncpy(ans_que, &text_rim[start], len);

    for(size_t i = 0; i < len; ++i)
        ans_que[i] = text_rim[start + i];

    ans_que[len] = '\0';

    // if(text_rim[*now] == type_word) 
    //     (*now)++;

    // fprintf(stderr, "\nпрочитали = %s нау = %zu\n\n", ans_que, *now);

    return ans_que;
}
