#pragma once

#include <datalint/FieldParser/ParsedField.h>
#include <datalint/FieldParser/RawValue.h>
#include <datalint/RuleSpecification/IValueSelector.h>

namespace datalint::rules {
/// @brief Concrete implementation of IValueSelector that selects a value at a specific index
class ValueAtIndexSelector final : public IValueSelector {
 public:
  /// @brief Virtual destructor
  virtual ~ValueAtIndexSelector() = default;
  /// @brief Constructor
  /// @param index the index at which we want to select our value
  ValueAtIndexSelector(std::size_t index) : index_(index) {}
  /// @brief Select function to select a raw value from a parsed field
  /// @param field the field from which we select the raw value
  /// @return The selected raw value
  std::vector<const datalint::fieldparser::RawValue*> Select(
      const datalint::fieldparser::ParsedField& field) const override {
    if (index_ >= field.Values.size()) {
      return {};
    }

    return {&field.Values[index_]};
  }

  /// @brief Clone function to create a deep copy of the selector
  std::unique_ptr<IValueSelector> Clone() const override {
    // Create a new selector with the same value
    return std::make_unique<ValueAtIndexSelector>(index_);
  }

 private:
  /// @brief The index of the value to select
  std::size_t index_;
};
}  // namespace datalint::rules
