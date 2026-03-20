#ifndef ENUMICHE
#define ENUMICHE

enum for_user
{
    OPE_rativ_ka = 28000,
    STK_capacity = 10,
    RET_capacity = 10,
    NUM_label_ss = 200,
};

#define FILE_for_SPU "asm_into_bin.bin"
#define FILE_for_ASM "../z_asm_for_start/lang.asm"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "stack_func/constructor.h"
#include "stack_func/push_pop.h"
#include "asembler/file_commands.h"

typedef int ans_typ;

#define ASSERTICHE(ptr, ret) \
        if((ptr) == NULL) {   \
            fprintf(stderr, "\nassert react in %s:%d\n", __FILE__, __LINE__); \
            return ret; \
        }


#define ASSCANFOR_ASM(ret, lin)  \
        if((ret) < 0) { \
            fprintf(stderr, "\nsscanf ruined in %s:%d, error in %s:%d\n", __FILE__, __LINE__, FILE_for_ASM, lin + 1); \
            return  NULL; \
        }


#define ASSCANF(ret)  \
    if((ret) < 0) { \
        fprintf(stderr, "\nsscanf ruined in %s:%d\n", __FILE__, __LINE__); \
        return  NULL; \
        }


#define LOGIC(MASK, func_type)   \
        if((MASK & operation)){   \
            func_type(data, stk_ret, line, str_str, lines_all, push_memory, operation);\
            return SU_CC_ESS;\
        }


#define DEBUG printf("hranilische[%d] = {%d} = (%s)[%d}\n", sche, hranilische[sche], str_str[lin], lin)
            

#define ST_PP(data)\
        int v_1 = stack_pop(data);\
        int v_2 = stack_pop(data);


#define TO_MUSH_ARG \
        struct stk* data, struct stk* stk_ret, int *line, int* str_str, int lines_all, int* push_memory, int operation


#define FOR_SW(line)\
        operation = str_str[*line];


struct SPU
{
    int* ram       = 0;
    stk  start_stk = {};
    stk  stk_ret   = {};
};


struct ASM
{
    int* black_metka = 0;
    char ** str_str  = 0;
    char* fuull_asm = 0;
};


struct operatio
{
    char    opera[16];
    int     maska;
    size_t  len_len;
    int     need_param;
};


enum calcic
{

    _CALC_      = 0x00000010,
    CMD_ADD_    = 0x00000011,
    CMD_SUB_    = 0x00000012,
    CMD_MUL_    = 0x00000013,
    CMD_DIV_    = 0x00000014,     
    CMD_POW_    = 0x00000015,
    CMD_SQRT_   = 0x00000016,
    
    _BASE_      = 0x00000100,
    CMD_PUSH_   = 0x00000101,
    CMD_OUT_    = 0x00000102,
    CMD_HLT_    = 0x00000103,
    
    _REG_       = 0x00001000,
    CMD_POPREG_ = 0x00001001,
    CMD_PSHREG_ = 0x00001002,

    _GAMMY_     = 0x00010000,
    CMD_JMP_    = 0x00010001,
    CMD_JB_     = 0x00010002,
    CMD_JBE_    = 0x00010003,
    CMD_JA_     = 0x00010004,
    CMD_JAE_    = 0x00010005,
    CMD_JE_     = 0x00010006,
    CMD_JNE_    = 0x00010007,

    _FUNCN_     = 0x00100000,
    CMD_RET_    = 0x00100001,
    CMD_CALL_   = 0x00100002,
    CMD_SLEP_   = 0x00100003,

    _MEMOR_     = 0x01000000,
    CMD_POPM_   = 0x01000001,
    CMD_PUSHM_  = 0x01000002,
    CMD_DRAW_   = 0x01000003,

    CMD_INT_    = 0x10000000,
};

enum er_sC
{
    SU_CC_ESS = 1,
    ER_R_OR   = 911
};

#define ARG_CLC \
        struct stk* data, struct stk* /*stk_ret*/, int* /*line*/, int* /*str_str*/, int /*lines_all*/, int* /*push_memory*/, int operation

#define ARG_STF \
        struct stk* data, struct stk* /*stk_ret*/, int *line, int* str_str, int lines_all, int* /*push_memory*/, int operation

#define ARG_REG \
        struct stk* data, struct stk* /*stk_ret*/, int *line, int* str_str, int /*lines_all*/, int* /*push_memory*/, int operation

#define ARG_JMP \
        struct stk* data, struct stk* /*stk_ret*/, int *line, int* str_str, int /*lines_all*/, int* /*push_memory*/, int operation

#define ARG_FFC \
        struct stk* /*data*/, struct stk* stk_ret, int *line, int* str_str, int /*lines_all*/, int* /*push_memory*/, int operation

#define ARG_WWM \
        struct stk* data, struct stk* /*stk_ret*/, int *line, int* str_str, int /*lines_all*/, int* push_memory, int operation

#define ARG_INF \
        struct stk* data, struct stk* /*stk_ret*/, int* /*line*/, int* /*str_str*/, int /*lines_all*/, int* /*push_memory*/, int /*operation*/


#endif