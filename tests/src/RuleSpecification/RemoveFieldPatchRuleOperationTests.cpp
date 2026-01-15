#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RemoveFieldRulePatchOperation.h>
#include <datalint/RuleSpecification/ValueAtIndexSelector.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint::fieldparser;

class RemoveFieldRulePatchOperationTests : public ::testing::Test {
 protected:
  // Helper to create a simple FieldRule
  FieldRule MakeFieldRule(std::string key) {
    return FieldRule{key, std::make_unique<IntegerInRangeRule>(0, 10),
                     std::make_unique<AllValuesSelector>()};
  }

  FieldRule MakeFieldRule(std::string key, std::unique_ptr<IValueRule> rule,
                          std::unique_ptr<IValueSelector> selector) {
    return FieldRule{key, std::move(rule), std::move(selector)};
  }
};

TEST_F(RemoveFieldRulePatchOperationTests, RemovesRuleByKey) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("key1"));
  rules.push_back(MakeFieldRule("key2"));

  RemoveFieldRulePatchOperation patch([](const FieldRule& r) { return r.FieldKey == "key1"; });

  patch.Apply(rules);

  ASSERT_EQ(rules.size(), 1);
  EXPECT_EQ(rules[0].FieldKey, "key2");
}

TEST_F(RemoveFieldRulePatchOperationTests, RemovesMultipleMatchingRules) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("remove"));
  rules.push_back(MakeFieldRule("keep"));
  rules.push_back(MakeFieldRule("remove"));

  RemoveFieldRulePatchOperation patch([](const FieldRule& r) { return r.FieldKey == "remove"; });

  patch.Apply(rules);

  ASSERT_EQ(rules.size(), 1);
  EXPECT_EQ(rules[0].FieldKey, "keep");
}

TEST_F(RemoveFieldRulePatchOperationTests, NoMatchingRulesLeavesVectorUnchanged) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("key1"));
  rules.push_back(MakeFieldRule("key2"));

  RemoveFieldRulePatchOperation patch(
      [](const FieldRule& r) { return r.FieldKey == "nonexistent"; });

  patch.Apply(rules);

  ASSERT_EQ(rules.size(), 2);
  EXPECT_EQ(rules[0].FieldKey, "key1");
  EXPECT_EQ(rules[1].FieldKey, "key2");
}

TEST_F(RemoveFieldRulePatchOperationTests, EmptyVector) {
  std::vector<FieldRule> rules;

  RemoveFieldRulePatchOperation patch([](const FieldRule& r) { return true; });

  patch.Apply(rules);

  EXPECT_TRUE(rules.empty());
}

TEST_F(RemoveFieldRulePatchOperationTests, RemoveRuleByValueRuleType) {
  std::vector<FieldRule> rules;

  // Add rules with different value rules
  rules.push_back(MakeFieldRule("key1", std::make_unique<IntegerInRangeRule>(0, 10),
                                std::make_unique<AllValuesSelector>()));

  rules.push_back(MakeFieldRule("key2", std::make_unique<IntegerInRangeRule>(5, 15),
                                std::make_unique<AllValuesSelector>()));

  rules.push_back(MakeFieldRule("key3", std::make_unique<IntegerInRangeRule>(1, 5),
                                std::make_unique<ValueAtIndexSelector>(0)));

  RemoveFieldRulePatchOperation patch([](const FieldRule& r) {
    // Remove rules whose ValueRule is IntegerInRangeRule
    return dynamic_cast<IntegerInRangeRule*>(r.ValueRule.get()) != nullptr;
  });

  patch.Apply(rules);

  EXPECT_TRUE(rules.empty());  // all rules were IntegerInRangeRule
}

TEST_F(RemoveFieldRulePatchOperationTests, RemoveRuleBySelectorType) {
  std::vector<FieldRule> rules;

  // Add rules with different value rules
  rules.push_back(MakeFieldRule("key1", std::make_unique<IntegerInRangeRule>(0, 10),
                                std::make_unique<AllValuesSelector>()));

  rules.push_back(MakeFieldRule("key2", std::make_unique<IntegerInRangeRule>(5, 15),
                                std::make_unique<AllValuesSelector>()));

  rules.push_back(MakeFieldRule("key3", std::make_unique<IntegerInRangeRule>(1, 5),
                                std::make_unique<ValueAtIndexSelector>(0)));

  RemoveFieldRulePatchOperation patch([](const FieldRule& r) {
    // Remove rules whose selector is AllValuesSelector
    return dynamic_cast<AllValuesSelector*>(r.ValueSelector.get()) != nullptr;
  });

  patch.Apply(rules);

  EXPECT_EQ(rules.size(), 1);  // all but one rule were AllValuesSelector
}
