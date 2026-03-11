#ifndef ITS_FOR_Tokenization_H
#define ITS_FOR_Tokenization_H

#include "../M_Diff.h"

struct A_S_T* lex_ana();

int func_defolt_or_user(struct leaf* toke_nize, int* pose_tz, size_t* now, char* ans_que);

void its_number_time(char* text_rim, size_t* now, struct leaf* toke_nize, int* pose_tz);

void its_over(ARG_s, char* text_rim);

void its_val_time(ARG_s, int* max_varia);

void its_schto_to(struct leaf* toke_nize, int* pose_tz, size_t* now, char shto_to);

char* what_need_printf(leaf* toke_nize, int pose);

void its_initi(struct leaf* toke_nize, int* pose_tz, size_t* now);

int check_znaki(struct leaf* toke_nize, int* pose_tz, size_t* now, char* ans_que);


#endif