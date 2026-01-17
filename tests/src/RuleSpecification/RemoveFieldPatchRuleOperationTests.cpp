#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RemoveFieldRulePatchOperation.h>
#include <datalint/RuleSpecification/ValueAtIndexSelector.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint::fieldparser;

/// @brief Fixture for remove field rule patch tests
class RemoveFieldRulePatchOperationTests : public ::testing::Test {
 protected:
  /// @brief Helper to create a field rule instance with default rule Integer in range and default
  /// selector All values
  /// @param key the key associated to the field rule
  /// @return the constructed field rule
  FieldRule MakeFieldRule(std::string key) {
    return FieldRule{key, std::make_unique<IntegerInRangeRule>(0, 10),
                     std::make_unique<AllValuesSelector>()};
  }

  /// @brief Helper to create a field rule instance
  /// @param key the key associated to the field rule
  /// @param rule the field rule's rule
  /// @param selector the field rule's selector
  /// @return the constructed field rule
  FieldRule MakeFieldRule(std::string key, std::unique_ptr<IValueRule> rule,
                          std::unique_ptr<IValueSelector> selector) {
    return FieldRule{key, std::move(rule), std::move(selector)};
  }
};

/// @brief Test that we're able to remove any field rule by the field rule's key
TEST_F(RemoveFieldRulePatchOperationTests, RemovesRuleByKey) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("key1"));
  rules.push_back(MakeFieldRule("key2"));

  RemoveFieldRulePatchOperation patch([](const FieldRule& r) { return r.FieldKey == "key1"; });

  patch.Apply(rules);

  ASSERT_EQ(rules.size(), 1);
  EXPECT_EQ(rules[0].FieldKey, "key2");
}

/// @brief Test that we're able to remove multiple instances of any field rule matching the criteria
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

/// @brief Test that given no field rules match the criteria, there's no change to the rules vector
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

/// @brief Test that even if the rules vector is empty the patch operation doesn't throw
TEST_F(RemoveFieldRulePatchOperationTests, EmptyVector) {
  std::vector<FieldRule> rules;

  RemoveFieldRulePatchOperation patch([](const FieldRule& r) { return true; });

  patch.Apply(rules);

  EXPECT_TRUE(rules.empty());
}

/// @brief Test that we're able to remove a field rule by value rule type as criteria
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

/// @brief Test that we're able to remove a field rule by selector type as criteria
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
