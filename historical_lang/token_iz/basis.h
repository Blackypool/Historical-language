#ifndef BASA_DAN_HIST_H
#define BASA_DAN_HIST_H

#include "../M_Diff.h"

struct numb_base
{
    const char* value;

    int num;

    int vsrtrechali_li;
};

#define BASA_HISTORY "history.rim"  //база событий с данными
#define STYLE_FILE   "style.rim"    //перезаписываем оригинал в нужном стиле
#define MY_language  "test.rim"     //откуда читаем


extern struct numb_base* date_hist;
extern int num_of_date;

int history_base_upgrad();
int call_nyrosetochka(char* ans_que, struct leaf* toke_nize, int* pose_tz);


#endif