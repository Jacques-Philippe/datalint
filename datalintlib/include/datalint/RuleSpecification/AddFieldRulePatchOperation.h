#pragma once

#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/IRulePatchOperation.h>

#include <vector>

namespace datalint::rules {
/// @brief Concrete class of rule patch operation for adding a field to a rule patch
class AddFieldRulePatchOperation final : public IRulePatchOperation {
 public:
  /// @brief Constructor
  /// @param rule the rule to add to the patch
  explicit AddFieldRulePatchOperation(FieldRule&& rule) : Rule_(std::move(rule)) {}

  /// @brief Overridden apply function to add the field rule to the existing set of all rules
  /// @param rules the rules to modify
  void Apply(std::vector<FieldRule>& rules) const override { rules.push_back(CloneRule(Rule_)); }

 private:
  /// @brief The rule to add
  FieldRule Rule_;
};
}  // namespace datalint::rules
