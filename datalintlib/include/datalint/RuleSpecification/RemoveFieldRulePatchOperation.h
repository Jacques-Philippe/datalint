#pragma once

#include <datalint/RuleSpecification/IRulePatchOperation.h>

#include <functional>

namespace datalint::rules {
/// @brief Class defining how field rules should be removed from the set of all fields via field
/// rule patches
class RemoveFieldRulePatchOperation final : public IRulePatchOperation {
 public:
  /// @brief The predicate to determine which fields match the criteria
  using Predicate = std::function<bool(const FieldRule&)>;

  /// @brief Constructor
  /// @param pred the predicate that defines how we match to certain values inside of a parsed field
  explicit RemoveFieldRulePatchOperation(Predicate pred) : Pred_(std::move(pred)) {}

  /// @brief Concrete implementation of the apply function, allowing us to remove field rules from
  /// our set of all rules, given they meet the predicate criteria
  /// @param rules the rules to modify
  void Apply(std::vector<FieldRule>& rules) const override { std::erase_if(rules, Pred_); }

 private:
  /// @brief the predicate that determines whether certain field rules should be removed
  Predicate Pred_;
};
}  // namespace datalint::rules
