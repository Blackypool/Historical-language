#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) 
{        
    char apple_script[120] = {};
    snprintf(apple_script, sizeof(apple_script), "cd historical_lang && ./a.out %s", argv[1]);
    system(apple_script);

    snprintf(apple_script, sizeof(apple_script), "cd historical_lang/translator && ./a.out %s", argv[2]);
    system(apple_script);

    snprintf(apple_script, sizeof(apple_script), "cd historical_lang/procc_essor/asembler && ./a.out %s", argv[2]);
    system(apple_script);

    snprintf(apple_script, sizeof(apple_script), "cd historical_lang/procc_essor/spu && ./a.out %s", argv[2]);
    system(apple_script);

    return 0;
}
    // компилятор       запуск скрипта.        название комипилированного.   название конечного/ то что указывается в конце файла
//   g++ compile.cpp && ./a.out z_test_programs/factorial.rim facto_rial    -- запуск факторила
//                  name of file                text in the end of file.rim
//   g++ compile.cpp && ./a.out z_test_programs/prime_kvadr.rim prime_kvadr -- запуск квадратки