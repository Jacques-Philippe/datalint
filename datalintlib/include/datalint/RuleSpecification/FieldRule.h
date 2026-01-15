#pragma once

#include <datalint/RuleSpecification/IValueRule.h>
#include <datalint/RuleSpecification/IValueSelector.h>

#include <string>

namespace datalint::rules {
struct FieldRule {
  std::string FieldKey;
  std::unique_ptr<IValueRule> ValueRule;
  std::unique_ptr<IValueSelector> ValueSelector;
};

inline FieldRule CloneRule(const FieldRule& rule) {
  return FieldRule{
      rule.FieldKey,
      rule.ValueRule->Clone(),
      rule.ValueSelector->Clone(),
  };
}
}  // namespace datalint::rules
