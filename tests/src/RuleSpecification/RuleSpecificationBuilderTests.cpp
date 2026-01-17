#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RuleSpecification.h>
#include <datalint/RuleSpecification/RuleSpecificationBuilder.h>
#include <gtest/gtest.h>

using namespace datalint::rules;
using namespace datalint;

/// @brief Test fixture
class TestAddRuleOperation final : public IRulePatchOperation {
 public:
  /// @brief Constructor
  /// @param key the key associated to the field rule to add to the rules
  explicit TestAddRuleOperation(std::string key) : key_(std::move(key)) {}

  /// @brief Apply function to apply the given rule patch operation to the list of rules. Adds a
  /// field rule with the given key to the list of rules.
  /// @param rules the list of rules to modify
  void Apply(std::vector<FieldRule>& rules) const override {
    rules.push_back(FieldRule{key_,
                              nullptr,  // rule not needed for this test
                              nullptr});
  }

 private:
  /// @brief The key of the field rule to add
  std::string key_;
};

/// @brief Helper to create an example rule patch
/// @param name the name of the patch
/// @param range the version range the patch applies to
/// @param ops the operations composing the patch
/// @return the constructed rule patch
RulePatch MakePatch(std::string name, VersionRange range,
                    std::vector<std::unique_ptr<IRulePatchOperation>> ops) {
  return RulePatch(std::move(name), std::move(range), std::move(ops));
}

/// @brief Test that given a patch belongs to the versions to apply, it's applied to the rules
/// specification
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

/// @brief Test that given a patch does not belong to the versions to apply, it's not applied to the
/// rules specification
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

/// @brief Test that given many patches belong to the versions to apply, they're applied to the
/// rules specification
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

/// @brief Test that given many patches belong to the versions to apply, they are applied in the
/// order in which they are provided
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

/// @brief Test that given no patches are provided, the rules specification is empty
TEST(RuleSpecificationBuilderTests, NoPatchesProducesEmptySpecification) {
  RuleSpecificationBuilder builder;
  Version version{1, 0, 0};

  RuleSpecification spec = builder.Build(version, {});

  EXPECT_TRUE(spec.Rules().empty());
}
