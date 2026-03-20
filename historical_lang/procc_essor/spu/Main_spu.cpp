#include "../enumchik_s.h"
#include "switch_func.h"

int* read_er(int *lines);

// void memory_crafter(SPU* spu);

int resume_calc(TO_MUSH_ARG);

void lego_spu(struct SPU* spu);

int main()
{
    struct SPU spu = {};    //конструктор процессора //Dump
    int lines = 0;

    int* str_str = read_er(&lines);
    ASSERTICHE(str_str, 0);

    //  for(int i = 0; i < lines; ++i)
    //     printf("bite_code[%d] = {%d}\n", i, str_str[i]);

    //memory_crafter(&spu);

    //lego_stack(&spu.start_stk, STK_capacity);
    //lego_stack(&spu.stk_ret, RET_capacity);
    lego_spu(&spu);
    ans_typ answer = SU_CC_ESS;
    for(int line_now = 0; line_now < lines && answer != CMD_HLT_ && answer != ER_R_OR; ++line_now)
    {
        //printf(ANSI_COLOR_CYAN "str_str = (%d) = line{%d} = [%d]\n", str_str[line_now], line_now, answer);
        answer = resume_calc(&spu.start_stk, &spu.stk_ret, &line_now, str_str, lines, spu.ram, 0);
        //printf(ANSI_COLOR_RESET "str_str = (%d) = line{%d} = [%d]\n", str_str[line_now], line_now, answer);
    }

    if(answer == ER_R_OR)
        printf("\n911 errorr\n");
    
    free(spu.ram);
    free(str_str);
    
    clear_stk(&spu.start_stk);
    clear_stk(&spu.stk_ret);

    return 0;
}

void lego_spu(struct SPU* spu)
{
    int* Ram = (int*) calloc(OPE_rativ_ka, sizeof(int));
    ASSERTICHE(Ram, perror("memory_crafter ruined"));

    spu->ram = Ram;

    lego_stack(&(spu->start_stk), STK_capacity);
    lego_stack(&(spu->stk_ret), RET_capacity);
}
// void memory_crafter(SPU* spu)
// {
//     int* Ram = (int*) calloc(OPE_rativ_ka, sizeof(int));
//     ASSERTICHE(Ram, perror("memory_crafter ruined"));

//     spu->ram = Ram;
// }

int* read_er(int *lines)
{   
    struct stat file_info = {};

    if (stat(FILE_for_SPU, &file_info) != 0)
    {
        perror("stat error");
        return NULL;
    }

    FILE *fp = fopen(FILE_for_SPU, "rb");
    ASSERTICHE(fp, NULL);

    size_t file_buf = (size_t)file_info.st_size;


    int* arraayy = (int*) calloc(file_buf/ sizeof(int) + 1, sizeof(int));
    ASSERTICHE(arraayy, NULL);

    *lines = (int) (file_buf / sizeof(int));

    size_t count = fread(arraayy, sizeof(int), (size_t)*lines, fp);
    ASSCANF(count);

    fclose(fp);

    return arraayy;
}

int resume_calc(TO_MUSH_ARG)
{
    ASSERTICHE(data, CMD_HLT_);
    ASSERTICHE(stk_ret, CMD_HLT_);

    FOR_SW(line);

    LOGIC(_REG_,    registors);

    LOGIC(_MEMOR_,  work_with_memory);

    LOGIC(_BASE_,   steck_fucn);

    LOGIC(_FUNCN_,  for_functions);

    LOGIC(_CALC_,   calcc_func);

    LOGIC(_GAMMY_,  jump_mishki_gammy);

    LOGIC(CMD_INT_, in_func);
    
    return ER_R_OR;
}

