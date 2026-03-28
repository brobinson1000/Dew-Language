#pragma once
#include <sstream>
#include <string>
#include <variant>

using varType = std::variant<float, double, int ,std::string>;

void moveCommand(std::istringstream& iss);
void movehCommand(std::istringstream& iss);
void freehCommand(std::istringstream& iss);
void getCommand(std::istringstream& iss);
void sysCommand(std::istringstream& iss);
void timesleepCommand(std::istringstream& iss);

