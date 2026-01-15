#pragma once

#include <datalint/FieldParser/ParsedField.h>
#include <datalint/FieldParser/RawValue.h>
#include <datalint/RuleSpecification/IValueSelector.h>

namespace datalint::rules {
/// @brief Concrete implementation of IValueSelector that selects a value at a specific index
class ValueAtIndexSelector : public IValueSelector {
 public:
  /// @brief Virtual destructor
  virtual ~ValueAtIndexSelector() = default;
  /// @brief Constructor
  ValueAtIndexSelector(int index) : index_(index) {}
  /// @brief Select function to select a raw value from a parsed field
  /// @param field the field from which we select the raw value
  /// @return The selected raw value
  /// @throws std::out_of_range if the index is out of range for the field's values
  const datalint::fieldparser::RawValue& Select(
      const datalint::fieldparser::ParsedField& field) const override {
    if (index_ < 0 || static_cast<size_t>(index_) >= field.Values.size()) {
      throw std::out_of_range("Index out of range in ValueAtIndexSelector");
    }
    return field.Values[index_];
  }

 private:
  /// @brief The index of the value to select
  int index_;
};
}  // namespace datalint::rules
