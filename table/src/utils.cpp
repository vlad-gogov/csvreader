#include "utils.hpp"

#include <algorithm>
#include <stdexcept>

std::vector<std::string> utils::splitString(const std::string &str, char delimiter) {
    if (str.empty()) {
        return {""};
    }
    std::vector<std::string> tokens;
    auto tokenBegin = str.begin();
    auto tokenEnd = tokenBegin;
    while (tokenBegin != str.end()) {
        while (tokenEnd != str.end() && *tokenEnd != delimiter)
            ++tokenEnd;
        tokens.emplace_back(tokenBegin, tokenEnd);
        if (tokenEnd != str.end())
            ++tokenEnd;
        tokenBegin = tokenEnd;
    }
    if (str.back() == delimiter)
        tokens.emplace_back();
    return tokens;
}

std::int64_t utils::parseInteger(const std::string &str) {
    std::int64_t value = 0;
    try {
        value = std::stoll(str);
    } catch (std::logic_error &e) {
        throw std::runtime_error("Cannot parse numeric value in cell: " + str);
    }
    return value;
}

bool utils::isInteger(const std::string &str) {
    if (str.empty())
        return false;
    auto first = str.front();
    if (first != '-' && first != '+' && !std::isdigit(first))
        return false;
    return std::all_of(std::next(str.begin()), str.end(), [](const char &ch) { return std::isdigit(ch); });
}
