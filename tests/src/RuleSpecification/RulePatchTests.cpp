#include <datalint/RuleSpecification/AddFieldRulePatchOperation.h>
#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/IRulePatchOperation.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RulePatch.h>
#include <datalint/Version/VersionRange.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint;

/// @brief Fixture for rule patch tests
class RulePatchTests : public ::testing::Test {
 protected:
  /// @brief the list of rules
  std::vector<FieldRule> rules_;  // empty is fine for most tests
};

/// @brief Fake concrete implementation of IRulePatchOperation so we can measure the calls to the
/// Apply function
class FakeRulePatchOperation : public IRulePatchOperation {
 public:
  /// @brief Constructor
  /// @param callCount the number of times the Apply function was called
  explicit FakeRulePatchOperation(int& callCount) : callCount_(callCount) {}

  /// @brief Concrete implementation of the Apply function
  /// @param rules the rules to modify
  void Apply(std::vector<FieldRule>& rules) const override { ++callCount_; }

 private:
  /// @brief the number of times the Apply function was called
  int& callCount_;
};

/// @brief Test that the rule patch stores the name and version range properly
TEST_F(RulePatchTests, StoresNameAndVersionRange) {
  VersionRange range = VersionRange::All();

  RulePatch patch("test-patch", range, {});

  EXPECT_EQ(patch.Name(), "test-patch");
  EXPECT_EQ(patch.AppliesTo(), range);
  EXPECT_TRUE(patch.Operations().empty());
}

/// @brief Test that given we apply our fake operation patch we call the Apply function once
TEST_F(RulePatchTests, ApplyCallsSingleOperation) {
  int callCount = 0;

  std::vector<std::unique_ptr<IRulePatchOperation>> ops;
  ops.push_back(std::make_unique<FakeRulePatchOperation>(callCount));

  RulePatch patch("single-op", VersionRange::All(), std::move(ops));

  patch.Apply(rules_);

  EXPECT_EQ(callCount, 1);
}

/// @brief Test that each of our fake patch operations calls Apply once
TEST_F(RulePatchTests, ApplyCallsAllOperations) {
  int callCount1 = 0;
  int callCount2 = 0;
  int callCount3 = 0;

  std::vector<std::unique_ptr<IRulePatchOperation>> ops;
  ops.push_back(std::make_unique<FakeRulePatchOperation>(callCount1));
  ops.push_back(std::make_unique<FakeRulePatchOperation>(callCount2));
  ops.push_back(std::make_unique<FakeRulePatchOperation>(callCount3));

  RulePatch patch("multi-op", VersionRange::All(), std::move(ops));

  patch.Apply(rules_);

  EXPECT_EQ(callCount1, 1);
  EXPECT_EQ(callCount2, 1);
  EXPECT_EQ(callCount3, 1);
}

/// @brief Test that given we apply an empty version patch the rules are unaffected
TEST_F(RulePatchTests, ApplyWithNoOperationsDoesNothing) {
  RulePatch patch("empty", VersionRange::All(), {});

  EXPECT_NO_THROW(patch.Apply(rules_));
  EXPECT_TRUE(rules_.empty());
}

/// @brief Test that given we use an AddField patch, a field is added to the rules
TEST_F(RulePatchTests, ApplyModifiesRulesUsingRealOperations) {
  FieldRule rule{"key1", std::make_unique<IntegerInRangeRule>(0, 10),
                 std::make_unique<AllValuesSelector>()};

  std::vector<std::unique_ptr<IRulePatchOperation>> ops;
  ops.push_back(std::make_unique<AddFieldRulePatchOperation>(std::move(rule)));

  RulePatch patch("add-rule", VersionRange::All(), std::move(ops));

  patch.Apply(rules_);

  ASSERT_EQ(rules_.size(), 1);
  EXPECT_EQ(rules_[0].FieldKey, "key1");
}
