#include <datalint/RuleSpecification/RuleValidator.h>

namespace datalint::rules {

bool RuleValidator::Validate(const RuleSpecification& ruleSpec,
                             const fieldparser::ParsedData& parsedData,
                             error::ErrorCollector& errorCollector) const {
  bool success = true;

  for (const auto& rule : ruleSpec.Rules()) {
    if (!ValidateFieldRule(rule, parsedData, errorCollector)) {
      success = false;
    }
  }

  return success;
}

bool RuleValidator::ValidateFieldRule(const FieldRule& rule,
                                      const fieldparser::ParsedData& parsedData,
                                      error::ErrorCollector& errorCollector) const {
  bool matchedAnyField = false;
  bool success = true;

  for (const auto& field : parsedData.Fields()) {
    if (field.Key != rule.FieldKey) {
      continue;
    }

    matchedAnyField = true;

    const auto selectedValues = rule.ValueSelector->Select(field);

    for (const auto& value : selectedValues) {
      RuleContext ctx{field, *value};

      rule.ValueRule->Evaluate(ctx, errorCollector);

      if (errorCollector.HasErrors()) {
        success = false;
      }
    }
  }

  if (!matchedAnyField) {
    errorCollector.AddErrorLog(error::ErrorLog{"Missing required field", rule.FieldKey});
    return false;
  }

  return success;
}

}  // namespace datalint::rules
