#include <datalint/RuleSpecification/AddFieldRulePatchOperation.h>
#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/IRulePatchOperation.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RulePatch.h>
#include <datalint/Version/VersionRange.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint;

class RulePatchTests : public ::testing::Test {
 protected:
  std::vector<FieldRule> rules_;  // empty is fine for most tests
};

class FakeRulePatchOperation : public IRulePatchOperation {
 public:
  explicit FakeRulePatchOperation(int& callCount) : callCount_(callCount) {}

  void Apply(std::vector<FieldRule>& rules) const override { ++callCount_; }

 private:
  int& callCount_;
};

TEST_F(RulePatchTests, StoresNameAndVersionRange) {
  VersionRange range = VersionRange::All();

  RulePatch patch("test-patch", range, {});

  EXPECT_EQ(patch.Name(), "test-patch");
  EXPECT_EQ(patch.AppliesTo(), range);
  EXPECT_TRUE(patch.Operations().empty());
}

TEST_F(RulePatchTests, ApplyCallsSingleOperation) {
  int callCount = 0;

  std::vector<std::unique_ptr<IRulePatchOperation>> ops;
  ops.push_back(std::make_unique<FakeRulePatchOperation>(callCount));

  RulePatch patch("single-op", VersionRange::All(), std::move(ops));

  patch.Apply(rules_);

  EXPECT_EQ(callCount, 1);
}

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

TEST_F(RulePatchTests, ApplyWithNoOperationsDoesNothing) {
  RulePatch patch("empty", VersionRange::All(), {});

  EXPECT_NO_THROW(patch.Apply(rules_));
  EXPECT_TRUE(rules_.empty());
}

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
