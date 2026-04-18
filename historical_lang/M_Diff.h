#ifndef MAIN_MATH_DIF_H
#define MAIN_MATH_DIF_H

//_________FOR FUST USE______
#define BASA_HISTORY "token_iz/history.rim"                  //база событий с данными
#define STYLE_FILE   "style.rim"                    //перезаписываем оригинал в нужном стиле
//откуда читаем = argc/argv == ./a.out z_test_programs/prime_kvadr.rim
//___________________________

typedef double typ_of_x;

#define ar_get struct A_S_T* ast
#define Le_af struct leaf*
#define Le_af_leaf struct leaf *leaf


#define CUR_ent ast->tok_mas[ast->pose]
#define CUR_OPER CUR_ent.value.oper

#define GLOBAL 1
#define LOCAL  0

#define COUNT_OF_MEM_FOR_FUNC 150

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
#include <time.h>


struct table_name
{
    char* name;
    
    int est_net;

    size_t size_tabl;

    int adress;

    int num_param;

    table_name* init_params;//массив указателей на перевеменные которые при вызове функции участвуют
};

typedef table_name* tip_lac;

struct stk
{
    int Kana_ = 0;

    tip_lac* stack = 0;
    ssize_t size = 0;
    ssize_t capacity = 0;

    uintptr_t hash_hash = 0;

    int _reikA = 0;
};


union un_ited
{
    const char* x;

    size_t oper;

    typ_of_x num;

    const char* us_op;
};


struct leaf
{
    size_t type;
    union un_ited value;
    size_t lines_in_Rim;


    struct leaf* prev;
    struct leaf* left;
    struct leaf* right;
};


struct A_S_T
{
    leaf* tok_mas;
    int pose;
    int max_pose;

    stk var_ble_tabl;
    int var_num;
    int max_num;

    table_name* userz_func;
    int func_num;
    int max_func_num;
    int init_num;

    const char* file_name; 
    
    int Glob_Locl;

    int Adress_next;
};


struct command_s
{
    const char* value;

    size_t e_num;
};
extern struct command_s com_m_trnslte[];
extern const int com_struct_size;

struct znaki
{
    const char* value;

    int e_num;

    const char* for_dump;
};
extern struct znaki prepinan[];
extern const int znaki_struct_size;

// struct leaf_before
// {
//     size_t type;
//     union un_ited value;

    
// };

enum type_t
{
    OPERAT = 1223,

    VARIA = 1,
    
    NUMBER = 0,

    END_OF_FILE = 333,

    USER_OPER = 888,

    Z_NAK = 999,

    CALL_F = 1111,
    
    NO_ARGS = 287,

    CONECTION = 777,
};

enum ALL_OPer {

    ADD_C  = 4096,
    SUB_C  = 4097,
    MUL_C  = 4098,   
    DIV_C  = 4099,    
    POW_C  = 4100,   
    SQRT_C = 4101,

    PRINT_F = 23,
    CONNEC_T = 24,
    FUNC_C = 25,
    
    
    L_smaller_R   = 8192, 
    L_E_smaller   = 8193,  
    L_bigger_R    = 8194, 
    L_E_bigger    = 8195, 
    EQUAL_C       = 8196, 
    N_EQUAL_C     = 8197,  
    

    LOG_AND = 12288,   
    LOG_OR  = 12289,    
    
  
    IF_C    = 16384,   
    ELSE_C  = 16385,    
    WHILE_C = 16386,   
    
    OUT_C   = 20480,    
    SCAN_C  = 20481,    
    DRAW_C  = 20482,    
    
   
    PUSHM_C = 24576,  
    RET_C   = 24577,   
    HLT_C   = 24578,  
    
   
    SKOB_krug_L = 28672, 
    SKOB_krug_R = 28673, 
    SKOB_figu_L = 28674, 
    SKOB_figu_R = 28675,  
    ZAPYTAYA    = 28676, 
    TOCHKA_ZAP  = 28677,  
    
    
    RAVNO = 32768,     
    IN_IT = 32769,
};

#define AsserT(what_need, retern)  \
            if(what_need){  \
                fprintf(stderr, "\nerror in line, %s:%d\n", __FILE__, __LINE__);  \
                return retern;  \
            }

#define  DE_Bug \
    // char* de_bug = what_need_printf(ast->tok_mas, ast->pose); \
    // fprintf(stderr, "========FUNC_%s=======\nnow = [%d]    type_token = {%zu}   value = '%s'\n\n", __func__, ast->pose, CUR_ent.type, de_bug); \


    ///проверка области видимости
#define OBLAST_SEE \
    if(see_var_li(ast) < 0)  \
    { \
        fprintf(stderr, "=====FUNC_%s is havent got args in oblast vidimosti", __func__); \
        return NULL; \
    }

//for tree
#include "grow_tr/seeing_zone.h"
#include "grow_tr/chitalka_main.h"
#include "grow_tr/distuct.h"
#include "grow_tr/dump_gr.h"

//tokeni_z
#include "token_iz/basis.h"
#include "token_iz/chtec.h"
#include "token_iz/style.h"
#include "token_iz/its_its.h"

//steck_chik
#include "grow_tr/z_constructor.h"
#include "grow_tr/z_prAverti.h"
#include "grow_tr/z_push_pop.h"

//translyator
#include "translator/read_tree.h"
#include "translator/logical_summ.h"
#include "translator/compare_s_func.h"


#endif