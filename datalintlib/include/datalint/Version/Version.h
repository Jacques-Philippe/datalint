#pragma once

#include <string>

namespace datalint {
/// @brief Struct to contain a version definition
struct Version {
  /// @brief Major version number. The first of the numbers, i.e. HERE.x.x
  int Major;
  /// @brief Minor version number. The second of the numbers, i.e. x.HERE.x
  int Minor;
  /// @brief Patch version number. The third of the numbers, i.e. x.x.HERE
  int Patch;

  friend auto operator<=>(const Version&, const Version&) = default;
};
}  // namespace datalint
