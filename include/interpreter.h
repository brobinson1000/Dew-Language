#pragma once
#include <sstream>
#include <string>
#include <variant>

using varType = std::variant<int, float, std::string>;

void displayFloor(std::istringstream& iss);
varType floorFunc(std::stringstream& iss);
void displayCeil(std::istringstream& iss);
varType ceilFunc(std::istringstream& iss);
varType piFunc(std::istringstream& iss);
void moveCommand(std::istringstream& iss);
void movehCommand(std::istringstream& iss);
void freehCommand(std::istringstream& iss);
void getCommand(std::istringstream& iss);
void sysCommand(std::istringstream& iss);
void timesleepCommand(std::istringstream& iss);

