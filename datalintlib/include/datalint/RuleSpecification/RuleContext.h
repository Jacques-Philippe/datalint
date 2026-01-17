#pragma once

#include <datalint/FieldParser/ParsedField.h>
#include <datalint/FieldParser/RawValue.h>

namespace datalint::rules {
/// @brief Context information provided to a rule when it is evaluated
struct RuleContext {
  /// @brief The parsed field associated to the rule context.
  const datalint::fieldparser::ParsedField& Field;
  /// @brief The raw value associated to the rule context.
  const datalint::fieldparser::RawValue& Value;
};
}  // namespace datalint::rules
