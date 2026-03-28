#include "math_wrapper.h"
#include "print.h"
#include "interpreter.h"
#include "interpreter_error.h"
#include <iostream>
extern "C" {
#include "math_utils.h"  
}

double sqrtFunc(std::istringstream& iss) {
    std::string arg;
    iss >> arg;

    double sqrt = math_sqrt(arg.c_str());
    return sqrt;
}

void displaySqrt(std::istringstream& iss) {
    std::string arg;
    iss >> arg;
    if (arg.empty()) {
        log("No argument provided for DISPLAY_SQRT");
        return;
    }
    int result = math_sqrt(arg.c_str());
    std::cout << result << "\n";
}


int ceilFunc(std::istringstream& iss) {
    std::string arg;
    iss >> arg;

    int result = math_ceil(arg.c_str());
    return result;
}

void displayCeil(std::istringstream& iss) {
    std::string arg;
    iss >> arg;
    if (arg.empty()) {
        log("No argument provided for DISPLAY_CEIL");
        return;
    }
    int result = math_ceil(arg.c_str());
    std::cout << result << "\n";
}



int floorFunc(std::stringstream& iss) {
    std::string arg;
    iss >> arg;
    
    int result = math_floor(arg.c_str());
    return result;
}

void displayFloor(std::istringstream& iss) {
    std::string arg;
    iss >> arg;
    if (arg.empty()) {
        log("No argument provided for DISPLAY_FLOOR");
        return;
    }
    int result = math_floor(arg.c_str());
    std::cout << result << "\n";
}


double piFunc(std::istringstream& iss) {
    std::string extra;
    if (iss >> extra) {
        std::cerr << "PI does not take arguments\n";
    }
    return math_pi();
}

double powFunc(std::istringstream& iss) {
    int a, b;
    if(!(iss >> a >> b)) {
        log("DISPLAY_POW takes exactly two integers");
        return 0;
    }

    std::string input = std::to_string(a) + " " + std::to_string(b);

    return math_pow(input.c_str());
}

void displayPow(std::istringstream& iss) {
    int a, b;

    if(!(iss >> a >> b)) {
        log("DISPLAY_POW takes exactly two integers");
        return;
    }

    std::string input = std::to_string(a) + " " + std::to_string(b);

    double result = math_pow(input.c_str());

    std::cout << result << "\n";
}



double hypotFunc(std::istringstream& iss) {
    int a, b;
    if(!(iss >> a >> b)) {
        return 0;
    }

    std::string input = std::to_string(a) + " " + std::to_string(b);

    return math_hypot(input.c_str());
}

void displayHypot(std::istringstream& iss) {
    int a, b;
    
    if(!(iss >> a >> b)) {
        log("No argument provided for DISPLAY_HYPOT");
        return;
    }

    std::string input = std::to_string(a) + " " + std::to_string(b);

    double result = math_hypot(input.c_str());

    std::cout << result << "\n";
}
