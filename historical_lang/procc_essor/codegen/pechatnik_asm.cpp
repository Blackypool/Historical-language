#include "pechatnik_asm.h"

void ffprintff(struct GEN* ration, int* adres, FILE *fp_out)
{
    ASSERTICHE(ration, perror("ff_strust_ff"));
    ASSERTICHE(fp_out, perror("file_ruined"));

    for (size_t i = 0; i < ration->char_in_file; ++i)
    {
        fprintf(fp_out, "PUSH %d\n", ration->full_txt[i]);  // -- пушим символ
        fprintf(fp_out, "PUSH %d\n", *adres);               // -- пущим его адрес 
            
        fprintf(fp_out, "POPREG AX\n");                     // -- в регистре AX хранится адрес
        fprintf(fp_out, "POPM [AX]\n");                     // -- в памяти в ячейку под номером адреса запихиваем в память ASCII символа

        (*adres)++;
    }
    
}

void open_write_all(FILE* fp_out)
{
    ASSERTICHE(fp_out, perror("file not come"));

    for (int nomer_file = 1; nomer_file <= KADROV; ++nomer_file)
    {
        struct GEN ration = {};

        number_of_file(&ration, nomer_file);

        file_pointer_read(&ration, nomer_file);
            
        int adres = 0;

        ffprintff(&ration, &adres, fp_out);

        // fprintf(“clear”);

        fprintf(fp_out, "DRAW\n");
        fprintf(fp_out, "SLEEP %d\n", PING);

        free(ration.full_txt);
    }
}

