#pragma once

#include <datalint/FieldParser/IFieldParser.h>
#include <datalint/FieldParser/ParsedField.h>

namespace datalint::fieldparser {
/// @brief Concrete implementation of IFieldParser for parsing CSV field values.
class CsvFieldParser : public IFieldParser {
 public:
  /// @brief Parses a raw field value into its constituent raw values.
  /// @param rawFieldValue The raw field value to parse.
  /// @return A ParsedField representing the parsed values.
  ParsedField ParseFieldValue(const RawField& rawFieldValue) const override;
};
}  // namespace datalint::fieldparser
