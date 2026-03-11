#include "file_commands.h"

void glue_of_functio(size_t& count_operation, int& lines_num, struct ASM* a_s_m)
{
    size_t number_char_in_file = number_of_file();

    char *full_asm = file_pointer_read();
    ASSERTICHE(full_asm, perror("bad glue full asm"));
    
    lines_num = number_of_lens(full_asm);

    char ** strstr = v_str_ku(full_asm, lines_num, number_char_in_file, count_operation);
    ASSERTICHE(strstr, perror("glue dry out str_str"));

    a_s_m->str_str = strstr;
    a_s_m->fuull_asm = full_asm;
}

size_t number_of_file()
{
    struct stat file_info = {};

    if (stat(FILE_for_ASM, &file_info) != 0)
    {
        perror("stat error");
        return 1;
    }

    return (size_t)file_info.st_size;
}

char* file_pointer_read()
{
    size_t number_char = number_of_file();

    FILE *fp = fopen(FILE_for_ASM, "rb");
    ASSERTICHE(fp, NULL);

    char *ptr = (char*) calloc((size_t)(number_char + 2), sizeof(char));
    if (ptr == NULL)
    {
        perror("Dinamics error");
        return NULL;
    }

    size_t count = fread(ptr, sizeof(char), number_char, fp);
    ASSCANF(count);

    fclose (fp);

    return ptr;
}

int number_of_lens(char* ptr)
{
    ASSERTICHE(ptr, -1);

    int lines_num = 0;

    for(int i = 0; ptr[i] != '\0'; ++i)
    {
        if(ptr[i] == '\n')
            ++lines_num;
    }

    return lines_num + 1;
}
