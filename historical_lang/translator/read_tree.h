#ifndef CHTEC_H
#define CHTEC_H

#include "../M_Diff.h"

#define Arg_s FILE* fp, Le_af leaf, ar_get
#define arg_s fp, leaf, ast

struct asm_dump
{   
    int enam_chik;

    const char* asm_asm;
};

void Asm_ret_for_rek_supp(FILE* fp);

int asm_main(FILE* fp, Le_af root, ar_get);

void Asm_another(FILE* fp, Le_af leaf, ar_get);

void user_oper_init(Arg_s);

void func_open_space(Le_af leaf, ar_get, int how_much_func, int num_func);

void Asm_init(Arg_s);

void Asm_ass_ignment(Arg_s);

void Asm_expression(Arg_s);

void var_printing(FILE* fp, Le_af leaf, ar_get);

void func_user_ptinting(FILE* fp, Le_af leaf, ar_get);

void Asm_get_args_(FILE* fp, Le_af leaf, ar_get, int num_in_f, table_name* params, int *i);

void Asm_get_left_args_(FILE* fp, Le_af leaf, ar_get, table_name* params, int i);

int where_you_from(ar_get, char* name_var, int* is_global);

int searching_func(const char* func_name, ar_get);



char* file__read(const char* name_file);

size_t number__file(const char* name_file);

int what__opera_znak(const char* ans_que);

int what__type(const char* ans_que);

char* doing_word(char **text_rim_ptr, const char type_word);

void skip_pper(char **curent_in_txt);

Le_af new_leaf_chik(char** curent_in_txt_ptr);

struct leaf* create_base(char** curent_in_txt_ptr);


#endif