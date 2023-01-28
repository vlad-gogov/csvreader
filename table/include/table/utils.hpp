#pragma once

#include <string>
#include <vector>

using Number = std::int64_t;

namespace utils {
std::vector<std::string> splitString(const std::string &str, char delimiter);
Number parseInteger(const std::string &str);
bool isInteger(const std::string &str);
} // namespace utils
