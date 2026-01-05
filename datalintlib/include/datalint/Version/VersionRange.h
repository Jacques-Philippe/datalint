#pragma once

#include <datalint/Version/Version.h>

#include <optional>
#include <string>

namespace datalint {
/// @brief Struct to contain a range of versions
struct VersionRange {
  /// @brief The lower bound of the range, if any
  std::optional<Version> Min;
  /// @brief The upper bound of the range, if any
  std::optional<Version> Max;

  /// @brief Whether the incoming version belongs to the range defined by this version range
  /// @param v incoming version
  /// @return true for the incoming version belongs to the range defined by this version range
  /// instance
  bool Contains(const Version& v) const {
    if (Min && v < *Min) return false;
    if (Max && v >= *Max) return false;
    return true;
  }

  /// @brief An identifier for a range encompassing all versions
  /// @return an empty version range
  static VersionRange All() { return {}; }

  /// @brief An identifier for a range starting at the incoming version
  /// @param min the start point
  /// @return a range with min set to incoming version and max set to nullopt
  static VersionRange From(Version min) { return {min, std::nullopt}; }
  /// @brief An identifier for a range ending at the incoming version
  /// @param min the end point
  /// @return a range with min set to nullopt and max set to incoming version
  static VersionRange Until(Version max) { return {std::nullopt, max}; }
  /// @brief An identifier for a range starting at min and ending at max
  /// @param min the start point
  /// @param max the end point
  /// @return a range with min set to min and max set to max
  static VersionRange Between(Version min, Version max) { return {min, max}; }
};
}  // namespace datalint
