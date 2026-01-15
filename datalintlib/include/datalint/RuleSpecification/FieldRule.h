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
}  // namespace datalint::rules
