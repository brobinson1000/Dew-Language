#include "print.h"
#include "interpreter.h"
#include "error_handling.h"
#include <iostream>


extern "C" { 
#include "unix_utils.h"
}



void sysCommand(std::istringstream& iss) {
    std::string cmd;
    std::getline(iss >> std::ws, cmd);
    if (cmd.empty()) {
        log("No argument provided for SYSTEM");
        return;
    }
    systemCommand(cmd.c_str());
}

void timesleepCommand(std::istringstream& iss) {
    std::string cmd;
    std::getline(iss, cmd);

    if (cmd.empty()) {
        return;
        log("No argument provided for SLEEP");
    } 
    
    sleepCommand(cmd.c_str());
}
