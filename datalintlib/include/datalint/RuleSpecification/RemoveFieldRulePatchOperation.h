#pragma once

#include <datalint/RuleSpecification/IRulePatchOperation.h>

#include <functional>

namespace datalint::rules {
class RemoveFieldRulePatchOperation final : public IRulePatchOperation {
  using Predicate = std::function<bool(const FieldRule&)>;

  explicit RemoveFieldRulePatchOperation(Predicate pred) : pred_(std::move(pred)) {}

  void Apply(std::vector<FieldRule>& rules) const override { std::erase_if(rules, pred_); }

 private:
  Predicate pred_;
};
}  // namespace datalint::rules
