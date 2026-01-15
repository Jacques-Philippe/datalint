#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RuleSpecification.h>
#include <datalint/RuleSpecification/RuleSpecificationBuilder.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint;

class TestAddRuleOperation final : public IRulePatchOperation {
 public:
  explicit TestAddRuleOperation(std::string key) : key_(std::move(key)) {}

  void Apply(std::vector<FieldRule>& rules) const override {
    rules.push_back(FieldRule{key_,
                              nullptr,  // rule not needed for this test
                              nullptr});
  }

 private:
  std::string key_;
};

RulePatch MakePatch(std::string name, VersionRange range,
                    std::vector<std::unique_ptr<IRulePatchOperation>> ops) {
  return RulePatch(std::move(name), std::move(range), std::move(ops));
}

TEST(RuleSpecificationBuilderTests, AppliesPatchWhenVersionMatches) {
  RuleSpecificationBuilder builder;
  Version version{1, 0, 0};

  std::vector<RulePatch> patches;
  std::vector<std::unique_ptr<IRulePatchOperation>> ops;
  ops.push_back(std::make_unique<TestAddRuleOperation>("field1"));
  patches.push_back(MakePatch("patch1", VersionRange::All(), std::move(ops)));

  RuleSpecification spec = builder.Build(version, patches);

  ASSERT_EQ(spec.Rules().size(), 1);
  EXPECT_EQ(spec.Rules()[0].FieldKey, "field1");
}

TEST(RuleSpecificationBuilderTests, SkipsPatchWhenVersionDoesNotMatch) {
  RuleSpecificationBuilder builder;
  Version version{2, 0, 0};

  std::vector<RulePatch> patches;
  std::vector<std::unique_ptr<IRulePatchOperation>> ops;
  ops.push_back(std::make_unique<TestAddRuleOperation>("field1"));
  patches.push_back(MakePatch("patch1", VersionRange::Until(Version{1, 0, 0}), std::move(ops)));

  RuleSpecification spec = builder.Build(version, patches);

  EXPECT_TRUE(spec.Rules().empty());
}

TEST(RuleSpecificationBuilderTests, AppliesMultipleMatchingPatches) {
  RuleSpecificationBuilder builder;
  Version version{1, 0, 0};

  std::vector<RulePatch> patches;

  std::vector<std::unique_ptr<IRulePatchOperation>> ops1;
  ops1.push_back(std::make_unique<TestAddRuleOperation>("field1"));
  patches.push_back(MakePatch("patch1", VersionRange::All(), std::move(ops1)));

  std::vector<std::unique_ptr<IRulePatchOperation>> ops2;
  ops2.push_back(std::make_unique<TestAddRuleOperation>("field2"));
  patches.push_back(MakePatch("patch2", VersionRange::All(), std::move(ops2)));

  RuleSpecification spec = builder.Build(version, patches);

  ASSERT_EQ(spec.Rules().size(), 2);
  EXPECT_EQ(spec.Rules()[0].FieldKey, "field1");
  EXPECT_EQ(spec.Rules()[1].FieldKey, "field2");
}

TEST(RuleSpecificationBuilderTests, AppliesPatchesInOrder) {
  RuleSpecificationBuilder builder;
  Version version{1, 0, 0};

  std::vector<RulePatch> patches;

  std::vector<std::unique_ptr<IRulePatchOperation>> ops1;
  ops1.push_back(std::make_unique<TestAddRuleOperation>("first"));
  patches.push_back(MakePatch("first", VersionRange::All(), std::move(ops1)));

  std::vector<std::unique_ptr<IRulePatchOperation>> ops2;
  ops2.push_back(std::make_unique<TestAddRuleOperation>("second"));
  patches.push_back(MakePatch("second", VersionRange::All(), std::move(ops2)));

  RuleSpecification spec = builder.Build(version, patches);

  ASSERT_EQ(spec.Rules().size(), 2);
  EXPECT_EQ(spec.Rules()[0].FieldKey, "first");
  EXPECT_EQ(spec.Rules()[1].FieldKey, "second");
}

TEST(RuleSpecificationBuilderTests, NoPatchesProducesEmptySpecification) {
  RuleSpecificationBuilder builder;
  Version version{1, 0, 0};

  RuleSpecification spec = builder.Build(version, {});

  EXPECT_TRUE(spec.Rules().empty());
}
