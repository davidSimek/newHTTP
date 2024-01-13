#include <stdio.h>

#include "logs.h"

#define RESET_COLOR "\e[m"
#define RED_FOREGROUND "\033[0;31m"
#define BLUE_FOREGROUND "\033[0;34m"

void log_error(const char* message) {
    #ifdef LINUX
    printf("%s[ERROR]: %s%s\n", RED_FOREGROUND, RESET_COLOR, message);
    #else
    printf("[ERROR]: %s\n", message);
    #endif
}
void log_info(const char* message) {
    #ifdef LINUX
    printf("%s[INFO]: %s%s\n", BLUE_FOREGROUND, RESET_COLOR, message);
    #else
    printf("[INFO]: %s\n", message);
    #endif
}
