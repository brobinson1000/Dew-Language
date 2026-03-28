#pragma once

#include <sstream>
#include <variant>
#include <unordered_map>
#include <string>


using varType = std::variant<float ,double, int, std::string>;

// Process User Space
extern std::unordered_map<std::string, varType> variables;
extern std::unordered_map<std::string, varType*> heap;
extern std::unordered_map<std::string, varType> consts;

void displayCommand(std::istringstream& iss);

void display_floatCommand(std::istringstream& iss);

void display_newlineCommand(std::istringstream& iss);

void display_endlineCommand(std::istringstream& iss);
