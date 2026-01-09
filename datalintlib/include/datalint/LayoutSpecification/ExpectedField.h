#pragma once

#include <optional>
#include <string>

namespace datalint::layout {

/// @brief Struct to contain the definition for an expected field, as a member of some layout
/// specification
struct ExpectedField {
  /// @brief The minimum number of occurrences of this field
  std::size_t MinCount;
  /// @brief The maximum number of occurrences of this field
  std::optional<std::size_t> MaxCount;
};
}  // namespace datalint::layout
