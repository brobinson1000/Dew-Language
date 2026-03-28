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
#include "error_handling.h"
#include "math_wrapper.h"
#include "unix_wrapper.h"



// Stack, Heap, Const Storage
std::unordered_map<std::string, varType> variables;
std::unordered_map<std::string, varType*> heap;
std::unordered_map<std::string, varType> consts;

// check consts space function
void check_const(const std::string &dest, std::unordered_map<std::string, varType> p) {
    auto search = p.find(dest);
    if ( search != p.end()) {
        log("Variable is declared constant therefore can not be reassigned");
        return;
    }
}

void check_variables(const std::string &dest, std::unordered_map<std::string, varType> p) {
    auto search = p.find(dest);
    if ( search != p.end()) {
        log("Variable name already used on stack");
        return;
    }
}




void moveconstCommand(std::istringstream& iss) {
    std::string val, dest;
    iss >> val >> dest;

    check_const(dest, consts);
    
    consts[dest] = val;
}
        



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

    auto search_ = heap.find(dest);
    if (search_ != heap.end()) {
        log("Variable name already used on the heap");
        return;
    }

    check_const(dest, consts);

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

    auto search_ = variables.find(dest);
    if ( search_ !=  variables.end()) {
        log("Variable declared already on the stack");
        return;
    }



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
        log("No argument provided for GET");
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






int main() {
    std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands;
    std::unordered_map<std::string, std::function<varType(std::istringstream&)>> functions;





    commands["DISPLAY"] = displayCommand;
    commands["GET"] = getCommand;
    commands["MOVE"] = moveCommand;
    commands["MOVE_CONST"] = moveconstCommand;
    commands["MOVEH"] = movehCommand;
    commands["FREEH"] = freehCommand; 
    commands["DISPLAY_NEWLINE"] = display_newlineCommand;
    commands["DISPLAY_ENDLINE"] = display_endlineCommand;
    commands["DISPLAY_FLOAT"] = display_floatCommand;
    //commands["DISPLAY_PI"] = display_pi;
    commands["SYSTEM"] = sysCommand;
    commands["SLEEP"] = timesleepCommand;    
    commands["DISPLAY_FLOOR"] = displayFloor;
    commands["DISPLAY_CEIL"] = displayCeil;
    commands["DISPLAY_SQRT"] = displaySqrt;
    commands["DISPLAY_HYPOT"] = displayHypot;
    commands["DISPLAY_POW"] = displayPow;

    functions["CEIL"] = ceilFunc;
    functions["PI"] = piFunc;
    functions["SQRT"] = sqrtFunc;
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
