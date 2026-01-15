#pragma once

#include <datalint/Error/ErrorCollector.h>
#include <datalint/RuleSpecification/RuleContext.h>

namespace datalint::rules {
/// @brief Class responsible for specifying a rule to apply to a value
class IValueRule {
 public:
  /// @brief Virtual destructor
  virtual ~IValueRule() = default;

  /// @brief Virtual function to define how the rule should evaluate
  /// @param ctx the context of the rule
  /// @param errorCollector the error collector
  virtual void Evaluate(const RuleContext& ctx,
                        datalint::error::ErrorCollector& errorCollector) const = 0;

  virtual std::unique_ptr<IValueRule> Clone() const = 0;
};
}  // namespace datalint::rules
