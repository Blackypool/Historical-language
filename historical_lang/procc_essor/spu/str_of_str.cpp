#include "str_of_str.h"


char** v_str_ku(char *full_asm, int lines_num, size_t number_char_in_file)
{
    ASSERTICHE(full_asm, NULL);

    char **str_str = (char**) calloc((size_t)lines_num + 1, sizeof(char*)); //массив указателей на строки
    ASSERTICHE(str_str, NULL);
    
    int sch = 0;
    while(full_asm[sch] != '\0')
    {
        if(full_asm[sch] == '\n')
            full_asm[sch] = '\0'; 
        
        ++sch;
    }

    lines_num = 0;
    str_str[lines_num] = &full_asm[0];   //загружаем 1 строку
    lines_num = 1;

    for(size_t i = 0; i < number_char_in_file; ++i)
    {
        if(full_asm[i] == '\0')
        {   
            str_str[lines_num] = &full_asm[i + 1];
            ++lines_num;
        }
    }

    return str_str;
}
