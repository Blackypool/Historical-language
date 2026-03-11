#include "type_of_opera.h"

static struct operatio oper[] = {

      {"ADD",  CMD_ADD_,  3, 0},  //0   //CMD_
       {"SUB",  CMD_SUB_,  3, 0},  //1  auto_ считать длину в струтуру длину строки в структуре последним элементом
        {"MUL",  CMD_MUL_,  3, 0},  //2
         {"DIV",  CMD_DIV_,  3, 0},  //3
          {"POW",  CMD_POW_,  3, 0},  //4
           {"SQRT", CMD_SQRT_, 4, 0},  //5
                                    {"POPREG", CMD_POPREG_, 6, 1},  //6
                                     {"PUSHREG", CMD_PSHREG_, 7, 1}, //7
            {"POPM",  CMD_POPM_,  4, 1}, //8
             {"PUSHM", CMD_PUSHM_, 5, 1}, //9
                                        {"PUSH", CMD_PUSH_, 4, 1},     //10
                                         {"OUT",  CMD_OUT_,  3, 0},     //11
                                          {"HLT",  CMD_HLT_,  3, 0},     //12
                   {"INT",  CMD_INT_,  3, 0}, //13
                    {"SLEEP",CMD_SLEP_, 5, 1}, //14
                     {"DRAW", CMD_DRAW_, 4, 0}, //15
                                              {"JMP", CMD_JMP_, 3, 1},      //16
                                               {"JBE", CMD_JBE_, 3, 1},      //17
                                                {"JB",  CMD_JB_,  2, 1},      //18
                                                 {"JAE", CMD_JAE_, 3, 1},      //19
                                                  {"JA",  CMD_JA_,  2, 1},      //20
                                                   {"JNE", CMD_JNE_, 3, 1},      //21
                                                    {"JE",  CMD_JE_,  2, 1},      //22
                             {"RET",   CMD_RET_, 3, 0},  //23
                              {"CALL", CMD_CALL_, 4, 1},  //24
                    
                                       };

// void doing_lens()
// {
//     int number_of_operation = sizeof(oper) / sizeof(oper[0]);
//     for (int i = 0; i < number_of_operation; ++i)
//         oper[i].len_len = strlen(oper[i].opera);

// }

int* what_the_operation(char** str_str, int lines, int *black_metka)
{
    // void doing_lens();

    ASSERTICHE(str_str, NULL);

    int *hranilische = (int*) calloc((size_t)(lines) * 2, sizeof(int));
    ASSERTICHE(hranilische, NULL);

    int Kana = 7;

    int oper_find = 0;
    int sche = 0; 

    for(int lin = 0; lin < lines; ++lin)
    {
        if(str_str[lin] == NULL)
            break;

        //чек лэйбэл
        label_you_li(str_str, black_metka, &lin, &sche);

        oper_find = choose_operatia(str_str, &lin);
        ASSCANFOR_ASM(oper_find, lin);
        
        hranilische[sche] = oper[oper_find].maska;
        
        DEBUG;

        if ((oper[oper_find].need_param) == 1)
        {
            ++sche;
            hranilische[sche] = need_param(str_str, lin, black_metka, oper_find, &Kana);
            ASSCANFOR_ASM(Kana, lin);
        }

        DEBUG;

        ++sche;
    }
        
    return hranilische;    
}

int choose_operatia(char** str_str, int *lin)
{
    if(str_str[*lin] == NULL)
        return -2;
        
    int number_of_operation = sizeof(oper) / sizeof(oper[0]);

    for(int i = 0; i < number_of_operation; ++i)
        if (strncmp(str_str[*lin], oper[i].opera, oper[i].len_len) == 0)
            return i;
    
    return -1;
}

int need_param(char** str_str, int lin, int *black_metka, int oper_find, int *kanareyka)
{   // указательный параметр

    int valli = 0;
    if (sscanf(str_str[lin] + oper[oper_find].len_len, " :%d" , &valli) > 0)
        return black_metka[valli];

    if (sscanf(str_str[lin] + oper[oper_find].len_len, " %d" , &valli) > 0)
        return valli;

    char command[2] = {};
    if (sscanf(str_str[lin] + oper[oper_find].len_len, " [%1cX]%n", command, &valli) > 0)     /////%n == 2
        return command[0] - 'A';
                
    if(sscanf(str_str[lin] + oper[oper_find].len_len, " %1cX%n", command, &valli) > 0)
        return command[0] - 'A';
    
    *kanareyka = -1;
    return -666;
}

void find_treasure(struct ASM* a_s_m)
{
    int *metka_s = (int*) calloc(NUM_label_ss, sizeof(int));
    ASSERTICHE(metka_s, perror("label not found"));

    for(int i = 0; i < NUM_label_ss; ++i)
        metka_s[i] = -1;

    a_s_m->black_metka = metka_s;
}

void label_you_li(char** str_str, int* black_metka, int *lin, int *sche)
{
    ASSERTICHE(str_str, perror("str_str is NULL"));

    if(str_str[*lin] == NULL)
    {
        fprintf(stderr, "\n\nstr_str[%d] is NULL in label_you_li\n\n", *lin);
        return;
    }

    int def = 0;         //   отдельная функция
    if (sscanf(str_str[*lin], ":%d", &def) > 0)
    {
        //printf(ANSI_COLOR_GREEN "\n\nMETKA FIND\n\n" ANSI_COLOR_RESET);
        (*lin)++;

        black_metka[def] = *sche;
    }
}
