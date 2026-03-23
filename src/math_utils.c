#include "math_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


double math_pi(void) {
    return 3.14159265358979323846;
}



int math_floor(const char* cmd) {
    double stand_db = atof(cmd);

    int f = (int)stand_db;

    if ( stand_db < 0 && stand_db != f) {
        f = f - 1;
    } 
    return f;
}

int math_ceil(const char* cmd) {
    double stand_db = atof(cmd);
    
    int f = (int)stand_db;

    if (stand_db > 0 && stand_db != f) {
        f = f + 1;
    }
    return f;
}

int math_abs(const char* cmd) {
    int stand_int = atoi(cmd);

    if (stand_int == 0) return 0;

    return stand_int < 0 ? -stand_int : stand_int;
  
}

