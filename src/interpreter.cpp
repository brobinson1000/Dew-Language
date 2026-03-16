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

std::unordered_map<std::string, varType> variables;
std::unordered_map<std::string, varType*> heap;

void moveCommand(std::istringstream& iss) {
    std::string val, dest;
    iss >> val >> dest;
    auto search = variables.find(val);
    if (search != variables.end()) {
        variables[dest] = search->second;
    } else {
        variables[dest] = val;
    }   
}    




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




int main() {
    std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands;


    commands["DISPLAY"] = displayCommand;
    commands["GET"] = getCommand;
    commands["MOVE"] = moveCommand;
    commands["MOVEH"] = movehCommand;
    commands["FREEH"] = freehCommand; 
    commands["DISPLAY_NEWLINE"] = display_newlineCommand;
    commands["DISPLAY_ENDLINE"] = display_endlineCommand;



    std::string line;
    while(std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) { return toupper(c);});

        auto it = commands.find(cmd);
        if ( it != commands.end()) {
            it->second(iss);
        } else {
            std::cerr << "UNKNOW COMMAND" << cmd << "\n";
        }
    }
}
