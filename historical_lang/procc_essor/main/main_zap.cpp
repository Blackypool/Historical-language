#include"music.h"

#ifndef ALL_COM
#define ALL_COM

int main() 
{
    system("open -n -a Terminal");
    
    call_terminal("cd ~/Desktop/прога/procc/codegen");
    call_terminal("make");
    call_terminal("./a.out");

    call_terminal("cp ~/Desktop/прога/procc/codegen/asm.asm ~/Desktop/прога/procc/asembler/asm.asm");

    sleep(3);
    system("open -n -a Terminal");
    
    call_terminal("cd ~/Desktop/прога/procc/asembler");
    call_terminal("make");
    call_terminal("./a.out");
    
    
    pid_t pid = fork();

    if(pid == 0)
    {
        system("open -n -a Terminal");
        
        sleep(3);
        call_terminal("cd ~/Desktop/прога/procc/spu");
        call_terminal("make");
        call_terminal("./a.out");
    }
        
    else system("afplay Hitsujibungaku.mp3");

    return 0;
    
    return 0;
}

#endif

//комментарии и пустые строчки
#ifndef COD_GEN
#define COD_GEN

int main() 
{
    system("open -n -a Terminal");
    
    call_terminal("cd ~/Desktop/прога/procc/codegen");
    call_terminal("make");
    call_terminal("./a.out");
    
    return 0;
}

#endif


#ifndef ASM_BIN
#define ASM_BIN

int main() 
{
    system("open -n -a Terminal");
    
    call_terminal("cd ~/Desktop/прога/procc/asembler");
    call_terminal("make");
    call_terminal("./a.out");
    
    return 0;
}

#endif


#ifndef SPU_SPU
#define SPU_SPU

int main() 
{
    // pid_t pid = fork();
    system("afplay Hitsujibungaku.mp3 &");

    // if(pid == 0)
    // {
        system("open -n -a Terminal");
        
        sleep(2);
        call_terminal("cd ~/Desktop/прога/procc/spu");
        call_terminal("make");
        call_terminal("./a.out");
    // }
        
    // else system("afplay Hitsujibungaku.mp3");

    return 0;
}

#endif