#include "print.h"
#include <iostream>
#include <variant>
#include <unordered_map>
#include <string>
#include <iomanip>




const auto printVar = [](auto& var) {
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


const auto printStringNL = [](auto& var) {
    if (std::holds_alternative<std::string>(var)) { 
        std::cout << std::get<std::string>(var) << "\n";
        std::cout.flush();
    } 
    else {
        return;
    }
};

const auto printFloat = [](auto& var) {
    if (std::holds_alternative<float>(var)) {
        std::cout << std::get<float>(var);
    } else if (std::holds_alternative<int>(var)) {
        std::cout << std::fixed << std::setprecision(6) << static_cast<float>(std::get<int>(var));
    } else {
        std::cerr << "NOT A FLOAT\n";
    }
};



void displayCommand(std::istringstream& iss) {
    std::string word{};
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

    std::string rest_of_line{};
    std::getline(iss, rest_of_line);
    std::cout << word << rest_of_line;

}

void display_floatCommand(std::istringstream& iss) {
    std::string word{};
    iss >> word;

    auto it = heap.find(word);
    if(it != heap.end()) {
        printFloat(*(it->second));
        return;
    }

    auto it_ = variables.find(word);
    if ( it_ != variables.end()) {
        printFloat(it_->second);
        return;
    }

    float x = std::stof(word);
    std::cout << std::fixed << std::setprecision(6) << x;
    
};






void display_newlineCommand(std::istringstream& iss) {
    std::cout << "\n";
}

void display_endlineCommand(std::istringstream& iss) {
    std::string word{};
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
   
    std::ostringstream buffer;
    std::string rest_of_line{};
    std::getline(iss, rest_of_line);
    buffer << word << rest_of_line << "\n";
    std::cout << buffer.str();

}
