#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

#include "table/table.hpp"

TEST(Table, can_calculate_with_formulas) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "1,1,0,1",
        "2,2,=A1+Cell30,0",
        "30,0,=B1+A1,5",
    });
    table.calculate();
    std::stringstream result;
    table.print(result);
    std::string answer = ",A,B,Cell\n"
                         "1,1,0,1\n"
                         "2,2,6,0\n"
                         "30,0,1,5\n";
    ASSERT_EQ(result.str(), answer);
}

TEST(Table, can_calculate_without_formulas) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "1,1,2,3",
        "2,4,5,6",
        "30,7,8,9",
    });
    table.calculate();
    std::stringstream result;
    table.print(result);
    std::string answer = ",A,B,Cell\n"
                         "1,1,2,3\n"
                         "2,4,5,6\n"
                         "30,7,8,9\n";
    ASSERT_EQ(result.str(), answer);
}

TEST(Table, can_calculate_with_complex_formulas) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "0,1,1,=A0+B0",
        "1,=Cell0+B0,=Cell0+A1,=A1+B1",
        "2,=B1+Cell1,=A2-Cell1,=A2*B2",
    });
    table.calculate();
    std::stringstream result;
    table.print(result);
    std::string answer = ",A,B,Cell\n"
                         "0,1,1,2\n"
                         "1,3,5,8\n"
                         "2,13,5,65\n";
    ASSERT_EQ(result.str(), answer);
}

TEST(Table, can_calculate_with_complex_formulas_deep) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "0,1,1,=A1+B0",
        "1,=B1+Cell1,=Cell1+A0,=A0+B0",
    });
    table.calculate();
    std::stringstream result;
    table.print(result);
    std::string answer = ",A,B,Cell\n"
                         "0,1,1,6\n"
                         "1,5,3,2\n";
    ASSERT_EQ(result.str(), answer);
}

TEST(Table, can_throw_exception_division_by_zero) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "0,1,0,=A0/B0",
    });
    ASSERT_THROW(table.calculate(), std::runtime_error);
}

TEST(Table, can_throw_exception_invalid_characters_in_column_name) {
    ASSERT_THROW(Table::fromLines({
                     ",A,B,Cell?",
                     "0,1,0,=A0*B0",
                 }),
                 std::runtime_error);
}

TEST(Table, can_throw_exception_invalid_characters_in_row_name) {
    ASSERT_THROW(Table::fromLines({
                     ",A,B,Cell",
                     "A0,1,0,=A0*B0",
                 }),
                 std::runtime_error);
}

TEST(Table, can_throw_exception_table_have_at_least_two_rows) {
    ASSERT_THROW(Table::fromLines({
                     ",A,B,Cell5",
                     "0,1,0,=A0*B0",
                 }),
                 std::runtime_error);
}

TEST(Table, can_throw_exception_table_have_at_least_two_columns) {
    ASSERT_THROW(Table::fromLines({
                     ",A",
                     "0",
                     "1",
                 }),
                 std::runtime_error);
}

TEST(Table, can_throw_exception_name_first_column_is_not_empty) {
    ASSERT_THROW(Table::fromLines({
                     "5,A,B,Cell?",
                     "0,1,0,=A0*B0",
                 }),
                 std::runtime_error);
}

TEST(Table, can_throw_exception_name_row_have_least_two_cells) {
    ASSERT_THROW(Table::fromLines({
                     ",A,B,Cell",
                     "0,",
                 }),
                 std::runtime_error);
}

TEST(Table, can_throw_exception_invalid_column_name_in_address) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "0,1,0,=D0*B0",
    });
    ASSERT_THROW(table.calculate(), std::runtime_error);
}

TEST(Table, can_throw_exception_invalid_row_name_in_address) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "0,1,0,=A1*B0",
    });
    ASSERT_THROW(table.calculate(), std::runtime_error);
}

TEST(Table, can_throw_exception_cell_is_not_integer) {
    ASSERT_THROW(Table::fromLines({
                     ",A,B,Cell",
                     "0,1,0,A",
                 }),
                 std::runtime_error);
}

TEST(Table, can_throw_exception_cell_is_not_formula) {
    ASSERT_THROW(Table::fromLines({
                     ",A,B,Cell",
                     "0,1,0,A1",
                 }),
                 std::runtime_error);
}

TEST(Table, can_throw_exception_cycle_1) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "0,1,=B0+A0,=A0+1",
    });
    ASSERT_THROW(table.calculate(), std::runtime_error);
}

TEST(Table, can_throw_exception_cycle_2) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "0,1,=Cell0+1,=B0+1",
    });
    ASSERT_THROW(table.calculate(), std::runtime_error);
}
