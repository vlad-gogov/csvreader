#include "utils.hpp"

#include <algorithm>
#include <stdexcept>

std::vector<std::string> utils::splitString(const std::string &str, char delimiter) {
    if (str.empty()) {
        return {std::string()};
    }
    std::vector<std::string> tokens;
    auto tokenBegin = str.begin();
    auto tokenEnd = std::next(tokenBegin);
    while (tokenBegin != str.end()) {
        while (tokenEnd != str.end() && *tokenEnd != delimiter)
            ++tokenEnd;
        tokens.emplace_back(tokenBegin, tokenEnd);
        if (tokenEnd != str.end())
            ++tokenEnd;
        tokenBegin = tokenEnd;
    }
    return tokens;
}

Number utils::parseInteger(const std::string &str) {
    Number value = 0;
    try {
        value = std::stoll(str);
    } catch (std::logic_error &e) {
        throw std::runtime_error("Cannot parse numeric value in cell: " + str);
    }
    return value;
}

bool utils::isInteger(const std::string &str) {
    return std::all_of(str.begin(), str.end(), std::isdigit);
}
