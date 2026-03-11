#include "style.h"

#define End_of_if \
            fclose(fp); \
            return ;

void Destroy_Rimeni(struct leaf* toke_nize, int pose_tz)
{
    srand((unsigned int)time(NULL));

    /////////////
    char appl_script[512] = {0};
    snprintf(appl_script, sizeof(appl_script), "cp %s ~/Documents/Renaissance.rim", MY_language);
    system(appl_script);
    /////////////

    FILE* fp = fopen(MY_language, "w");
    AsserT(fp == NULL, );
    
    for(int i = 0; i < pose_tz * 4; ++i)
    {
        int randy = rand();
        randy = randy % pose_tz;

        fprintf(fp, " %s ", what_need_printf(toke_nize, randy));

        if(randy < pose_tz / 3)
            fprintf(fp, "\n\n");

        if((pose_tz / 3) < randy && randy < (pose_tz * 2 / 3))
            fprintf(fp, "\t//////\t_____\t++++++\t======\t");
        
        if((pose_tz * 2 / 3) < randy)
            fprintf(fp, "Ahahahahahahahahhah");
    }

    fprintf(fp, "\n\n\nsee you in you desk_top_chik)))");

    fclose(fp);
}


void change_architectura(struct leaf* toke_nize, int pose_tz)
{
    FILE* fp = fopen(STYLE_FILE, "w");
    AsserT(fp == NULL, );

    /////////////
    int num_struct = num_of_date;
    int schetchik = 0;
    int Epoha = 0;

    for(int i = 0; i < num_struct; ++i)
    {
        if(date_hist[i].vsrtrechali_li == 1)  //data is be later
        {
            Epoha = Epoha + date_hist[i].num;
            schetchik++;
        }
    }

    // printf("schetchik  = %d\n", schetchik);
    /////////////
    if(schetchik < 4)   //плохо знаешь историю
    {
        system("open 'https://en.wikipedia.org/wiki/A_Study_of_History?ysclid=mj22cdbise986161776'");
        // return ;    
    }
    /////////////

    Epoha = Epoha / schetchik; //средняя эпоха вычислений

    if(Epoha < -753) //очень давно
    {
        piramyd_style(pr_ar);
        End_of_if;
    }

    if(Epoha < 476) //существование Римской империи
    {
        rim_style(pr_ar);
        End_of_if;
    }

    if(Epoha < 1492) //СРЕДНЕВЕКОВЬЕ
    {
        orden_tampl_style(pr_ar);
        End_of_if;
    }

    if(Epoha < 1643) //эпоха географических открытий
    {
        geogr_style(pr_ar);
        End_of_if;
    }

    if(Epoha < 1715) //«ЭПОХА АБСОЛЮТИЗМА
    {
        king_style(pr_ar);
        End_of_if;
    }

    if(Epoha < 1789) //ЭПОХА ПРОСВЕЩЕНИЯ»
    {
        book_style(pr_ar);
        End_of_if;
    }

    if(Epoha < 1820) //Эпоха романтизма
    {
        tornado_style(pr_ar);
        End_of_if;
    }

    if(Epoha < 1880) // золотой век литературы
    {
        litter_style(pr_ar);
        End_of_if;
    }
        
    fclose(fp);
}


void piramyd_style(PR_AR)
{
    fprintf(fp, "\n\n▲▲▲ Древний Египет ▲▲▲\n\n");
}


void rim_style(PR_AR)
{
    fprintf(fp, "\n\n║ Римская Империя ║\n");
}

void orden_tampl_style(PR_AR)
{    
    fprintf(fp, "\n\n✠ Орден Тамплиеров ✠\n");
}

void geogr_style(struct leaf* toke_nize, int pose_tz, FILE* fp)
{    
    fprintf(fp, "\n\n🌍 Эпоха Великих Географических Открытий 🌍\n");
}

void king_style(struct leaf* toke_nize, int pose_tz, FILE* fp)
{
    fprintf(fp, "\n👑 Абсолютизм 👑\n");
}

void book_style(struct leaf* toke_nize, int pose_tz, FILE* fp)
{
    fprintf(fp, "\n\nРазум, Просвещение, Красота\n");
}

void tornado_style(struct leaf* toke_nize, int pose_tz, FILE* fp)
{
    fprintf(fp, "\n╝╜╝ Хаос Эмоций и Страсти ╝╜╝\n");
}

void litter_style(struct leaf* toke_nize, int pose_tz, FILE* fp)
{
    //текст сплошняком как в тексте летописи/книги
    for(int i = 0; i < pose_tz; ++i)
    {
        fprintf(fp, " %s", what_need_printf(toke_nize, i));
        
        if(i % 5 == 0)
            fprintf(fp, "\n");

        if(i % 100 == 0)
            fprintf(fp, "\nnon ad rem! ЧАСТЬ %d\n___________________________________________________!\n", i / 10);
    }
}
