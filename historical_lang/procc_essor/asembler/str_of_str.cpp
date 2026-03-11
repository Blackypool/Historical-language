// #include "str_of_str.h"

// void skip_spasec(int *sch, char* full_asm);
// void comments(int *sch, char* full_asm);

// #include "str_of_str.h"

// char** v_str_ku(char *full_asm, int lines_num, size_t number_char_in_file, size_t& count_operation)
// {
//     ASSERTICHE(full_asm, NULL);

//     char **str_str = (char**) calloc((size_t)lines_num + 1, sizeof(char*)); //массив указателей на строки
//     ASSERTICHE(str_str, NULL);
    

//     int sch = 0;
//     while(full_asm[sch] != '\0')
//     {
//         skip_spasec(&sch, full_asm);

//         if(full_asm[sch] == '\0')
//             break;

//         if(full_asm[sch] == '\n')
//         {
//             full_asm[sch] = '\0';
//             ++count_operation;
//         }

//         if(full_asm[sch] == ' ') 
//             ++count_operation;

//         ++sch;
//     }

//     ++count_operation;

//     lines_num = 0;
//     str_str[lines_num] = &full_asm[0];   //загружаем 1 строку
//     lines_num = 1;

//     for(size_t i = 0; i < number_char_in_file; ++i)
//     {
//         if(full_asm[i] == '\0')
//         {
//             str_str[lines_num] = &full_asm[i + 1];
//             ++lines_num;
//         }
//     }

//     return str_str;
// }


// void skip_spasec(int *sch, char* full_asm)
// {
//     if(*sch == 0)
//         return ;

//     //если предыдущий -- цифра/буква, значит это команда и слеш эн скипать не надо
//     if( ('A' <= full_asm[*sch - 1] && full_asm[*sch - 1] <= 'Z') || ('0' <= full_asm[*sch - 1] && full_asm[*sch - 1] <= '9') )
//         return ;

//     comments(&(*sch), full_asm);

//     while(full_asm[*sch] == '\n' || full_asm[*sch] == '\t')
//         ++(*sch);
// }


// void comments(int *sch, char* full_asm)
// {
//     if(full_asm[*sch] == ';')
//         while(full_asm[*sch] != '\n' && full_asm[*sch] != '\0')
//             ++(*sch);
// }





#include "str_of_str.h"

char** v_str_ku(char *full_asm, int lines_num, size_t number_char_in_file, size_t& count_operation)
{
    ASSERTICHE(full_asm, NULL);

    char **str_str = (char**) calloc((size_t)lines_num + 1, sizeof(char*)); //массив указателей на строки
    ASSERTICHE(str_str, NULL);
    

    int sch = 0;
    while(full_asm[sch] != '\0')
    {
        if(full_asm[sch] == '\n')
        {
            full_asm[sch] = '\0';
            ++count_operation;
        }

        if(full_asm[sch] == ' ') 
            ++count_operation;

        ++sch;
    }

    ++count_operation;

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





// #include "str_of_str.h"

// char** v_str_ku(char *full_asm, int lines_num, size_t number_char_in_file, size_t& count_operation)
// {
//     ASSERTICHE(full_asm, NULL);

//     char **str_str = (char**) calloc((size_t)lines_num + 1, sizeof(char*));
//     ASSERTICHE(str_str, NULL);
    
//     count_operation = 0;

//     for(size_t i = 0; i < number_char_in_file; ++i) 
//     {
//         if(full_asm[i] == '\n') 
//             full_asm[i] = '\0';
//     }


//     int line_index = 0;
//     size_t i = 0;
    
//     while(i < number_char_in_file && line_index < lines_num) 
//     {
//         while(i < number_char_in_file && (full_asm[i] == '\0' || full_asm[i] == ' ' || full_asm[i] == '\t')) 
//             ++i;
        
//         if(i >= number_char_in_file) 
//             break;
        
//         str_str[line_index] = &full_asm[i];
//         line_index++;
        
//         while(i < number_char_in_file && full_asm[i] != '\0') 
//             ++i;
//     }
    
//     str_str[line_index] = NULL;
    
//     return str_str;
// }
