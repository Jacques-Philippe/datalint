#pragma once

#include <datalint/FieldParser/ParsedField.h>

#include <vector>

namespace datalint::fieldparser {
/// @brief Class to contain all fields parsed from raw data
class ParsedData {
 public:
  /// @brief Constructor that initializes ParsedData with a vector of ParsedField.
  /// @param fields The vector of ParsedField to initialize with.
  ParsedData(std::vector<ParsedField> fields) : parsedFields(std::move(fields)) {}

  /// @brief Returns a reference to the vector of parsed fields.
  /// @return A const reference to the vector of parsed fields.
  const std::vector<ParsedField>& Fields() const noexcept { return parsedFields; }

 private:
  /// @brief The collection of parsed fields.
  std::vector<ParsedField> parsedFields;
};

}  // namespace datalint::fieldparser
