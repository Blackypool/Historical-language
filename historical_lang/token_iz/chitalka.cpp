#include "chtec.h"

size_t number_of_file(const char* name_file)
{
    struct stat file_info = {};

    if(stat(name_file, &file_info) != 0)
    {
        perror("stat error");
        return 1;
    }

    return (size_t)file_info.st_size;
}


char* file_pointer_read(size_t *number_char, const char* name_file)
{
    *number_char = number_of_file(name_file);

    FILE *fp = fopen(name_file, "rb");
    AsserT(fp == NULL, NULL);

    char *ptr = (char*) calloc((*number_char + 2), sizeof(char));
    AsserT(ptr == NULL, NULL);

    size_t count = fread(ptr, sizeof(char), *number_char, fp);
    AsserT(count == 0, NULL);

    fclose (fp);

    return ptr;
}
