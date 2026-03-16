#pragma once

#include <sstream>
#include <variant>
#include <unordered_map>
#include <string>


using varType = std::variant<double, int, std::string>;

extern std::unordered_map<std::string, varType> variables;
extern std::unordered_map<std::string, varType*> heap;

void displayCommand(std::istringstream& iss);

void display_newlineCommand(std::istringstream& iss);

void display_endlineCommand(std::istringstream& iss);
