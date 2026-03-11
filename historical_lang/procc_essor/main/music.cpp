#include "music.h"


void call_terminal(const char* command) 
{
    char apple_script[512] = {};
    snprintf(apple_script, sizeof(apple_script), "osascript -e " \
    "'tell application \"Terminal\" to do script \"%s\" in front window'", command);

    system(apple_script);
}

// через форк сделать два вывода видео в два терминала два мультика одновременно 
// open -n -a Terminal
// debug ifndef endif
// "osascript -e 'tell application \"Terminal\" to do script \"%s\" in front window'", 