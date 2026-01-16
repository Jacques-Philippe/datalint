#pragma once
#include <datalint/Error/ErrorLog.h>
#include <datalint/RuleSpecification/IValueRule.h>
#include <datalint/StringUtils.h>

namespace datalint::rules {
/// @brief Concrete implementation of the rule value applying an integer range rule on the selected
/// values. With this, we can specify that an integer value should be contained to a given range
/// inclusively
class IntegerInRangeRule final : public IValueRule {
 public:
  /// @brief Constructor
  /// @param min the minimum part of the range (inclusive)
  /// @param max the maximum part of the range (inclusive)
  IntegerInRangeRule(int min, int max) : Min_(min), Max_(max) {}

  /// @brief Function determining whether the incoming field value meets the rule expectations
  /// @param ctx the context available to the rule's evaluation
  /// @param errorCollector where we should send errors to given there's a problem with the field
  /// meeting expectations
  void Evaluate(const RuleContext& ctx,
                datalint::error::ErrorCollector& errorCollector) const override {
    int value;
    if (!datalint::utils::TryParseInt(ctx.Value.Value, value)) {
      errorCollector.AddErrorLog(
          datalint::error::ErrorLog{"Incorrect value type", "Value must be an integer"});
      return;
    }

    if (value < Min_ || value > Max_) {
      errorCollector.AddErrorLog(datalint::error::ErrorLog{
          "Incorrect value",
          "Value must be between " + std::to_string(Min_) + " and " + std::to_string(Max_)});
    }
  }

  /// @brief Clone function for use in patching / RuleSpecificationBuilder
  std::unique_ptr<IValueRule> Clone() const override {
    // Simply create a new instance with the same min and max
    return std::make_unique<IntegerInRangeRule>(Min_, Max_);
  }

 private:
  /// @brief The minimum value in our acceptable range (inclusive)
  int Min_;
  /// @brief the maximum value in our acceptable range (inclusive)
  int Max_;
};
}  // namespace datalint::rules
