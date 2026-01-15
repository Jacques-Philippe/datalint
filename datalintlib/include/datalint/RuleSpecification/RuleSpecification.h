#pragma once

#include <datalint/RuleSpecification/FieldRule.h>

#include <vector>

namespace datalint::rules {
class RuleSpecification {
 public:
  /// @brief Constructor that takes ownership of the resolved rules
  /// @param rules The field rules that make up this specification
  explicit RuleSpecification(std::vector<FieldRule> rules) : Rules_(std::move(rules)) {}

  /// @brief Access the resolved field rules
  /// @return const reference to the vector of rules
  const std::vector<FieldRule>& Rules() const noexcept { return Rules_; }

 private:
  std::vector<FieldRule> Rules_;
};
}  // namespace datalint::rules
