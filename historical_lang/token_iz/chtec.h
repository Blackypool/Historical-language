#ifndef CHTEC_HH
#define CHTEC_HH

#define ARG_s char* ans_que, struct leaf* toke_nize, int* pose_tz, size_t* now

#include "../M_Diff.h"


size_t number_of_file(const char* name_file);

char* file_pointer_read(size_t *number_char, const char* name_file);


void skip_comments(char* text_rim, size_t* now);

void skip_spasec(char* text_rim, size_t* now);

char* create_word(char* text_rim, size_t* now, const char type_word);


#endif