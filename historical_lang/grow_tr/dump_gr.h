#ifndef GRAPH_DUMP
#define GRAPH_DUMP

#include "../M_Diff.h"


void call_terminal(int number_of_zapusk);

void draw_stick(FILE *fp_out, struct leaf *leaf);

void draw_clear_leaf(FILE *fp_out, struct leaf *leaf);

const char* translate_r(size_t oper);

void picture_of_root(struct leaf *root, int *number_of_zapusk, const char* text);


#endif