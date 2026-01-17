#pragma once

#include <datalint/RuleSpecification/IValueRule.h>
#include <datalint/RuleSpecification/IValueSelector.h>

#include <string>

namespace datalint::rules {
/// @brief Defines a single field rule instance telling us how to treat certain fields; these field
/// rules make up all rules contained in our rule specification
struct FieldRule {
  /// @brief The key of the parsed field
  std::string FieldKey;
  /// @brief The rule to apply to the field
  std::unique_ptr<IValueRule> ValueRule;
  /// @brief the accessor to determine which values of the field the rule should be applied to
  std::unique_ptr<IValueSelector> ValueSelector;
};

/// @brief Clone function to return a copy of the incoming rule
/// @param rule the rule to copy
/// @return a copy of the rule
/// @throws logic error for either value rule or selector not initialized
inline FieldRule CloneRule(const FieldRule& rule) {
  if (!rule.ValueRule) {
    throw std::logic_error("FieldRule ValueRule is not initialized");
  }
  if (!rule.ValueSelector) {
    throw std::logic_error("FieldRule ValueSelector is not initialized");
  }
  return FieldRule{
      rule.FieldKey,
      rule.ValueRule->Clone(),
      rule.ValueSelector->Clone(),
  };
}
}  // namespace datalint::rules
