#include "../M_Diff.h"

void AST_cleaner(ar_get);

int main(int argc, char *argv[])
{
    char* name_of_compile_file = argv[1];

    struct A_S_T* ast = lex_ana(name_of_compile_file);
    AsserT(ast == NULL, -1);

    lego_stack(&ast->var_ble_tabl, ast->max_num);

    ast->pose = 0;
    Le_af root = Get_G(ast);
    AsserT(root == NULL, -1);
    picture_of_root(root, &ast->var_num, "Get_G(ast)");


    int err = pre_order_print(root, ast);
    AsserT(err < 0, -1);

    
    // fell_a_root(&root);

    // AST_cleaner(ast);

    return 0;
}


void AST_cleaner(ar_get)
{
    clear_stk(&ast->var_ble_tabl);

    free((void*)ast->file_name);
    ast->file_name = NULL;

    for(int i = 0; i < ast->max_pose; ++i)
    {
        if(&ast->tok_mas[i] != NULL)
        {
            switch (ast->tok_mas[i].type)
            {

            case OPERAT:
                    ast->tok_mas[i].value.oper = 0;
                break;

            case VARIA:
                    free((void*)ast->tok_mas[i].value.x);
                    ast->tok_mas[i].value.x = NULL;
                break;
            
            case USER_OPER:
                    free((void*)ast->tok_mas[i].value.us_op);
                    ast->tok_mas[i].value.us_op = NULL;
                break;

            case NUMBER:
                    ast->tok_mas[i].value.num = 0;
                break;

            case Z_NAK:
                    ast->tok_mas[i].value.oper = 0;
                break;

            case NO_ARGS:
                    free((void*)ast->tok_mas[i].value.x);
                    ast->tok_mas[i].value.x = NULL;
                break;

            
            default:
                break;

            }

            ast->tok_mas[i].type = 0;
            ast->tok_mas[i].lines_in_Rim = 0;
        }
    }

    ast->max_pose = 0;
    ast->max_num = 0;
    ast->var_num = 0;
    ast->pose = 0;
    ast->func_num = 0;
    ast->max_func_num = 0;
}


// void pre_order_printf(struct leafs *leaf)
// {
//     if(leaf != NULL)
//     {
//         printf("(");

//         printf("%d", leaf->value);


//         if(leaf->left != NULL)
//             pre_order_printf(leaf->left);

//         if(leaf->right != NULL)
//             pre_order_printf(leaf->right);

//         printf(")");
//     }
// }
