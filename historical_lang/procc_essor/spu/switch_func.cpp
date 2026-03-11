#include "switch_func.h"

void calcc_func(ARG_CLC)
{
    switch(operation)
        {

            case CMD_ADD_:
            {
                ST_PP_CALC(data, v_1 + v_2);
            }
            break;

            case CMD_SUB_:
            {
                ST_PP_CALC(data, v_2 - v_1);
            }
            break;

            case CMD_MUL_:
            {
                ST_PP_CALC(data, v_1 * v_2);
            }
            break;
        
            case CMD_DIV_:
            {
                ST_PP(data);

                if (v_1 == 0)
                {
                    perror("Go out its not matan");
                    break;
                }

                stack_push(data, v_2 / v_1);
            }
            break;
                
            case CMD_POW_:
            {
                ST_PP_CALC(data, (tip_lac)pow(v_2, v_1));                
            }
            break;

            case CMD_SQRT_:
            {
                int v_1 = stack_pop(data);
                
                if(v_1 < 0)
                {
                    perror("sqvrt ot <0");
                    break;
                }

                stack_push(data, (tip_lac)sqrt(v_1));
            }
            break;

            default: break;

        }
}

void steck_fucn(ARG_STF)
{
    switch (operation)
    {

        case CMD_PUSH_:
            {
                (*line)++;
                int value = str_str[*line];
                
                stack_push(data, value);
            }
            break;
        
        case CMD_OUT_:
            {
                int answer = stack_pop(data);
                printf(ANSI_COLOR_BLUE "answer = (%d)", answer);
                printf(ANSI_COLOR_RESET "\n");
            }
            break;

        case CMD_HLT_:
            {
            *line = lines_all;
            }
            break;

        default: break;

    }
}

void registors(ARG_REG)
{
    switch (operation)
    {

        case CMD_POPREG_:
            {
                (*line)++;
                int xx = str_str[*line];

                int param = stack_pop(data);

                data->PuSh_rEg[xx] = param;
            }
            break;
                    
        case CMD_PSHREG_:
            {
                (*line)++;
                int xx = str_str[*line];

                stack_push(data, data->PuSh_rEg[xx]);
            }
            break;

        default: break;

    }
}

void jump_mishki_gammy(ARG_JMP)
{
    switch (operation)
    {

        case CMD_JMP_:
            {
                (*line)++;

                *line = str_str[*line] - 1;
            }
            break;

        case CMD_JB_:
        {
            ST_PP_JUMP(data, v_2 <  v_1);
        }
            break;
            
        case CMD_JBE_:
        {
            ST_PP_JUMP(data, v_2 <= v_1);
        }
            break;

        case CMD_JA_:
        {
            ST_PP_JUMP(data, v_2 >  v_1);
        }
            break;

        case CMD_JAE_:
        {
            ST_PP_JUMP(data, v_2 >= v_1);
        }
            break;

        case CMD_JE_:
        {
            ST_PP_JUMP(data, v_2 == v_1);
        }
            break;

        case CMD_JNE_:
        {
            ST_PP_JUMP(data, v_2 != v_1);
        }
            break;

        default: break;

    }
}

void for_functions(ARG_FFC) 
{
    switch (operation)
    {
        
        case CMD_CALL_:
            {
                (*line)++;
                int line_kuda_tp = str_str[*line] - 1;
                printf("\n\n\nline_kuda_tp = %d\n\n\n", line_kuda_tp);
                
                int kuda_obratno = *line + 1;

                printf("\n\n\nkuda_obratno = %d\n\n\n", kuda_obratno);
                stack_push(stk_ret, kuda_obratno);

                *line = line_kuda_tp;
            }
            break;

        case CMD_RET_:
            {
                *line = stack_pop(stk_ret) - 1;
            }
            break;

        case CMD_SLEP_:
            {
                (*line)++;

                useconds_t for_sl = (useconds_t)str_str[*line];
                
                usleep(for_sl);
            }
            break;
        
        default: break;

    }
}

void work_with_memory (ARG_WWM)
{
    switch (operation)
    {

        case CMD_POPM_:
            {
                (*line)++;
                int xx = str_str[*line];

                int ptr = data->PuSh_rEg[xx];

                //printf(ANSI_COLOR_GREEN "\n________________________________________\n" ANSI_COLOR_RESET);
                push_memory[ptr] = stack_pop(data);
            }
            break;

        case CMD_PUSHM_:
            {
                (*line)++;
                int xx = str_str[*line];

                int ptr = data->PuSh_rEg[xx];

                stack_push(data, push_memory[ptr]);
            }
            break;

        case CMD_DRAW_:
            {   
                fwrite(push_memory, sizeof(int), OPE_rativ_ka, stdout);

                printf("\n");
            }

        default: break;

    }
}

void in_func(ARG_INF)
{
    printf("enter number");

    int value = 0;
    scanf("%d", &value);

    stack_push(data, value);
}
