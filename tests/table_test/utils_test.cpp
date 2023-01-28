#include <gtest/gtest.h>

#include <sstream>

#include "table/utils.hpp"

TEST(Utils, can_split_empty_string) {
    auto delimiter = ',';
    std::stringstream str;
    str << "";
    std::vector<std::string> answer = {""};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_empty_strings) {
    auto delimiter = ',';
    std::stringstream str;
    str << delimiter << delimiter << delimiter;
    std::vector<std::string> answer = {"", "", "", ""};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_string_1) {
    auto delimiter = ',';
    std::stringstream str;
    str << " " << delimiter << "A" << delimiter << "B" << delimiter << "Cell";
    std::vector<std::string> answer = {" ", "A", "B", "Cell"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_string_2) {
    auto delimiter = ' ';
    std::stringstream str;
    str << " " << delimiter << "A" << delimiter << "B" << delimiter << "Cell";
    std::vector<std::string> answer = {" ", "A", "B", "Cell"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_string_3) {
    auto delimiter = '+';
    std::stringstream str;
    str << " " << delimiter << "A" << delimiter << "B" << delimiter << "Cell";
    std::vector<std::string> answer = {" ", "A", "B", "Cell"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_string_4) {
    auto delimiter = ',';
    std::stringstream str;
    str << "2" << delimiter << "2" << delimiter << "=A1+Cell30" << delimiter << "0";
    std::vector<std::string> answer = {"2", "2", "=A1+Cell30", "0"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_string_5) {
    auto delimiter = ',';
    std::stringstream str;
    str << "2" << delimiter << delimiter << "=A1+Cell30" << delimiter << delimiter << "0";
    std::vector<std::string> answer = {"2", "", "=A1+Cell30", "", "0"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}
