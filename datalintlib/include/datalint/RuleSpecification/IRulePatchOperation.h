#pragma once

#include <datalint/RuleSpecification/FieldRule.h>

#include <vector>

namespace datalint::rules {
/// @brief Interface to define an operation we can apply to a rule patch. It's through these
/// operations that we can define new fields, remove existing ones
class IRulePatchOperation {
 public:
  /// @brief Virtual destructor
  virtual ~IRulePatchOperation() = default;

  /// @brief Application function to be overridden in the concrete operation instance
  /// @param rules the rules to modify
  virtual void Apply(std::vector<FieldRule>& rules) const = 0;
};

}  // namespace datalint::rules
