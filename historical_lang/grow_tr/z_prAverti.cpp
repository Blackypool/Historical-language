#include "z_prAverti.h"


void pr_in_tf(struct stk* data, int /*num_line*/, const char* /*file_n*/)
{
    ssize_t schetchik = data->capacity;

    FILE *fp = fopen("OTLADCHIK.txt", "w");
    if(fp == NULL)
        perror("file not open((");
      
    while(schetchik > 0)
    {
        schetchik--;

        fprintf(fp, "stack[%zd] =\n", schetchik);
    }

    fclose(fp);
}


void yadro_li_you(struct stk* data, int num_line, const char* file_n)
{
    uintptr_t adr_ptr = (uintptr_t)(data->stack);

    if ((adr_ptr < 0x1000) || (adr_ptr > 0x00007FFFFFFFFFFF))
    {
        printf("\nNO_NO_NO Mr. fish, you go out is pamyat yadrad%s:%d\n", file_n, num_line);

        if(data->stack != NULL)
        {
            free(data->stack);
            data->stack = NULL;
        }

        data->stack = (tip_lac*) calloc((size_t)(data->capacity), sizeof(int));

        if(data->stack == NULL)
            perror("Unluck - x2\n");
    }
}


void defence_of_capacity(struct stk* data, int num_line, const char* file_n)
{
    ssize_t schetchik = data->capacity;

    if(llabs(data->capacity) >= pow(2, 62))
    {
        printf("To big capacity = (%zd) %s:%d\n", data -> capacity, file_n, num_line);
        schetchik = llabs(data->capacity) / 4;
        data -> capacity = schetchik;
    }


    if(data->capacity == 0)
    {
        printf("Capacity cant be zero\nBut I can fix it%s:%d\n", file_n, num_line);
        (data->capacity) = 1;
    }


    if(schetchik < 0)
    {
        printf("\nCAPACITY STRONGER THAT YOU THINK /(modul of capasity)%s:%d\n", file_n, num_line);

        schetchik = labs(data->capacity) +2;
        data->capacity = schetchik + 4;
    }
}


void def_size_capacity(struct stk* data, int /*num_line*/, const char* /*file_n*/)
{
    if((data->size) >= (data->capacity))
        printf("size >= capacity(((");
}


uintptr_t hash_hash(struct stk* data)
{
    // {return 1;}
    uintptr_t adr_ptr = (uintptr_t)(data->stack);

    uintptr_t znacheni_a = 0;


    for(ssize_t i = data->size; i > 0; --i)
        znacheni_a = znacheni_a + (uintptr_t)data->stack[i] * 2;

    znacheni_a = adr_ptr * 23 - (znacheni_a * (uintptr_t)data->size) + (uintptr_t)data->Kana_ - (uintptr_t)data->_reikA * 8;

    return znacheni_a;
}
