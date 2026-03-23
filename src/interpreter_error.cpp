#include "interpreter_error.h"
#include <iostream>

void log(const std::string_view message, const std::source_location location) {
    std::cerr 
        << "\033[1;31m" 
        << "[ERROR] "
        << "\033[0m"
        << "\033[31m"
        << location.file_name() << '('
        << location.line() << ':'
        << location.column() << ") `"
        << location.function_name() << "`: "
        << message
        << "\033[0m"  
        << std::endl;
}
