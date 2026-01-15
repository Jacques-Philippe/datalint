#pragma once

#include <datalint/FieldParser/ParsedField.h>
#include <datalint/FieldParser/RawValue.h>
#include <datalint/RuleSpecification/IValueSelector.h>

namespace datalint::rules {
/// @brief Concrete implementation of IValueSelector that selects all values
class AllValuesSelector : public IValueSelector {
 public:
  /// @brief Virtual destructor
  virtual ~AllValuesSelector() = default;
  /// @brief Constructor
  AllValuesSelector() {}
  /// @brief Select function to select a raw value from a parsed field
  /// @param field the field from which we select the raw value
  /// @return The selected raw value
  /// @throws std::out_of_range if the index is out of range for the field's values
  std::vector<const datalint::fieldparser::RawValue*> Select(
      const datalint::fieldparser::ParsedField& field) const override {
    std::vector<const datalint::fieldparser::RawValue*> result;
    for (const auto& value : field.Values) {
      result.push_back(&value);
    }
    return result;
  }
};
}  // namespace datalint::rules
