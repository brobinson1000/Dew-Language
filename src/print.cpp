#include "print.h"
#include <iostream>
#include <variant>
#include <unordered_map>
#include <string>




auto printVar = [](auto& var) {
    if (std::holds_alternative<int>(var)) {
       std::cout << std::get<int>(var);
    } 
    else if (std::holds_alternative<double>(var)) {
        std::cout << std::get<double>(var);
    } 
    else {
        std::cout << std::get<std::string>(var);
    }
};


auto printStringNL = [](auto& var) {
    if (std::holds_alternative<std::string>(var)) { 
        std::cout << std::get<std::string>(var) << "\n";
        std::cout.flush();
    } 
    else {
        return;
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

void display_newlineCommand(std::istringstream& iss) {
    std::cout << "\n";
    std::cout.flush();
}

void display_endlineCommand(std::istringstream& iss) {
    std::string word;
    iss >> word;
    auto it = heap.find(word);
    if ( it != heap.end()) {
        printStringNL(*(it->second));
        return;
    }

    auto it_ = variables.find(word);
    if ( it_ != variables.end()) {
        printStringNL(it_->second);
        return;
    }
    
    std::string rest_of_line;
    std::getline(iss, rest_of_line);
    std::cout << word << rest_of_line << "\n";


}
