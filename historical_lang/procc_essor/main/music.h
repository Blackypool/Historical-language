#ifndef MUS_HHH
#define MUS_HHH

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



#define COD_GEN
#define ASM_BIN
// #define SPU_SPU

#define ALL_COM


void call_terminal(const char* command);

#endif