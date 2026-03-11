#include "readers.h"

void number_of_file(struct GEN* ration, int number_file)
{
    struct stat file_info = {};

    char str[LEN_FILE_MAX] = {};
    snprintf(str, sizeof str, NAME_F, number_file);

    if (stat(str, &file_info) != 0)
        perror("stat error");

    ration->char_in_file = (size_t)file_info.st_size;
}

void file_pointer_read(struct GEN* ration, int number_file)
{

    char str[LEN_FILE_MAX] = {};
    snprintf(str, sizeof str, NAME_F, number_file);

    FILE *fp = fopen(str, "r");
    ASSERTICHE(fp, perror("file not open"));

    char *ptr = (char*) calloc((ration->char_in_file + 2), sizeof(char));
    ASSERTICHE(ptr, perror("calloc ruined"));

    size_t count = fread(ptr, sizeof(char), ration->char_in_file, fp);
    ASSCANF(count, perror("error in file_pointer_read"));

    ration->full_txt = ptr;

    fclose (fp);
}
