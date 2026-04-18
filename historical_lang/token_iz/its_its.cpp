#include "its_its.h"


// struct command_s com_m_trnslte[] = {

//     {"излечить", ADD_C},
//     // {"помни:", HLT_C},
//     {"волшебный_эликсир", POW_C},
//     {"линчевать", DIV_C},
//     {"Edictum", IF_C}, //эдикт (указ магистрата)
//     {"затопить", RET_C},
//     {"тамплиерский_обед", MUL_C},
//     {"крестовый_поход", WHILE_C},
//     {"исповедь", SCAN_C},
//     {"догма", DRAW_C},
//     {"открыть_Америку", PUSHM_C},
//     // {"серебряный_кубок", ASSERT_C},
//     {"индульгенция", SUB_C},

// };
struct command_s com_m_trnslte[] = {

    {"cure", ADD_C},                 // излечить -> сложение
    {"magic_elixir", POW_C},         // волшебный_эликсир -> степень
    {"lynch", DIV_C},                // линчевать -> деление
    {"Edictum", IF_C},               // Edictum -> условие if (оставляем латиницу)
    {"flood", RET_C},                // затопить -> return
    {"templar_meal", MUL_C},         // тамплиерский_обед -> умножение
    {"crusade", WHILE_C},            // крестовый_поход -> цикл while
    {"confession", SCAN_C},          // исповедь -> ввод
    {"dogma", PRINT_F},               // догма -> вывод/рисование
    {"discover_america", PUSHM_C},   // открыть_Америку -> push memory
    {"indulgence", SUB_C},           // индульгенция -> вычитание
    {"kazn", ELSE_C},
    {"init", IN_IT},
    {"=", RAVNO},
    {"cnct", CONNEC_T},
    {"func", FUNC_C},
    {"dragon_fire", SQRT_C},

    {"излечить", ADD_C},
    {"помни:", HLT_C},
    {"волшебный_эликсир", POW_C},
    {"линчевать", DIV_C},
    {"Edictum", IF_C}, //эдикт (указ магистрата)
    {"затопить", RET_C},
    {"тамплиерский_обед", MUL_C},
    {"крестовый_поход", WHILE_C},
    {"исповедь", SCAN_C},
    {"догма", DRAW_C},
    {"открыть_Америку", PUSHM_C},
    // {"серебряный_кубок", ASSERT_C},
    {"индульгенция", SUB_C},
    {"сжигающее_пламя_дракона", SQRT_C},

};
const int com_struct_size = sizeof(com_m_trnslte) / sizeof(com_m_trnslte[0]);


struct znaki prepinan[] = {

    {"(", SKOB_krug_L, "SKOB_krug_L"},
    {")", SKOB_krug_R, "SKOB_krug_R"},
    {"{", SKOB_figu_L, "SKOB_figu_L"},
    {"}", SKOB_figu_R, "SKOB_figu_R"},
    {";", TOCHKA_ZAP, "TOCHKA_ZAP"},
    {"==", EQUAL_C, "EQUAL_C"},
    {",", ZAPYTAYA, "ZAPYTAYA"},

    {">=", L_E_bigger, "L_E_bigger"},
    {">", L_bigger_R, "L_bigger_R"},

    {"<=", L_E_smaller, "L_E_smaller"},
    {"<", L_smaller_R, "L_smaller_R"},
    
    {"!=", N_EQUAL_C, "N_EQUAL_C"},
    {"∧", LOG_AND, "LOG_AND"},
    {"!∧", LOG_OR, "LOG_OR"},

};
const int znaki_struct_size = sizeof(prepinan) / sizeof(prepinan[0]);


int func_defolt_or_user(struct leaf* toke_nize, int* pose_tz, size_t* now, char* ans_que)
{
    // size_t back_up = *now;

    // char* ans_que = create_word(text_rim, now, ' ');
    // (*now)++;

    ////////////// ищем функцию в базовых
    for(int i = 0; i < com_struct_size; ++i)
    {
        if(strcasecmp(ans_que, com_m_trnslte[i].value) == 0)
        {
            toke_nize[*pose_tz].lines_in_Rim = *now;
            toke_nize[*pose_tz].type = OPERAT;
            toke_nize[*pose_tz].value.oper = com_m_trnslte[i].e_num;

            (*pose_tz)++;

            // free(ans_que);
            // ans_que = NULL;

            return OPERAT;
        }
    }
    //////////////

    ////////////// функция с нижним подчеркиванием, созданная пользователем и не нашлась в таблице функций
    if(strchr(ans_que, '_') != NULL)
    {
        // while(text_rim[*now] != ' ')
        //     (*now)++;

        // (*now)++;

        toke_nize[*pose_tz].lines_in_Rim = *now;
        toke_nize[*pose_tz].type = USER_OPER;
        toke_nize[*pose_tz].value.us_op = strdup(ans_que);//strdup(ans_que);

        (*pose_tz)++;

        // free(ans_que);
        // ans_que = NULL;

        return OPERAT;
    }

    ////////////// переменная
    // (*now) = back_up;

    // free(ans_que);
    // ans_que = NULL;

    return VARIA;
}


void its_number_time(char* text_rim, size_t* now, struct leaf* toke_nize, int* pose_tz)
{
    skip_spasec(text_rim, now);

    (*now)++; //скипаем доллар
    toke_nize[*pose_tz].lines_in_Rim = *now;

    char* ans_que = create_word(text_rim, now, '$'); //скопировал строчку в диапазоне долларов

    int num_struct = num_of_date;
    for(int sch = 0; sch < num_struct; ++sch)
    {
        if(date_hist[sch].value == NULL)
            break;

        // fprintf(stderr, "\nsch = %d;   value_data = %s \n\n", sch, date_hist[sch].value);
        if(strcasecmp(ans_que, date_hist[sch].value) == 0)
        {
            // fprintf(stderr, "\nsch = %d;   value_data = %s \n\n", sch, date_hist[sch].value);
            if(date_hist[sch].vsrtrechali_li == 0)
                date_hist[sch].vsrtrechali_li = 1;

            toke_nize[*pose_tz].type = NUMBER;
            toke_nize[*pose_tz].value.num = date_hist[sch].num;

            (*pose_tz)++;

            break;
        }

        if(sch == num_struct - 2)//потом сделаю базу данных с датами
        {
            fprintf(stderr, "\nhere need nyro to scan date^ but no))\n\n");
           // call_nyrosetochka(ans_que, toke_nize, pose_tz);
        }
    }

    free(ans_que);
}


void its_over(ARG_s, char* text_rim)
{
    skip_spasec(text_rim, now);
    
    toke_nize[*pose_tz].lines_in_Rim = *now;
    toke_nize[*pose_tz].type = (size_t)END_OF_FILE;
    toke_nize[*pose_tz].value.oper = (size_t)END_OF_FILE;

    (*pose_tz)++;

    free(ans_que);
    ans_que = NULL;


    // (*now)++;
    char* an_ue = create_word(text_rim, now, '\0');

    char new_file_name[69] = {0}; 
    snprintf(new_file_name, strlen(an_ue) + 50, "translator/%s.txt", an_ue);

    toke_nize[*pose_tz].lines_in_Rim = *now;
    toke_nize[*pose_tz].type = VARIA;
    toke_nize[*pose_tz].value.x = strdup(new_file_name);

    (*pose_tz)++;

    free(an_ue);
    ans_que = NULL;
}


void its_val_time(ARG_s, int* max_varia)
{
    toke_nize[*pose_tz].lines_in_Rim = *now;
    toke_nize[*pose_tz].type = VARIA;
    toke_nize[*pose_tz].value.x = strdup(ans_que);//strdup(ans_que);

    (*pose_tz)++;
    (*max_varia)++;
}


void its_schto_to(struct leaf* toke_nize, int* pose_tz, size_t* now, char shto_to)
{
    toke_nize[*pose_tz].lines_in_Rim = *now;
    toke_nize[*pose_tz].type = Z_NAK;

    for(int i = 0; i < znaki_struct_size; ++i)
        if((const char)shto_to == *prepinan[i].value)
             toke_nize[*pose_tz].value.oper = (size_t)prepinan[i].e_num;

    (*pose_tz)++;
}


char* what_need_printf(leaf* toke_nize, int pose)
{
    if(toke_nize[pose].type == USER_OPER)
        return strdup(toke_nize[pose].value.us_op);

    if(toke_nize[pose].type == VARIA)
        return strdup(toke_nize[pose].value.x);

    if(toke_nize[pose].type == OPERAT)
    {
        for(int i = 0; i < com_struct_size; ++i)
        {
            if(toke_nize[pose].value.oper == com_m_trnslte[i].e_num)
                return strdup(com_m_trnslte[i].value);
        }
    }

    if(toke_nize[pose].type == NUMBER)
    {
        int num_struct = num_of_date;
        for(int i = 0; i < num_struct; ++i)
        {
            if((int)toke_nize[pose].value.num == (int)date_hist[i].num)
            {
                static char str[50] = {0};
                snprintf(str, sizeof(str), "$%s$", date_hist[i].value);

                return str;
            }
        }
    }

    if(toke_nize[pose].type == Z_NAK)
    {
        for(int i = 0; i < znaki_struct_size; ++i)
        {
            if(toke_nize[pose].value.oper == (size_t)prepinan[i].e_num)
                return strdup(prepinan[i].value);
        }
    }

    if(toke_nize[pose].type == (size_t)END_OF_FILE)
    {
        return strdup("END_OF_FILE");
    }

    return strdup("unluc k");
}


void its_initi(struct leaf* toke_nize, int* pose_tz, size_t* now)
{
    toke_nize[*pose_tz].lines_in_Rim = *now;
    toke_nize[*pose_tz].type = OPERAT;

    toke_nize[*pose_tz].value.oper = IN_IT;

    (*pose_tz)++;
}


int check_znaki(struct leaf* toke_nize, int* pose_tz, size_t* now, char* ans_que)
{
    for(int i = 0; i < znaki_struct_size; ++i)
    {
        if(strcasecmp(ans_que, prepinan[i].value) == 0)
        {
            toke_nize[*pose_tz].lines_in_Rim = *now;
            toke_nize[*pose_tz].type = Z_NAK;
            toke_nize[*pose_tz].value.oper = (size_t)prepinan[i].e_num;

            (*pose_tz)++;

            return Z_NAK;
        }
    }

    return OPERAT;
}
