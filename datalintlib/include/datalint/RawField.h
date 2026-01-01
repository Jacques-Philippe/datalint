#pragma once

#include <string>

namespace datalint {

/// @brief A key-value pair representing a raw field from input data.
struct RawField {
  /// @brief The key of the field.
  std::string Key;
  /// @brief The value of the field.
  std::string Value;
};
}  // namespace datalint
