#include "enumchik_s.h"
#include "type_of_opera.h"

void nahui_is_compilatora(int *hranilische, size_t number_of);

//башскрипты
//isspace///
int main()
{
    size_t count_operation = 0;
    int lines_num = 0;

    struct ASM a_s_m = {};

    find_treasure(&a_s_m);

    glue_of_functio(count_operation, lines_num, &a_s_m);


    // for(int i = 0; i < lines_num; ++i)
    //     printf("str[%d] = {%s}\n", i, a_s_m.str_str[i]);

    int* hranilische = what_the_operation(a_s_m.str_str, lines_num, a_s_m.black_metka);
    ASSERTICHE(hranilische, 0);
    
    int not_use_labls = 0;
    for(int i = 0; i < NUM_label_ss; ++i)
        if (a_s_m.black_metka[i] < 0)
            ++not_use_labls;


    if (not_use_labls != NUM_label_ss)
    {
        printf("\n\n\n");
        free(hranilische);
        hranilische = NULL;
        hranilische = what_the_operation(a_s_m.str_str, lines_num, a_s_m.black_metka);
    }


    nahui_is_compilatora(hranilische, count_operation);

    free(hranilische);
    // free(a_s_m.str_str[0]);
    free(a_s_m.str_str);
    free(a_s_m.black_metka);
    free(a_s_m.fuull_asm);

    return 0;
}

void nahui_is_compilatora(int *hranilische, size_t number_of)
{
    ASSERTICHE(hranilische, perror("no way home"));
    
    FILE *fp = fopen(FILE_for_SPU , "wb");
    ASSERTICHE(fp, )

    fwrite(hranilische, number_of, sizeof(int), fp);
      
    // for(size_t i = 0; i < number_of; i++)
    //     fprintf(fp, "%d\n", hranilische[i]);

    fclose(fp);
}
