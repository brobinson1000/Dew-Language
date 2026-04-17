#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <variant>
#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "print.h"
#include "error_handling.h"
#include "math_wrapper.h"
#include "unix_wrapper.h"



// Stack, Heap, Const Storage
std::unordered_map<std::string, varType> variables;
std::unordered_map<std::string, varType*> heap;
std::unordered_map<std::string, varType> consts;

// keywords

std::unordered_set<std::string> Keywords {
    "*",
    "+",
    "-",
    "/",
};








bool check_keyword(std::unordered_set<std::string> k, const std::string& name) {
    auto search = k.find(name);
    if ( search != k.end()) {
        log("Can not use keyword");
        return true;
    }
    return false;
}



// check consts space function
bool check_const(const std::string &dest, std::unordered_map<std::string, varType> p) {
    auto search = p.find(dest);
    if ( search != p.end()) {
        log("Variable is declared constant therefore can not be reassigned");
        return true;
    }
    return false;

}

bool check_heap(const std::string &dest, std::unordered_map<std::string, varType*> p) {
    auto search = p.find(dest);
    if (search != p.end()) {
        log("Variable named already used on heap");
        return true;
    }
    return false;
}

bool check_variables(const std::string &dest, std::unordered_map<std::string, varType> p) {
    auto search = p.find(dest);
    if ( search != p.end()) {
        log("Variable name already used on stack");
        return true;
    }
    return false;
}


bool name_exists_anywhere(const std::string& name) {
    if (variables.count(name) || heap.count(name) || consts.count(name)) {
        log("Variable name already exists");
        return true;
    }
    return false;
}

double parseExpression(std::istringstream& iss);

double parseNumber(std::istringstream& iss) {
    double value;
    iss >> value;
    return value;
}

double parseFactor(std::istringstream& iss) {
    if (iss.peek() == '(') {
        iss.get();
        double val = parseExpression(iss);
        iss.get();
        return val;
    }
    return parseNumber(iss);
}

double parseTerm(std::istringstream& iss) {
    double value = parseFactor(iss);

    while (true) {
        if (iss.peek() == '*') {
            iss.get();
            value *= parseFactor(iss);
        } else if (iss.peek() == '/') {
            iss.get();
            value /= parseFactor(iss);
        } else {
            break;
        }
    }

    return value;
}


double parseExpression(std::istringstream& iss) {
    double value = parseTerm(iss);

    while (true) {
        if ( iss.peek() == '+') {
            iss.get();
            value += parseTerm(iss);
        } else if (iss.peek() == '-') {
            iss.get();
            value -= parseTerm(iss);
        } else { break;
}
    }
    return value;
}








void moveconstCommand(std::istringstream& iss) {
    std::string val, dest;
    iss >> val >> dest;

    if (name_exists_anywhere(dest)) return;

    try {
        consts[dest] = std::stoi(val);
    } catch (...) {
        try {
            consts[dest] = std::stof(val);
        } catch (...) {
            consts[dest] = val;
        }
    }
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
    std::string line;
    std::getline(iss, line);

    if (line.empty()) {
        log("INVALID MOVE syntax");
        return;
    }

    if (line[0] == ' ') line.erase(0, 1);

    size_t lastSpace = line.find_last_of(' ');
    if (lastSpace == std::string::npos) {
        log("INVALID MOVE syntax");
        return;
    }

    std::string expr = line.substr(0, lastSpace);
    std::string dest = line.substr(lastSpace + 1);

    if (check_const(dest, consts)) return;
    if (check_heap(dest, heap)) return;

    try {
        std::istringstream exprStream(expr);
        double result = parseExpression(exprStream);

        variables[dest] = result;
        return;
    } catch (...) {}

    auto search = variables.find(expr);
    if (search != variables.end()) {
        variables[dest] = search->second;
        return;
    }

    auto csearch = consts.find(expr);
    if (csearch != consts.end()) {
        variables[dest] = csearch->second;
        return;
    }

    try {
        variables[dest] = std::stoi(expr);
        return;
    } catch (...) {}

    try {
        variables[dest] = std::stof(expr);
        return;
    } catch (...) {}

    variables[dest] = expr;
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

    if ( check_variables(dest, variables)) return;


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

    if ( search == heap.end()) {
        log("Variable not located on the heap");
        return;
    }


  

    delete search->second;
    search->second = nullptr;
    heap.erase(search);
        

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

    std::cin >> std::ws; // discard leading white space char
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
    //commands["DISPLAY_PI"] = display_pi; THERE IS AN ERROR IN THE CODE!!
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
    //functions["FLOOR"] = floorFunc; THERE IS AN ERROR IN THIS CODE

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
