#pragma once

#include <datalint/SourceLocation.h>

#include <string>

namespace datalint {

/// @brief A key-value pair representing a raw field from input data.
struct RawField {
  /// @brief The key of the field.
  std::string Key;
  /// @brief The value of the field.
  std::string Value;
  /// @brief The source location of the field in the input file.
  SourceLocation Location;
};
}  // namespace datalint
