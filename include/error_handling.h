#pragma once
#include <string_view>
#include <source_location>

void log(const std::string_view message, 
         const std::source_location location = std::source_location::current());
