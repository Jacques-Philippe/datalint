#pragma once

#include <datalint/RuleSpecification/FieldRule.h>

#include <vector>

namespace datalint::rules {
class IRulePatchOperation {
 public:
  virtual ~IRulePatchOperation() = default;

  virtual void Apply(std::vector<FieldRule>& rules) const = 0;
};

}  // namespace datalint::rules
