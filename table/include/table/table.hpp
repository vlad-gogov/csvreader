#pragma once

#include <algorithm>
#include <ostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

class Table {
  public:
    Table(const Table &) = default;
    Table(Table &&) = default;
    ~Table() = default;

    Table &operator=(const Table &) = default;
    Table &operator=(Table &&) = default;

    static Table fromLines(const std::vector<std::string> &lines);
    static Table fromFile(const std::string_view &filename);

    void calculate();
    void print(std::ostream &stream) const;

  private:
    using RowId = std::uint64_t;
    using ColumnId = std::string;
    using Address = std::pair<ColumnId, RowId>;

    struct Formula {
        char operation;
        std::variant<std::int64_t, Address> left;
        std::variant<std::int64_t, Address> right;
    };

    struct Cell {
        std::variant<std::int64_t, Formula> value;
        std::string raw;

        explicit Cell(const std::string &rawValue);
        ~Cell() = default;

        bool calculated() const;

        static Address extractAddress(const std::string &str);
    };

    using Row = std::vector<Cell>;

    Table() = default;

    void setColumnNames(const std::vector<std::string> &names);
    void insertRow(const std::vector<std::string> &rowValues);
    std::int64_t valueByAddress(const std::variant<std::int64_t, Address> &cellAddress);
    void calculateCell(Cell &cell);

    static bool isValidString(const std::string &str);

    std::unordered_map<ColumnId, size_t> columns;
    std::unordered_map<RowId, Row> data;
};
