#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RuleSpecification.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint;

FieldRule MakeFieldRule(const std::string& key) {
  return FieldRule{key, std::make_unique<IntegerInRangeRule>(0, 10),
                   std::make_unique<AllValuesSelector>()};
}

TEST(RuleSpecificationTest, StoresRules) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("key1"));
  rules.push_back(MakeFieldRule("key2"));

  RuleSpecification spec(std::move(rules));

  ASSERT_EQ(spec.Rules().size(), 2);
  EXPECT_EQ(spec.Rules()[0].FieldKey, "key1");
  EXPECT_EQ(spec.Rules()[1].FieldKey, "key2");
}

TEST(RuleSpecificationTests, SupportsEmptyRules) {
  std::vector<FieldRule> rules;

  RuleSpecification spec(std::move(rules));

  EXPECT_TRUE(spec.Rules().empty());
}

TEST(RuleSpecificationTests, TakesOwnershipOfRules) {
  std::vector<FieldRule> rules;
  rules.push_back(MakeFieldRule("key"));

  RuleSpecification spec(std::move(rules));

  // Moved-from vector should be empty or in valid but unspecified state
  EXPECT_TRUE(rules.empty() || rules.size() == 0);

  ASSERT_EQ(spec.Rules().size(), 1);
  EXPECT_EQ(spec.Rules()[0].FieldKey, "key");
}
