#ifndef SWITCH
#define SWITCH

#include "enumchik_s.h"

#define ST_PP_CALC(data, uslovie)\
        int v_1 = stack_pop(data);\
        int v_2 = stack_pop(data); \
        stack_push(data, uslovie)//;  \
        //printf("ST_PP||line[%d] = {%d}", *line, uslovie)


#define ST_PP_JUMP(data, uslovie)   \
            (*line)++;\
            int v_1 = stack_pop(data);\
            int v_2 = stack_pop(data); \
            if(uslovie) \
                *line = str_str[*line] - 1;  \
            //else *line++;
            //printf("JUMP||line[%d] = {%d}", *line, uslovie)


void calcc_func(TO_MUSH_ARG);

void steck_fucn(TO_MUSH_ARG);

void registors(TO_MUSH_ARG);

void jump_mishki_gammy(TO_MUSH_ARG);

void for_functions(TO_MUSH_ARG);

void work_with_memory (TO_MUSH_ARG);

void in_func(TO_MUSH_ARG);

#endif