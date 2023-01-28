#include "table.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>

#include "utils.hpp"

Table Table::fromLines(const std::vector<std::string> &lines) {
    if (lines.size() < 2u) {
        throw std::runtime_error("Table must have at least two rows including heading");
    }
    for (const auto &line : lines) {
        if (!isValidString(line)) {
            throw std::runtime_error("Invalid characters");
        }
    }
    Table table;
    table.setColumnNames(utils::splitString(lines.front(), ','));
    for (auto iter = std::next(lines.begin()); iter != lines.end(); ++iter) {
        const auto &rowLine = *iter;
        table.insertRow(utils::splitString(rowLine, ','));
    }
    return table;
}

Table Table::fromFile(const std::string_view &filename) {
    std::ifstream file(filename.data());
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.emplace_back(std::move(line));
    }
    return fromLines(lines);
}

void Table::calculate() {
    for (auto &[rowId, row] : data) {
        for (auto &cell : row) {
            calculateCell(cell);
        }
    }
}

void Table::print(std::ostream &stream) const {
    for (const auto &[columnName, columnIndex] : columns) {
        stream << ',' << columnName;
    }
    stream << '\n';
    for (auto &[rowId, row] : data) {
        stream << rowId;
        for (auto &cell : row) {
            stream << ',';
            if (cell.calculated()) {
                stream << std::get<Number>(cell.value);
            } else {
                stream << cell.raw;
            }
        }
        stream << '\n';
    }
}

Table::Cell::Cell(const std::string &rawValue) : raw(rawValue) {
    if (raw.front() == '=') {
        size_t opIndex = raw.find_first_of("+-*/");
        std::string leftStr = raw.substr(1u, opIndex);
        std::string rightStr = raw.substr(opIndex + 1u);
        Formula formula;
        formula.operation = raw[opIndex];
        if (utils::isInteger(leftStr)) {
            std::get<Number>(formula.left) = utils::parseInteger(leftStr);
        }
        if (utils::isInteger(rightStr)) {
            std::get<Number>(formula.right) = utils::parseInteger(rightStr);
        }
        std::get<Formula>(value) = formula;
        return;
    }
    if (!utils::isInteger(raw)) {
        throw std::runtime_error("Cell value is neither an integer not a formula");
    }
    std::get<Number>(value) = utils::parseInteger(raw);
}

bool Table::Cell::calculated() const {
    return std::holds_alternative<Number>(value);
}

Table::Address Table::Cell::extractAddress(const std::string &str) {
    size_t numberStart = str.length() - 1;
    for (; numberStart > 0; numberStart--) {
        if (!std::isdigit(str[numberStart])) {
            break;
        }
    }
    return Address(str.substr(0, numberStart), utils::parseInteger(str.substr(numberStart)));
}

void Table::setColumnNames(const std::vector<std::string> &names) {
    if (names.size() < 2u) {
        throw std::runtime_error("Table must have at least two columns");
    }
    constexpr const char *const UNALLOWED = "1234567890=+-*/";
    if (!names.front().empty()) {
        throw std::runtime_error("First column name must be empty");
    }
    columns.reserve(names.size() - 1u);
    size_t index = 0;
    for (auto iter = std::next(names.begin()); iter != names.end(); ++iter) {
        const auto &name = *iter;
        if (name.find_first_of(UNALLOWED) != std::string::npos) {
            throw std::runtime_error("Invalid characters in column names");
        }
        columns.emplace(name, index++);
    }
}

void Table::insertRow(const std::vector<std::string> &rowValues) {
    if (rowValues.size() < 2u) {
        throw std::runtime_error("Row must have at least two cells");
    }
    RowId rowId = 0;
    try {
        const std::string &idLiteral = rowValues.front();
        rowId = static_cast<RowId>(std::stoul(idLiteral));
    } catch (std::logic_error &e) {
        throw std::runtime_error(std::string("Cannot parse row id ") + e.what());
    }
    auto placement = data.emplace(rowId, Row{});
    if (!placement.second) {
        throw std::runtime_error("Each row must have unique id");
    }
    auto &row = (*placement.first).second;
    for (auto iter = std::next(rowValues.begin()); iter != rowValues.end(); ++iter) {
        const auto &rowValue = *iter;
        row.emplace_back(rowValue);
    }
}

void Table::calculateCell(Table::Cell &cell) {
    if (cell.calculated())
        return;
    const auto &formula = std::get<Formula>(cell.value);
    if (std::holds_alternative<Address>(formula.left)) {
        const auto &address = std::get<Address>(formula.left);
        size_t columnIndex = columns[address.first];
        auto &leftCell = data[address.second][columnIndex];
        calculateCell(leftCell);
    }
    Number leftValue = std::get<Number>(formula.left);
    if (std::holds_alternative<Address>(formula.right)) {
        const auto &address = std::get<Address>(formula.right);
        size_t columnIndex = columns[address.first];
        auto iter = data.find(address.second);
        if (iter == data.end()) {
            throw std::runtime_error("Invalid row id in address " + cell.raw);
        }
        auto &rightCell = iter->second[columnIndex];
        calculateCell(rightCell);
    }
    Number rightValue = std::get<Number>(formula.right);
    Number result = 0;
    switch (formula.operation) {
    case '+':
        result = leftValue + rightValue;
        break;
    case '-':
        result = leftValue - rightValue;
        break;
    case '*':
        result = leftValue * rightValue;
        break;
    case '/':
        if (rightValue == 0) {
            throw std::runtime_error("Cannot divide by zero");
        }
        result = leftValue / rightValue;
        break;
    }
    std::get<Number>(cell.value) = result;
}

bool Table::isValidString(const std::string &str) {
    constexpr const char *const ALLOWED = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890=+-*/,";
    return str.find_first_not_of(ALLOWED) == std::string::npos;
}
