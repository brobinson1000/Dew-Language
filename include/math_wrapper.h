#pragma once
#include <sstream>

#pragma once
#include <sstream>

// Value-returning wrappers
double sqrtFunc(std::istringstream& iss);
int ceilFunc(std::istringstream& iss);
int floorFunc(std::stringstream& iss);
double powFunc(std::istringstream& iss);
double hypotFunc(std::istringstream& iss);
double piFunc(std::istringstream& iss);

// Display wrappers
void displaySqrt(std::istringstream& iss);
void displayCeil(std::istringstream& iss);
void displayFloor(std::istringstream& iss);
void displayPow(std::istringstream& iss);
void displayHypot(std::istringstream& iss);
