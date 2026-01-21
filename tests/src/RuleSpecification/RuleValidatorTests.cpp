#include <datalint/Error/ErrorCollector.h>
#include <datalint/FieldParser/ParsedData.h>
#include <datalint/FieldParser/ParsedField.h>
#include <datalint/FieldParser/RawValue.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RuleSpecification.h>
#include <datalint/RuleSpecification/RuleValidator.h>
#include <datalint/RuleSpecification/ValueAtIndexSelector.h>
#include <gtest/gtest.h>

#include <memory>
#include <vector>

using namespace datalint::rules;
using namespace datalint::fieldparser;
using namespace datalint::error;

/// @brief Fixture to test Rule Validator
class RuleValidatorTest : public ::testing::Test {
 protected:
  /// @brief the rule validator instance
  RuleValidator validator_;
};

/// @brief Test that an empty rule specification can pass successfully
TEST_F(RuleValidatorTest, EmptyRuleSpecificationPasses) {
  RuleSpecification spec({});
  ParsedData data({});
  ErrorCollector collector;

  EXPECT_TRUE(validator_.Validate(spec, data, collector));
  EXPECT_EQ(collector.GetErrorLogs().size(), 0);
}

/// @brief Test that a valid rule passes successfully
TEST_F(RuleValidatorTest, ValidRulePasses) {
  // Create a field with value "5" at index 0
  ParsedField field{"key10", {RawValue{"5", {}}}};
  ParsedData data({field});

  // Rule: key10 must be integer between 0 and 10, check index 0
  FieldRule rule{"key10", std::make_unique<IntegerInRangeRule>(0, 10),
                 std::make_unique<ValueAtIndexSelector>(0)};
  std::vector<FieldRule> rules;
  rules.push_back(std::move(rule));
  RuleSpecification spec(std::move(rules));

  ErrorCollector collector;

  EXPECT_TRUE(validator_.Validate(spec, data, collector));
  EXPECT_EQ(collector.GetErrorLogs().size(), 0);
}

/// @brief Test that an invalid rule fails
TEST_F(RuleValidatorTest, InvalidRuleFails) {
  // Create a field with value "15" at index 0
  ParsedField field{"key10", {RawValue{"15", {}}}};
  ParsedData data({field});

  // Rule: key10 must be integer between 0 and 10, check index 0
  FieldRule rule{"key10", std::make_unique<IntegerInRangeRule>(0, 10),
                 std::make_unique<ValueAtIndexSelector>(0)};
  std::vector<FieldRule> rules;
  rules.push_back(std::move(rule));
  RuleSpecification spec(std::move(rules));

  ErrorCollector collector;

  EXPECT_FALSE(validator_.Validate(spec, data, collector));
  EXPECT_EQ(collector.GetErrorLogs().size(), 1);
  EXPECT_EQ(collector.GetErrorLogs()[0].Subject(), "Incorrect value");
}

/// @brief Test that a rule for a missing field results in an error
TEST_F(RuleValidatorTest, MissingFieldFails) {
  // Data has no "key10" field
  ParsedData data({});

  // Rule expects "key10"
  FieldRule rule{"key10", std::make_unique<IntegerInRangeRule>(0, 10),
                 std::make_unique<ValueAtIndexSelector>(0)};

  std::vector<FieldRule> rules;
  rules.push_back(std::move(rule));
  RuleSpecification spec(std::move(rules));

  ErrorCollector collector;

  EXPECT_FALSE(validator_.Validate(spec, data, collector));
  EXPECT_EQ(collector.GetErrorLogs().size(), 1);
  EXPECT_EQ(collector.GetErrorLogs()[0].Subject(), "Missing required field");
  EXPECT_EQ(collector.GetErrorLogs()[0].Body(), "key10");
}

/// @brief Tests a failure with an integer in range rule checking against a non-integer
TEST_F(RuleValidatorTest, NonIntegerValueFails) {
  // Create a field with non-integer value
  ParsedField field{"key10", {RawValue{"notanumber", {}}}};
  ParsedData data({field});

  FieldRule rule{"key10", std::make_unique<IntegerInRangeRule>(0, 10),
                 std::make_unique<ValueAtIndexSelector>(0)};
  std::vector<FieldRule> rules;
  rules.push_back(std::move(rule));
  RuleSpecification spec(std::move(rules));

  ErrorCollector collector;

  EXPECT_FALSE(validator_.Validate(spec, data, collector));
  EXPECT_EQ(collector.GetErrorLogs().size(), 1);
  EXPECT_EQ(collector.GetErrorLogs()[0].Subject(), "Incorrect value type");
}

/// @brief Tests that we're able to define multiple rules and that if one fails it's handled as
/// expected
TEST_F(RuleValidatorTest, MultipleRulesOneFails) {
  ParsedField field1{"key10", {RawValue{"5", {}}}};
  ParsedField field2{"key11", {RawValue{"20", {}}}};
  ParsedData data({field1, field2});

  FieldRule rule1{"key10", std::make_unique<IntegerInRangeRule>(0, 10),
                  std::make_unique<ValueAtIndexSelector>(0)};
  FieldRule rule2{"key11", std::make_unique<IntegerInRangeRule>(0, 10),
                  std::make_unique<ValueAtIndexSelector>(0)};

  std::vector<FieldRule> rules;
  rules.push_back(std::move(rule1));
  rules.push_back(std::move(rule2));
  RuleSpecification spec(std::move(rules));

  ErrorCollector collector;

  EXPECT_FALSE(validator_.Validate(spec, data, collector));
  EXPECT_EQ(collector.GetErrorLogs().size(), 1);  // Only one error for key11
}
