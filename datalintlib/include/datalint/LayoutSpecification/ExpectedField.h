#pragma once

#include <optional>
#include <string>

namespace datalint::layout {

/// @brief Struct to contain the definition for an expected field, as a member of some layout
/// specification
struct ExpectedField {
  /// @brief Unique key used to identify the field as a member of the layout specification
  std::string Key;
  /// @brief Whether the field is mandatory
  bool Required = false;
  /// @brief A string specifying the type the field is expected to have
  std::optional<std::string> TypeString;
};
}  // namespace datalint::layout
