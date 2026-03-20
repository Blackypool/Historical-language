#ifndef CONSTRUCTOR
#define CONSTRUCTOR

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../colores.h"

#include "prAverti.h"

#define  L_F __LINE__, __FILE__

typedef int tip_lac;

struct stk
{
    int Kana_ = 0;

    tip_lac* stack = 0;
    ssize_t size = 0;
    ssize_t capacity = 0;

    int number_of_reg = 5;
    int PuSh_rEg[8] = {};

    uintptr_t hash_hash = 0;

    int _reikA = 0;
};

void lego_stack(struct stk* data, ssize_t capacity);

void clear_stk(struct stk* data);

#endif
