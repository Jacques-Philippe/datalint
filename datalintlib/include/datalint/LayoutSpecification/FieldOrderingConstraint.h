#pragma once

#include <string>

namespace datalint::layout {
/// @brief Represent a field ordering constraint between two fields
struct FieldOrderingConstraint {
  /// @brief The key of the field that must come before
  std::string BeforeKey;
  /// @brief The key of the field that must come after
  std::string AfterKey;

  /// @brief Equality operator for comparing constraints
  /// @param other The other constraint to compare with
  /// @return true if both constraints are equal, false otherwise
  bool operator==(const FieldOrderingConstraint& other) const {
    return BeforeKey == other.BeforeKey && AfterKey == other.AfterKey;
  }
};
}  // namespace datalint::layout
