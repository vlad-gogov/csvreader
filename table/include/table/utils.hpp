#pragma once

#include <string>
#include <vector>

namespace utils {
std::vector<std::string> splitString(const std::string &str, char delimiter);
std::int64_t parseInteger(const std::string &str);
bool isInteger(const std::string &str);
} // namespace utils
