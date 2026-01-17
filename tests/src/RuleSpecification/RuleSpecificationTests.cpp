#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RuleSpecification.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint;

/// @brief Helper to construct an example field rule. The field rule defaults to Integer in range
/// rule and All values selector
/// @param key the key to associate to the field rule
/// @return the constructed field rule
FieldRule MakeFieldRule(const std::string& key) {
  return FieldRule{key, std::make_unique<IntegerInRangeRule>(0, 10),
                   std::make_unique<AllValuesSelector>()};
}

/// @brief Test that the rule specification can be built from a list of field rules
TEST(RuleSpecificationTest, StoresRules) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("key1"));
  rules.push_back(MakeFieldRule("key2"));

  RuleSpecification spec(std::move(rules));

  ASSERT_EQ(spec.Rules().size(), 2);
  EXPECT_EQ(spec.Rules()[0].FieldKey, "key1");
  EXPECT_EQ(spec.Rules()[1].FieldKey, "key2");
}

/// @brief Test that the rule specification can be built from a list of empty field rules
TEST(RuleSpecificationTests, SupportsEmptyRules) {
  std::vector<FieldRule> rules;

  RuleSpecification spec(std::move(rules));

  EXPECT_TRUE(spec.Rules().empty());
}

/// @brief Test that the rule specification takes ownership of the rules once they're used to build
/// the rule specification
TEST(RuleSpecificationTests, TakesOwnershipOfRules) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("key"));

  RuleSpecification spec(std::move(rules));

  // Moved-from vector should be empty or in valid but unspecified state
  EXPECT_TRUE(rules.empty() || rules.size() == 0);

  ASSERT_EQ(spec.Rules().size(), 1);
  EXPECT_EQ(spec.Rules()[0].FieldKey, "key");
}
