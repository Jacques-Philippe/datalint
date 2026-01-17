#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IValueRule.h>
#include <datalint/RuleSpecification/IValueSelector.h>
#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

using namespace datalint::rules;

/// @brief Dummy implementation of an IValueRule so we can test that its values are transmitted as
/// expected
class DummyValueRule final : public IValueRule {
 public:
  /// @brief Constructor
  /// @param id the id of the value rule
  explicit DummyValueRule(int id) : id_(id) {}

  /// @brief Clone function
  /// @return a copy of the dummy value rule
  std::unique_ptr<IValueRule> Clone() const override {
    return std::make_unique<DummyValueRule>(id_);
  }

  /// @brief Getter for the id
  /// @return the id
  int Id() const { return id_; }

  /// @brief Dummy evaluation function
  void Evaluate(const RuleContext&, datalint::error::ErrorCollector&) const override {}

 private:
  /// @brief the id of the dummy value rule
  int id_;
};

/// @brief Dummy implementation of IValueSelector so we can test the values are transmitted as
/// expected
class DummyValueSelector final : public IValueSelector {
 public:
  /// @brief Constructor
  /// @param id the id of the value selector
  explicit DummyValueSelector(int id) : id_(id) {}

  /// @brief Clone function
  /// @return the clone
  std::unique_ptr<IValueSelector> Clone() const override {
    return std::make_unique<DummyValueSelector>(id_);
  }

  /// @brief Getter for the instance id
  /// @return the id
  int Id() const { return id_; }

  /// @brief Dummy select implementation
  std::vector<const datalint::fieldparser::RawValue*> Select(
      const datalint::fieldparser::ParsedField&) const override {
    return {};
  }

 private:
  /// @brief the id associated to the instance
  int id_;
};

/// @brief Test that cloning produces a deep copy of each property of the field rule
TEST(FieldRuleTests, CloneRuleProducesDeepCopy) {
  FieldRule original{
      "TestKey",
      std::make_unique<DummyValueRule>(42),
      std::make_unique<DummyValueSelector>(7),
  };

  FieldRule clone = CloneRule(original);

  // FieldKey copied
  EXPECT_EQ(clone.FieldKey, "TestKey");

  // Pointers are not shared
  EXPECT_NE(clone.ValueRule.get(), original.ValueRule.get());
  EXPECT_NE(clone.ValueSelector.get(), original.ValueSelector.get());

  // Concrete types preserved
  auto* rule = dynamic_cast<DummyValueRule*>(clone.ValueRule.get());
  auto* selector = dynamic_cast<DummyValueSelector*>(clone.ValueSelector.get());

  ASSERT_NE(rule, nullptr);
  ASSERT_NE(selector, nullptr);

  EXPECT_EQ(rule->Id(), 42);
  EXPECT_EQ(selector->Id(), 7);
}

/// @brief Test that the clone function throws given the value rule is missing
TEST(FieldRuleTests, CloneRuleThrowsIfValueRuleMissing) {
  FieldRule invalid{
      "TestKey",
      nullptr,
      std::make_unique<DummyValueSelector>(1),
  };

  EXPECT_THROW(CloneRule(invalid), std::logic_error);
}

/// @brief Test that the clone function throws given value selector is missing
TEST(FieldRuleTests, CloneRuleThrowsIfValueSelectorMissing) {
  FieldRule invalid{
      "TestKey",
      std::make_unique<DummyValueRule>(1),
      nullptr,
  };

  EXPECT_THROW(CloneRule(invalid), std::logic_error);
}
