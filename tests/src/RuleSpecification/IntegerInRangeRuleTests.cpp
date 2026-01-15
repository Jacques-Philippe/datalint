#include <datalint/Error/ErrorCollector.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RuleContext.h>
#include <gtest/gtest.h>

using namespace datalint::rules;

class IntegerInRangeRuleTests : public ::testing::Test {
 protected:
  datalint::error::ErrorCollector errorCollector;

  datalint::fieldparser::ParsedField field;
  datalint::fieldparser::RawValue value;

  RuleContext MakeContext(std::string_view text) {
    field.Key = "TestKey";
    field.Values.clear();

    value.Value = text;
    value.Location = {"file.txt", 1};

    return RuleContext{field, value};
  }
};

TEST_F(IntegerInRangeRuleTests, AcceptsIntegerWithinRange) {
  IntegerInRangeRule rule(1, 10);
  auto ctx = MakeContext("5");

  rule.Evaluate(ctx, errorCollector);

  EXPECT_FALSE(errorCollector.HasErrors());
}

TEST_F(IntegerInRangeRuleTests, RejectsNonIntegerValue) {
  IntegerInRangeRule rule(1, 10);
  auto ctx = MakeContext("abc");

  rule.Evaluate(ctx, errorCollector);

  ASSERT_TRUE(errorCollector.HasErrors());
  const auto& error = errorCollector.GetErrorLogs().front();
  EXPECT_EQ(error.Subject(), "Incorrect value type");
}

TEST_F(IntegerInRangeRuleTests, RejectsIntegerBelowRange) {
  IntegerInRangeRule rule(10, 20);
  auto ctx = MakeContext("5");

  rule.Evaluate(ctx, errorCollector);

  ASSERT_TRUE(errorCollector.HasErrors());

  const auto& error = errorCollector.GetErrorLogs().front();
  EXPECT_EQ(error.Subject(), "Incorrect value");
  EXPECT_EQ(error.Body(), "Value must be between 10 and 20");
}

TEST_F(IntegerInRangeRuleTests, RejectsIntegerAboveRange) {
  IntegerInRangeRule rule(10, 20);
  auto ctx = MakeContext("25");

  rule.Evaluate(ctx, errorCollector);

  ASSERT_TRUE(errorCollector.HasErrors());

  const auto& error = errorCollector.GetErrorLogs().front();
  EXPECT_EQ(error.Subject(), "Incorrect value");
  EXPECT_EQ(error.Body(), "Value must be between 10 and 20");
}

TEST_F(IntegerInRangeRuleTests, AcceptsBoundaryValues) {
  IntegerInRangeRule rule(10, 20);

  rule.Evaluate(MakeContext("10"), errorCollector);
  rule.Evaluate(MakeContext("20"), errorCollector);

  EXPECT_FALSE(errorCollector.HasErrors());
}
