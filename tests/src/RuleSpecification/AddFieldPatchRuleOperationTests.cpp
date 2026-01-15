#include <datalint/RuleSpecification/AddFieldRulePatchOperation.h>
#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint::fieldparser;

class AddFieldRulePatchOperationTests : public ::testing::Test {
 protected:
  // Helper to create a simple FieldRule
  FieldRule MakeFieldRule(std::string key) {
    return FieldRule{key, std::make_unique<IntegerInRangeRule>(0, 10),
                     std::make_unique<AllValuesSelector>()};
  }
};

TEST_F(AddFieldRulePatchOperationTests, AddsRuleToEmptyVector) {
  FieldRule rule = MakeFieldRule("key1");
  AddFieldRulePatchOperation patch(std::move(rule));

  std::vector<FieldRule> rules;
  patch.Apply(rules);

  ASSERT_EQ(rules.size(), 1);
  EXPECT_EQ(rules[0].FieldKey, "key1");
}

TEST_F(AddFieldRulePatchOperationTests, AddsRuleToExistingVector) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("existing"));

  FieldRule newRule = MakeFieldRule("key2");
  AddFieldRulePatchOperation patch(std::move(newRule));

  patch.Apply(rules);

  ASSERT_EQ(rules.size(), 2);
  EXPECT_EQ(rules[1].FieldKey, "key2");
}

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
