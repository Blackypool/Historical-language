#ifndef ALL_HHH
#define ALL_HHH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "readers.h"
#include "pechatnik_asm.h"
#include "for_fast_use.h"

#define ASSERTICHE(ptr, ret) \
        if((ptr) == NULL) {   \
            fprintf(stderr, "\nassert react in %s:%d\n", __FILE__, __LINE__); \
            return ret; \
        }


#define ASSCANF(ret, retern)  \
    if((ret) < 0) { \
        fprintf(stderr, "\nsscanf ruined in %s:%d\n", __FILE__, __LINE__); \
        return  retern; \
        }


struct GEN
{
    size_t char_in_file = 0;
    char* full_txt = 0;
};


#endif