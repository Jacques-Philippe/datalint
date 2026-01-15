#pragma once

#include <datalint/FieldParser/ParsedField.h>
#include <datalint/FieldParser/RawValue.h>

namespace datalint::rules {
/// @brief Interface for selecting a raw value from a parsed field.
class IValueSelector {
 public:
  /// @brief Virtual destructor
  virtual ~IValueSelector() = default;
  /// @brief Select function to select a raw value from a parsed field
  /// @param field the field from which we select the raw value
  /// @return The selected raw value
  virtual const datalint::fieldparser::RawValue& Select(
      const datalint::fieldparser::ParsedField& field) const = 0;
};
}  // namespace datalint::rules
