#ifndef PRAVERTI
#define PRAVERTI

#include "constructor.h"
#include "colores.h"

#define POISON 666

enum ERR_or_GOOD
{
    CAPACITY_FAIL   = 2,
    MEMORY_OVERFLOW = 4,
    NOT_YOUR_MEMORY = 8,
    SO_BIG_VALUE    = 16,
    ALL_RIGHT       = 0
};

void pr_in_tf(struct stk* data, int num_line, const char* file_n);

void yadro_li_you(struct stk* data, int num_line, const char* file_n);

void defence_of_capacity(struct stk* data, int num_line, const char* file_n);

void def_size_capacity(struct stk* data, int num_line, const char* file_n);

void dinamayk_def(struct stk* data, int num_line, const char* file_n);

void double_kanar(struct stk* data, int num_line, const char* file_n);

//void P_O_I_S_O_N(struct stk* data);

uintptr_t hash_hash(struct stk* data);

#endif