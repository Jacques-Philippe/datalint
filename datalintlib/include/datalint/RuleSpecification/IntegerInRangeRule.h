#pragma once
#include <datalint/Error/ErrorLog.h>
#include <datalint/RuleSpecification/IValueRule.h>
#include <datalint/StringUtils.h>

namespace datalint::rules {
class IntegerInRangeRule final : public IValueRule {
 public:
  IntegerInRangeRule(int min, int max) : Min_(min), Max_(max) {}

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
  int Min_;
  int Max_;
};
}  // namespace datalint::rules
