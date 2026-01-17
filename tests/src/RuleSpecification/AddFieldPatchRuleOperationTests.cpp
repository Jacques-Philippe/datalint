#include <datalint/RuleSpecification/AddFieldRulePatchOperation.h>
#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint::fieldparser;

/// @brief Fixture for the current test suite
class AddFieldRulePatchOperationTests : public ::testing::Test {
 protected:
  /// @brief Helper to create a field rule with the incoming key. Defaults to IntegerInRangeRule and
  /// AllValuesSelector
  /// @param key the key the field rule should have
  /// @return the built field rule
  FieldRule MakeFieldRule(std::string key) {
    return FieldRule{key, std::make_unique<IntegerInRangeRule>(0, 10),
                     std::make_unique<AllValuesSelector>()};
  }
};

/// @brief test that we're able to add a field rule to a patch
TEST_F(AddFieldRulePatchOperationTests, AddsRuleToEmptyVector) {
  FieldRule rule = MakeFieldRule("key1");
  AddFieldRulePatchOperation patch(std::move(rule));

  std::vector<FieldRule> rules;
  patch.Apply(rules);

  ASSERT_EQ(rules.size(), 1);
  EXPECT_EQ(rules[0].FieldKey, "key1");
}

/// @brief Test that we're able to add a field rule to a set of existing rules
TEST_F(AddFieldRulePatchOperationTests, AddsRuleToExistingVector) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("existing"));

  FieldRule newRule = MakeFieldRule("key2");
  AddFieldRulePatchOperation patch(std::move(newRule));

  patch.Apply(rules);

  ASSERT_EQ(rules.size(), 2);
  EXPECT_EQ(rules[1].FieldKey, "key2");
}

/// @brief Test to make sure the clone function is working properly
TEST_F(AddFieldRulePatchOperationTests, ClonesRule) {
  FieldRule original = MakeFieldRule("key3");
  AddFieldRulePatchOperation patch(std::move(original));

  std::vector<FieldRule> rules;
  patch.Apply(rules);

  // Mutate the original rule
  original.FieldKey = "mutated";

  // Applied rule should not change
  ASSERT_EQ(rules.size(), 1);
  EXPECT_EQ(rules[0].FieldKey, "key3");
}
