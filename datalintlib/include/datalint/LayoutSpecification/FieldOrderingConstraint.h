#pragma once

#include <string>

namespace datalint::layout {
/// @brief Represent a field ordering constraint between two fields
struct FieldOrderingConstraint {
  /// @brief The key of the field that must come before
  std::string Before;
  /// @brief The key of the field that must come after
  std::string After;
};
}  // namespace datalint::layout
