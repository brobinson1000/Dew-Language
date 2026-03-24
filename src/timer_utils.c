#include "timer_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void sleepCommand(const char* cmd) {
    int seconds = atoi(cmd);
    sleep(seconds);
}

void timeofdayCommand(const char* cmd) {
    time_t currentTime;
    time(&currentTime);

    printf("%s", ctime(&currentTime));
}




