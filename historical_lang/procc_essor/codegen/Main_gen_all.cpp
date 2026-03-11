#include "for_fast_use.h"

int main()
{
    FILE *fp_out = fopen("asm.asm", "w");
    ASSERTICHE(fp_out, 0);

    
    for (int qwerty = 0; qwerty < REPEAT_RAZ; ++qwerty)
        open_write_all(fp_out);


    fprintf(fp_out, "HLT\n");

    fclose(fp_out);

    return 0;
}
