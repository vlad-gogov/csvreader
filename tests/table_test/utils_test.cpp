#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

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

TEST(Utils, can_split_string_comma) {
    auto delimiter = ',';
    std::stringstream str;
    str << " " << delimiter << "A" << delimiter << "B" << delimiter << "Cell";
    std::vector<std::string> answer = {" ", "A", "B", "Cell"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_string_hyphen) {
    auto delimiter = '-';
    std::stringstream str;
    str << " " << delimiter << "A" << delimiter << "B" << delimiter << "Cell";
    std::vector<std::string> answer = {" ", "A", "B", "Cell"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_string_with_expression) {
    auto delimiter = ',';
    std::stringstream str;
    str << "2" << delimiter << "2" << delimiter << "=A1+Cell30" << delimiter << "0";
    std::vector<std::string> answer = {"2", "2", "=A1+Cell30", "0"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_split_string_with_empty_parts) {
    auto delimiter = ',';
    std::stringstream str;
    str << "2" << delimiter << delimiter << "=A1+Cell30" << delimiter << delimiter << "A2345";
    std::vector<std::string> answer = {"2", "", "=A1+Cell30", "", "A2345"};
    auto result = utils::splitString(str.str(), delimiter);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_parse_positive_integer) {
    std::string str = "123456";
    std::int64_t answer = 123456;
    auto result = utils::parseInteger(str);
    ASSERT_EQ(answer, result);
}

TEST(Utils, can_parse_negative_integer) {
    std::string str = "-123456";
    std::int64_t answer = -123456;
    auto result = utils::parseInteger(str);
    ASSERT_EQ(answer, result);
}

TEST(Utils, cannot_parse_erroneous_integer) {
    std::string str = "A2";
    ASSERT_THROW(utils::parseInteger(str), std::runtime_error);
}

TEST(Utils, can_check_is_integer_for_positive_integer) {
    std::string str = "5789";
    ASSERT_TRUE(utils::isInteger(str));
}

TEST(Utils, can_check_is_integer_for_positive_integer_with_plus) {
    std::string str = "+5789";
    ASSERT_TRUE(utils::isInteger(str));
}

TEST(Utils, can_check_is_integer_for_negative_integer) {
    std::string str = "-5789";
    ASSERT_TRUE(utils::isInteger(str));
}

TEST(Utils, can_check_is_integer_for_erroneous_integer) {
    std::string str = "57A89";
    ASSERT_FALSE(utils::isInteger(str));
}
