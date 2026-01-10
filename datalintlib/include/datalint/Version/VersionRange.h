#pragma once

#include <datalint/Version/Version.h>

#include <optional>

namespace datalint {
/// @brief Class to contain a range of versions
class VersionRange {
 public:
  /// @brief Constructor: must provide both min and max (can be nullopt)
  /// @param min The lower bound of the range, if any
  /// @param max The upper bound of the range, if any
  /// @throws std::invalid_argument if min > max
  VersionRange(std::optional<Version> min, std::optional<Version> max)
      : Min_(std::move(min)), Max_(std::move(max)) {
    // Optional: validate that Min <= Max if both are set
    if (Min_ && Max_ && *Min_ > *Max_) {
      throw std::invalid_argument("VersionRange: Min cannot be greater than Max");
    }
  }
  /// @brief Getter for the lower bound of the range, if any
  /// @return The lower bound of the range, if any
  std::optional<Version> Min() const { return Min_; }
  /// @brief Getter for the upper bound of the range, if any
  /// @return The upper bound of the range, if any
  std::optional<Version> Max() const { return Max_; }

  /// @brief Whether the incoming version belongs to the range defined by this version range
  /// @param v incoming version
  /// @return true for the incoming version belongs to the range defined by this version range
  /// instance
  bool Contains(const Version& v) const {
    if (Min_ && v < *Min_) return false;
    if (Max_ && v > *Max_) return false;
    return true;
  }

  /// @brief Version range representing all versions
  /// @return VersionRange representing all versions
  static VersionRange All() { return VersionRange(std::nullopt, std::nullopt); }

  /// @brief Version range starting at the incoming version, inclusive
  /// @param min the lower bound version
  /// @return the VersionRange starting at the incoming version, inclusive
  static VersionRange From(const Version& min) { return VersionRange(min, std::nullopt); }

  /// @brief Version range ending at the incoming version, inclusive
  /// @param max the upper bound version
  /// @return the VersionRange ending at the incoming version, inclusive
  static VersionRange Until(const Version& max) { return VersionRange(std::nullopt, max); }

  /// @brief Version range between the incoming min and max versions, inclusive
  /// @param min the lower bound version, inclusive
  /// @param max the upper bound version, inclusive
  /// @return the VersionRange between the incoming min and max versions, inclusive
  /// @throws std::invalid_argument if min > max
  static VersionRange Between(const Version& min, const Version& max) {
    return VersionRange(min, max);
  }

 private:
  /// @brief The lower bound of the range, if any
  std::optional<Version> Min_;
  /// @brief The upper bound of the range, if any
  std::optional<Version> Max_;
};
}  // namespace datalint
