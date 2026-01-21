#pragma once

#include <datalint/Error/ErrorCollector.h>
#include <datalint/FieldParser/ParsedData.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/RuleSpecification.h>

namespace datalint::rules {
/// @brief Class responsible for validating all rules in the rule specification given the parsed
/// data
class RuleValidator {
 public:
  /// @brief Validate raw data against a rule specification
  /// @param ruleSpec The resolved rule specification
  /// @param parsedData The parsed raw input data
  /// @param errorCollector Collector for validation errors
  /// @return true if validation passed, false otherwise
  [[nodiscard]] bool Validate(const RuleSpecification& ruleSpec,
                              const fieldparser::ParsedData& parsedData,
                              error::ErrorCollector& errorCollector) const;

 private:
  /// @brief Helper to validate an individual field rule
  /// @param rule the field rule
  /// @param parsedData the parsed data
  /// @param errorCollector the error collector
  /// @return true for the field rule is valid
  bool ValidateFieldRule(const FieldRule& rule, const fieldparser::ParsedData& parsedData,
                         error::ErrorCollector& errorCollector) const;
};

}  // namespace datalint::rules
