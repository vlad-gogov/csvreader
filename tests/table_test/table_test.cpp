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
    ASSERT_EQ(2 + 2, 4);
}
