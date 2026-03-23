#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <variant>
#include <memory>
#include <vector>
#include <algorithm>

#include "print.h"



extern "C" { 
#include "system.h"
#include "timer_utils.h"
#include "math_utils.h"
}


// Stack and Heap Storage
std::unordered_map<std::string, varType> variables;
std::unordered_map<std::string, varType*> heap;



/*
 * moveCommand:
 * Copies a variable from stack into a stack location.
 *
 * Parameters:
 *   iss - input string stream containing the source and destination
 *
 * Behavior:
 *   - If source exists in stack, copy it to destination
 *   - If not, create a new stack variable with the literal value
 */

void moveCommand(std::istringstream& iss) {
    std::string val, dest;
    iss >> val >> dest;
    auto search = variables.find(val);
    if (search != variables.end()) {
        variables[dest] = search->second;
    } else {
        try {
            int n = std::stoi(val);
            variables[dest] = n;
    } catch (...) {
        try {
            float f = std::stof(val);
            variables[dest] = f;
        } catch (...) {
            variables[dest] = val;
        }
    }
  }

}    



/*
 * movehCommand:
 * Copies a variable from heap into another heap location.
 *
 * Parameters:
 *   iss - input string stream containing the source and destination
 *
 * Behavior:
 *   - If source exists in heap, copy it to destination
 *   - If not, create a new heap variable with the literal value
 */

void movehCommand(std::istringstream& iss) {
    std::string val, dest;
    iss >> val >> dest;

    auto search = heap.find(val);
    if ( search != heap.end()) {
        heap[dest] = new varType(*(search->second));
    } else {
        heap[dest] = new varType(val);
    }
}



/*
 * freehCommand:
 * Check if variable is stored on the heap and then free variables heap memory.
 *
 * Parameters:
 *   iss - input string stream contain variable name
 *
 * Behavior:
 *   - If source exists in heap, free in from memory and erase from structure
 *   - If not, throw error
 */

void freehCommand(std::istringstream& iss) {
    std::string varName;
    iss >> varName;

    auto search = heap.find(varName);
    if ( search != heap.end()) {
        delete search->second;
        search->second = nullptr;
        heap.erase(search);
        
    } 
}



/*
 * getCommand:
 * Gets user input and stores it in stack.
 *
 * Parameters:
 *   iss - input string stream containing the variable name
 *
 * Behavior:
 *   - 
 *   - 
 */
void getCommand(std::istringstream& iss) {
    std::string varName;
    iss >> varName;

    if (varName.empty()) {
        std::cerr << "ERROR: No variable specified\n";
        return;
    }

    std::string inputValue;

    std::getline(std::cin, inputValue);

    // Detect numeric type
    try {
        variables[varName] = std::stoi(inputValue);
        return;
    } catch(...) {}

    try {
        variables[varName] = std::stod(inputValue);
        return;
    } catch(...) {}

    variables[varName] = inputValue; // fallback to string
}

void sysCommand(std::istringstream& iss) {
    std::string cmd;
    std::getline(iss >> std::ws, cmd);
    if (cmd.empty()) {
        std::cerr << "NO COMMAND";
        return;
    }
    systemCommand(cmd.c_str());
}

void timesleepCommand(std::istringstream& iss) {
    std::string cmd;
    std::getline(iss, cmd);

    if (cmd.empty()) {
        return;
        std::cerr << "NO COMMAND";
    } 
    
    sleepCommand(cmd.c_str());
    std::cout << "DONE";
}

varType ceilFunc(std::istringstream& iss) {
    std::string arg;
    iss >> arg;

    int result = math_ceil(arg.c_str());
    return result;
}

void displayCeil(std::istringstream& iss) {
    std::string arg;
    iss >> arg;
    if (arg.empty()) {
        std::cerr << "NO ARGUMENT PROVIDED FOR CEIL\n";
        return;
    }
    int result = math_ceil(arg.c_str());
    std::cout << result << "\n";
}



varType floorFunc(std::stringstream& iss) {
    std::string arg;
    iss >> arg;
    
    int result = math_floor(arg.c_str());
    return result;
}

void displayFloor(std::istringstream& iss) {
    std::string arg;
    iss >> arg;
    if (arg.empty()) {
        std::cerr << "No argument provided for FLOOR\n";
        return;
    }
    int result = math_floor(arg.c_str());
    std::cout << result << "\n";
}


varType piFunc(std::istringstream& iss) {
    std::string extra;
    if (iss >> extra) {
        std::cerr << "PI does not take arguments\n";
    }
    return math_pi();
}

void display_pi(std::istringstream& iss) {
    std::string cmd;
    std::getline(iss, cmd);

    std::cout << math_pi();
}


int main() {
    std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands;
    std::unordered_map<std::string, std::function<varType(std::istringstream&)>> functions;





    commands["DISPLAY"] = displayCommand;
    commands["GET"] = getCommand;
    commands["MOVE"] = moveCommand;
    commands["MOVEH"] = movehCommand;
    commands["FREEH"] = freehCommand; 
    commands["DISPLAY_NEWLINE"] = display_newlineCommand;
    commands["DISPLAY_ENDLINE"] = display_endlineCommand;
    commands["DISPLAY_FLOAT"] = display_floatCommand;
    commands["DISPLAY_PI"] = display_pi;
    commands["SYSTEM"] = sysCommand;
    commands["SLEEP"] = timesleepCommand;    
    commands["DISPLAY_FLOOR"] = displayFloor;
    commands["DISPLAY_CEIL"] = displayCeil;


    functions["CEIL"] = ceilFunc;
    functions["PI"] = piFunc;
    //functions["FLOOR"] = floorFunc;

    std::string line;
    while(std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) { return toupper(c);});
    
        auto it = commands.find(cmd);
        if (it != commands.end()) {
            it->second(iss);
        } else {
            auto fit = functions.find(cmd);
            if (fit != functions.end()) {
                varType result = fit->second(iss);

                //std::visit([](auto&& v) {
                  //  std::cout << v << std::endl;
                //}, result);

            } else {
                std::cerr << "UNKNOWN COMMAND " << cmd << "\n";
            }
        }


    }
}
