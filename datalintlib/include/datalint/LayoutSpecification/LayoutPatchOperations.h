#pragma once

#include <datalint/LayoutSpecification/ExpectedField.h>

#include <functional>
#include <string>
#include <variant>

namespace datalint::layout {
/// @brief Struct to represent an operation used to add a field to an existing layout specification
struct AddField {
  /// @brief The key associated to the field
  std::string Key;
  /// @brief The field to add
  ExpectedField Field;
};

/// @brief Struct to represent an operation used to remove a field from an existing layout
/// specification
struct RemoveField {
  /// @brief The key associated to the field
  std::string Key;
};

/// @brief Struct to represent an operation used to modify a field in an existing layout
/// specification
struct ModifyField {
  /// @brief The key associated to the field
  std::string Key;
  /// @brief The mutator function to apply to the field
  std::function<void(ExpectedField&)> Mutator;
};

/// @brief Variant to represent any layout patch operation
using LayoutPatchOperation = std::variant<AddField, RemoveField, ModifyField>;

}  // namespace datalint::layout
