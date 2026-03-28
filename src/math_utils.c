#include "math_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

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

int math_sqrt(const char* cmd) {
    int stand_int = atoi(cmd);
    double new_guess;

    if ( stand_int < 0 ) {
        return -1;
    }

    double guess = ( stand_int > 1 ) ? stand_int / 2.0 : 1.0;
    double tolerance = 1e-10;

    while (1) {
        new_guess = (guess + stand_int / guess) / 2.0;

        if ((new_guess - guess < tolerance) && (guess - new_guess < tolerance)) {
            return new_guess;
        }
        guess = new_guess;
    }

    double result = (double)new_guess;

    return result;
}

int math_pow(const char* cmd) {
    int a, b;

    if (sscanf(cmd, "%d %d", &a, &b) == 2) {
        int result = 1;
        for(int i = 0; i < b; i++) result *= a;

        return result;
    }
}

double math_hypot(const char* cmd) {
    int a, b;

    if (sscanf(cmd, "%d %d", &a, &b) != 2) {
        return 0;
    }

    double c = (double)(a * a + b * b);

    return (double)sqrt(c);
    
}
        




