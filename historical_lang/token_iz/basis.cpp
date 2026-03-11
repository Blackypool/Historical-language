#include "basis.h"

struct numb_base* date_hist = NULL;
int num_of_date = 0;

int history_base_upgrad()
{
    size_t number_char = 0;
    char* all_file = file_pointer_read(&number_char, BASA_HISTORY);
    AsserT(all_file == NULL, -1);
    /////////////

    for(size_t i = 0; i < number_char; ++i)
    {
        if(all_file[i] == '\n' || all_file[i] == '\0')
            ++num_of_date;
    }
    ++num_of_date;

    /////////////
    date_hist = (struct numb_base*)calloc((size_t)num_of_date + 1, sizeof(numb_base));
    AsserT(date_hist == NULL, -2);

    char* cur = all_file;

    for(int i = 0; i < num_of_date; ++i)
    {
        char value_data[256] = {0};

        char* end_str = strchr(cur, '\n');
        if(end_str == NULL)
            break;

        int proverka = sscanf(cur, "$%[^$]$ | %d", value_data, &date_hist[i].num);
        AsserT(proverka != 2, -3);
        
        date_hist[i].value = strdup(value_data);
        cur = end_str + 1;
        // fprintf(stderr, "\n\ni = %d; proverka = %d; value_data = %s \n\n", i, proverka, date_hist[i].value);
    }

    free(all_file);

    return 0;
}


int call_nyrosetochka(char* ans_que, struct leaf* toke_nize, int* pose_tz)
{
    char apple_script[512] = {0};

    system("open -n -a Terminal && ollama serve &");
    snprintf(apple_script, 512, "ollama run phi3:mini \
                                    \"Когда произошло событие: %s? Ответь только числом (год).\"", ans_que);

    /////////////
    FILE* fp = popen(apple_script, "r");
    AsserT(fp == NULL, -1);

    char buffer[256] = {0};
    int data_of_sob = 0;
    while(fgets(buffer , sizeof(buffer), fp))
        {
            if(sscanf(buffer, "%d", &data_of_sob) == 1)
                break;
        }

    if(data_of_sob == 0)
        fprintf(stderr, "\nдаже нейросеть не нашла твое событие(((\n\n");

    pclose(fp);
    /////////////

    /////////////
    FILE* base_hist = fopen(BASA_HISTORY, "a");
    AsserT(base_hist == NULL, -1);

    fprintf(base_hist, "$%s$ | %d\n", ans_que, data_of_sob);

    fclose(base_hist);
    /////////////

    system("killall -9 ollama");


    toke_nize[*pose_tz].type = NUMBER;
    toke_nize[*pose_tz].value.num = data_of_sob;
    (*pose_tz)++;

    return 0;
}
