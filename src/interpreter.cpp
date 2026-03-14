#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <variant>
#include <memory>
#include <vector>
#include <algorithm>


// Heap and Stack Allocated Data
std::unordered_map<std::string, std::variant<int, double, std::string>> variables;

using varType = std::variant<int, double, std::string>;

std::unordered_map<std::string, varType*> heap;




auto printVar = [](auto& var) {
    if (std::holds_alternative<int>(var)) {
        std::cout << std::get<int>(var) << "\n";
    } else if (std::holds_alternative<double>(var)) {
        std::cout << std::get<double>(var) << "\n";
    } else {
        std::cout << std::get<std::string>(var) << "\n";
}
};



void displayCommand(std::istringstream& iss) {
    std::string word;
    iss >> word;

    auto it = heap.find(word);
    if (it != heap.end()) {
        printVar(*(it->second));
        return;
    }

    auto it_ = variables.find(word);
    if ( it_ != variables.end()) {
        printVar(it_->second);
        return;
    }
}




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

    std::string line;
    while(std::getline(std::cin, line)) {
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::toupper(c);});
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        auto it = commands.find(cmd);
        if ( it != commands.end()) {
            it->second(iss);
        } else {
            std::cerr << "UNKNOW COMMAND" << cmd << "\n";
        }
    }
}
