#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "unix_utils.h"

void systemCommand(const char* cmd) {
    if (!cmd) return;
    int ret = system(cmd);
    if ( ret != 0 ) {
        fprintf(stderr, "Command failed with exit code %d\n", ret);
    }
}

void sleepCommand(const char* cmd) {
    int seconds = atoi(cmd);
    sleep(seconds);
}

void timeofdayCommand(const char* cmd) {
    time_t currentTime;
    time(&currentTime);

    printf("%s", ctime(&currentTime));
}


