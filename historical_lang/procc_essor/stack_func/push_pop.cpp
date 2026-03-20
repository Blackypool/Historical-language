#include "push_pop.h"

void stack_push(struct stk* data, tip_lac value)
{
    uintptr_t h_a_s_h = hash_hash(data);
    if(h_a_s_h != data->hash_hash)
        perror("Hash hash hash......");

    dinamayk_def(data, L_F);
    double_kanar(data, L_F);

    defence_of_capacity(data, L_F);
    def_size_capacity(data, L_F);
    
    data->stack[data->size] = value;
    data->size++;
    pr_in_tf(data, L_F);

    data->hash_hash = hash_hash(data);

    dinamayk_def(data, L_F);
    double_kanar(data, L_F);
}

tip_lac stack_pop(struct stk* data)
{
    
    dinamayk_def(data, L_F);
    double_kanar(data, L_F);

    if(data->size == 0)
        perror("size < 0((");

    uintptr_t h_a_s_h = hash_hash(data);
    if(h_a_s_h != data->hash_hash)
        perror("Hash hash hash......");
    
    data->size--;
    tip_lac paramchik = data->stack[data->size];

    pr_in_tf(data, L_F);

    data->hash_hash = hash_hash(data);

    dinamayk_def(data, L_F);
    double_kanar(data, L_F);

    return paramchik;
}
