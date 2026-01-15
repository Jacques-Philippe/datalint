#pragma once

#include <datalint/FieldParser/ParsedField.h>
#include <datalint/RawField.h>

#include <string>

namespace datalint::fieldparser {
/// @brief Interface for defining the parser of field values.
class IFieldParser {
 public:
  virtual ~IFieldParser() = default;

  /// @brief Parses a raw field value into its constituent raw values.
  /// @param rawFieldValue The raw field value to parse.
  /// @return A ParsedField representing the parsed values.
  virtual ParsedField ParseFieldValue(const RawField& rawFieldValue) const = 0;
};
}  // namespace datalint::fieldparser
