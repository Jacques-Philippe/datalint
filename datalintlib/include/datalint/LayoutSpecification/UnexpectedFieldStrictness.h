#pragma once

namespace datalint::layout {
/// @brief Enumeration to define strictness levels for unexpected fields in layout specifications

enum class UnexpectedFieldStrictness {
  /// @brief Strict mode: unexpected fields will cause validation errors
  Strict,
  /// @brief Permissive mode: unexpected fields will be ignored
  Permissive
};
}  // namespace datalint::layout
