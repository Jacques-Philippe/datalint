#pragma once

#include <datalint/RuleSpecification/IRulePatchOperation.h>

namespace datalint::rules {
class AddFieldRulePatchOperation final : public IRulePatchOperation {
 public:
  explicit AddFieldRulePatchOperation(FieldRule rule) : Rule_(std::move(rule)) {}

  void Apply(std::vector<FieldRule>& rules) const override { rules.push_back(CloneRule(Rule_)); }

 private:
  FieldRule Rule_;
};
}  // namespace datalint::rules
