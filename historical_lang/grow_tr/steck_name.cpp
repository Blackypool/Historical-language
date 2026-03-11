#include "z_constructor.h"
#include "z_push_pop.h"


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

    ////////////
    data->Kana_ = 914;
    data->_reikA = 419;
    ////////////

    data->size = 0;

    data->hash_hash = hash_hash(data);
}

//cleaner_of_steck
void clear_stk(struct stk* data)
{
    if(data == NULL)
    {
        perror("stk is NULL in clearing");
        return;
    }
    data->Kana_ = 0;
    data->capacity = 0;
    data->hash_hash = 0;
    data->size = 0;
    data->_reikA = 0;

    free(data->stack);
    data->stack = NULL;
}


void stack_push(struct stk* data, tip_lac value)
{
    uintptr_t h_a_s_h = hash_hash(data);
    if(h_a_s_h != data->hash_hash)
        perror("Hash hash hash......");


    defence_of_capacity(data, L_F);
    def_size_capacity(data, L_F);
    
    data->stack[data->size] = value;
    data->size++;
    pr_in_tf(data, L_F);

    data->hash_hash = hash_hash(data);
}


tip_lac stack_pop(struct stk* data)
{
    if(data->size == 0)
        perror("size < 0((");

    uintptr_t h_a_s_h = hash_hash(data);
    if(h_a_s_h != data->hash_hash)
        perror("Hash hash hash......");
    
    data->size--;
    tip_lac paramchik = data->stack[data->size];

    pr_in_tf(data, L_F);

    data->hash_hash = hash_hash(data);

    return paramchik;
}
