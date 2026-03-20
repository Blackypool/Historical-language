#include "constructor.h"

void lego_stack(struct stk* data, ssize_t capacity)
{
    if(data == NULL)
    {
        perror("stk is NULL in constructor(((");
        return;
    }
    
    data->capacity = capacity;
    defence_of_capacity(data, L_F);

    data->stack = (tip_lac*) calloc((size_t)data->capacity + 2, sizeof(tip_lac));
    yadro_li_you(data, L_F);
    //P_O_I_S_O_N(data);

    int x_x = data->number_of_reg;  // количество регистров
    for(int i = 0; i < x_x; ++i)
        data->PuSh_rEg[i] = 0;

    data->stack[0] = 23;
    data->stack[data->capacity + 1] = 7557;                                                                                                                                                                   

    data->Kana_ = 914;
    data->_reikA = 419;

    data->size = 1;

    data->hash_hash = hash_hash(data);

    dinamayk_def(data, L_F);
    double_kanar(data, L_F);
}

//очищаем стэк
void clear_stk(struct stk* data)
{
    if(data == NULL)
    {
        perror("stk is NULL in clearing");
        return;
    }
    
    data->size = 0;
    data->capacity = 0;
    free(data->stack);
}
