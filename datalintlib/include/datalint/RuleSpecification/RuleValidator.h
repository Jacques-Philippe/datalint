#pragma once

#include <datalint/Error/ErrorCollector.h>
#include <datalint/FieldParser/ParsedData.h>
#include <datalint/RawData.h>
#include <datalint/RuleSpecification/FieldRule.h>
#include <datalint/RuleSpecification/RuleSpecification.h>

#include <vector>

namespace datalint::rules {

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
  bool ValidateFieldRule(const FieldRule& rule, const fieldparser::ParsedData& parsedData,
                         error::ErrorCollector& errorCollector) const;
};

}  // namespace datalint::rules
