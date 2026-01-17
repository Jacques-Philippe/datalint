#pragma once

#include <datalint/FieldParser/ParsedField.h>
#include <datalint/FieldParser/RawValue.h>

#include <memory>
#include <vector>

namespace datalint::rules {
/// @brief Interface for selecting a set of raw values from a given parsed field.
class IValueSelector {
 public:
  /// @brief Virtual destructor
  virtual ~IValueSelector() = default;
  /// @brief Select function to select a raw value from a parsed field
  /// @param field the field from which we select the raw value
  /// @return The selected raw value
  virtual std::vector<const datalint::fieldparser::RawValue*> Select(
      const datalint::fieldparser::ParsedField& field) const = 0;

  /// @brief Clone function
  /// @return a clone of the value selector
  virtual std::unique_ptr<IValueSelector> Clone() const = 0;
};
}  // namespace datalint::rules
