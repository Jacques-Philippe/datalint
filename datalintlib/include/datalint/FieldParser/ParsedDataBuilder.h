#pragma once

#include <datalint/FieldParser/IFieldParser.h>
#include <datalint/FieldParser/ParsedData.h>
#include <datalint/RawData.h>

namespace datalint::fieldparser {
/// @brief Builder class for constructing ParsedData from RawData.
class ParsedDataBuilder {
 public:
  /// @brief Constructor that initializes the ParsedDataBuilder with a field parser.
  /// @param fieldparser the field parser to use for parsing raw fields.
  ParsedDataBuilder(std::unique_ptr<IFieldParser> fieldparser);

  /// @brief Builds and returns the ParsedData object.
  /// @return The constructed ParsedData object.
  ParsedData Build(const RawData& rawData) const;

 private:
  /// @brief The field parser used to parse raw fields.
  std::unique_ptr<IFieldParser> FieldParser_;
};
}  // namespace datalint::fieldparser
