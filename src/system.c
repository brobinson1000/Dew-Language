#include "system.h"
#include <stdio.h>
#include <stdlib.h>

void systemCommand(const char* cmd) {
    if (!cmd) return;
    int ret = system(cmd);
    if ( ret != 0 ) {
        fprintf(stderr, "Command failed with exit code %d\n", ret);
    }
}
