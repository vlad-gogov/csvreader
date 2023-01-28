#include <gtest/gtest.h>

#include <sstream>

#include "table/table.hpp"

TEST(Table, first) {
    auto table = Table::fromLines({
        ",A,B,Cell",
        "1,1,0,1",
        "2,2,=A1+Cell30,0",
        "30,0,=B1+A1,5",
    });
    table.calculate();
    std::stringstream result;
    table.print(result);
    std::string answer = ",A,Cell,B\n"
                         "1,1,0,1\n"
                         "2,2,6,0\n"
                         "30,0,1,5\n";
    ASSERT_EQ(result.str(), answer);
}
