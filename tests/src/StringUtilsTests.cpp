#include <datalint/StringUtils.h>
#include <gtest/gtest.h>

using namespace datalint::utils;

/// @brief Test some cases where we expect the parsing to succeed
TEST(TryParseIntTests, ParsesValidIntegers) {
  int value = 0;

  EXPECT_TRUE(TryParseInt("0", value));
  EXPECT_EQ(value, 0);

  EXPECT_TRUE(TryParseInt("42", value));
  EXPECT_EQ(value, 42);

  EXPECT_TRUE(TryParseInt("-17", value));
  EXPECT_EQ(value, -17);

  EXPECT_TRUE(TryParseInt("2147483647", value));  // INT_MAX
  EXPECT_EQ(value, 2147483647);

  EXPECT_TRUE(TryParseInt("-2147483648", value));  // INT_MIN
  EXPECT_EQ(value, -2147483648);
}

/// @brief Test some cases where we expect parsing to fail
TEST(TryParseIntTests, RejectsInvalidInput) {
  int value = 123;  // sentinel

  EXPECT_FALSE(TryParseInt("", value));
  EXPECT_EQ(value, 123) << "Value should be unchanged as a result of the failed parse operation";
  EXPECT_FALSE(TryParseInt(" ", value));
  EXPECT_FALSE(TryParseInt("abc", value));
  EXPECT_FALSE(TryParseInt("12abc", value));
  EXPECT_FALSE(TryParseInt("1.5", value));
  EXPECT_FALSE(TryParseInt("+", value));
  EXPECT_FALSE(TryParseInt("-", value));
}

/// @brief Test int limit edge cases
TEST(TryParseIntTests, RejectsOverflow) {
  int value = 0;

  EXPECT_FALSE(TryParseInt("2147483648", value));   // INT_MAX + 1
  EXPECT_FALSE(TryParseInt("-2147483649", value));  // INT_MIN - 1
}

/// @brief Make sure whitespace causes test to fail, trimming should come from outside the util
TEST(TryParseIntTests, RejectsWhitespace) {
  int value = 0;

  EXPECT_FALSE(TryParseInt(" 42", value));
  EXPECT_FALSE(TryParseInt("42 ", value));
  EXPECT_FALSE(TryParseInt("\t42", value));
  EXPECT_FALSE(TryParseInt("42\n", value));
}

/// @brief Make sure we have stringview correctness
TEST(TryParseIntTests, WorksWithStringViewSubstrings) {
  std::string input = "value=123";
  std::string_view sv(input.data() + 6, 3);

  int value = 0;
  EXPECT_TRUE(TryParseInt(sv, value));
  EXPECT_EQ(value, 123);
}
