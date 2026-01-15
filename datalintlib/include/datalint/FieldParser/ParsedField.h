#pragma once

#include <datalint/FieldParser/RawValue.h>

#include <string>
#include <vector>

namespace datalint::fieldparser {
/// @brief Represents a parsed field with its key and associated raw values.
struct ParsedField {
  /// @brief The key of the parsed field.
  std::string Key;
  /// @brief The collection of raw values associated with the field.
  std::vector<RawValue> Values;
};
}  // namespace datalint::fieldparser
