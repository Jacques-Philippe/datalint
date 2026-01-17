#include <datalint/Error/ErrorCollector.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RuleContext.h>
#include <gtest/gtest.h>

using namespace datalint::rules;

/// @brief Fixture for the integer in range rule tests
class IntegerInRangeRuleTests : public ::testing::Test {
 protected:
  /// @brief Reference to the error collector
  datalint::error::ErrorCollector errorCollector;
  /// @brief the parsed field of the rule context
  datalint::fieldparser::ParsedField field;
  /// @brief the raw value of the rule context
  datalint::fieldparser::RawValue value;

  /// @brief Helper to create a rule context instance made up of the parsed field and raw value
  /// @param text the text used as the key of the parsed field
  /// @return the rule context containing the
  RuleContext MakeContext(std::string_view text) {
    field.Key = "TestKey";
    field.Values.clear();

    value.Value = text;
    value.Location = {"file.txt", 1};

    return RuleContext{field, value};
  }
};

/// @brief Test that given an integer in range rule and a rule context made up of an integer in that
/// range, the rule evaluates successfully and no errors are collected
TEST_F(IntegerInRangeRuleTests, AcceptsIntegerWithinRange) {
  IntegerInRangeRule rule(1, 10);
  auto ctx = MakeContext("5");

  rule.Evaluate(ctx, errorCollector);

  EXPECT_FALSE(errorCollector.HasErrors());
}

/// @brief Test that given an integer in range rule and a rule context made up of a non-integer
/// value, errors are collected about the value type
TEST_F(IntegerInRangeRuleTests, RejectsNonIntegerValue) {
  IntegerInRangeRule rule(1, 10);
  auto ctx = MakeContext("abc");

  rule.Evaluate(ctx, errorCollector);

  ASSERT_TRUE(errorCollector.HasErrors());
  const auto& error = errorCollector.GetErrorLogs().front();
  EXPECT_EQ(error.Subject(), "Incorrect value type");
}

/// @brief Test that given an integer in range rule and a rule context made up of an integer value
/// below the acceptable range, an error is collected about the value correctness
TEST_F(IntegerInRangeRuleTests, RejectsIntegerBelowRange) {
  IntegerInRangeRule rule(10, 20);
  auto ctx = MakeContext("5");

  rule.Evaluate(ctx, errorCollector);

  ASSERT_TRUE(errorCollector.HasErrors());

  const auto& error = errorCollector.GetErrorLogs().front();
  EXPECT_EQ(error.Subject(), "Incorrect value");
  EXPECT_EQ(error.Body(), "Value must be between 10 and 20");
}

/// @brief Test that given an integer in range rule and a rule context made up of an integer value
/// above the acceptable range, an error is collected about the value correctness
TEST_F(IntegerInRangeRuleTests, RejectsIntegerAboveRange) {
  IntegerInRangeRule rule(10, 20);
  auto ctx = MakeContext("25");

  rule.Evaluate(ctx, errorCollector);

  ASSERT_TRUE(errorCollector.HasErrors());

  const auto& error = errorCollector.GetErrorLogs().front();
  EXPECT_EQ(error.Subject(), "Incorrect value");
  EXPECT_EQ(error.Body(), "Value must be between 10 and 20");
}

/// @brief Test that given an integer in range rule and a rule context made up of an integer value
/// on the minimum and maximum thresholds, no errors are generated
TEST_F(IntegerInRangeRuleTests, AcceptsBoundaryValues) {
  IntegerInRangeRule rule(10, 20);

  rule.Evaluate(MakeContext("10"), errorCollector);
  EXPECT_FALSE(errorCollector.HasErrors()) << "Min boundary (10) should be accepted";

  // make sure we reset error collector
  errorCollector = datalint::error::ErrorCollector{};

  rule.Evaluate(MakeContext("20"), errorCollector);
  EXPECT_FALSE(errorCollector.HasErrors()) << "Max boundary (20) should be accepted";
}
