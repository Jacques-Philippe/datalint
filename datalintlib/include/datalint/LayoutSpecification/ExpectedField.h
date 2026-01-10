#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string>

namespace datalint::layout {

/// @brief Class to contain the definition for an expected field, as a member of some layout
/// specification
class ExpectedField {
 public:
  /// @brief Default Constructor: initializes minCount to 1 and maxCount to unlimited, i.e. "At
  /// least once"
  ExpectedField() : minCount(1), maxCount(std::nullopt) {}

  /// @brief Explicit constructor
  /// @param minCount The minimum number of occurrences of this field
  /// @param maxCount The maximum number of occurrences of this field (or std::nullopt for
  /// unlimited)
  ExpectedField(std::size_t minCount, std::optional<std::size_t> maxCount = std::nullopt)
      : minCount(minCount), maxCount(maxCount) {
    if (maxCount && *maxCount < minCount) {
      throw std::invalid_argument("MaxCount < MinCount");
    }
  }

  /// @brief Sets the minimum number of occurrences of this field
  /// @param count The new minimum number of occurrences
  /// @throws std::invalid_argument if the new min count is greater than the current max count
  void SetMinCount(std::size_t count) {
    if (maxCount && *maxCount < count) {
      throw std::invalid_argument("MaxCount < MinCount");
    }
    minCount = count;
  }

  /// @brief Sets the maximum number of occurrences of this field
  /// @param count the new maximum number of occurrences (or std::nullopt for unlimited)
  /// @throws std::invalid_argument if the new max count is less than the current min count
  void SetMaxCount(std::optional<std::size_t> count) {
    if (count && *count < minCount) {
      throw std::invalid_argument("MaxCount < MinCount");
    }
    maxCount = count;
  }

  /// @brief Returns the minimum number of occurrences of this field
  /// @return The minimum number of occurrences
  std::size_t MinCount() const { return minCount; }
  /// @brief  Returns the maximum number of occurrences of this field
  /// @return The maximum number of occurrences
  const std::optional<std::size_t>& MaxCount() const { return maxCount; }

 private:
  /// @brief The minimum number of occurrences of this field
  std::size_t minCount;
  /// @brief The maximum number of occurrences of this field
  std::optional<std::size_t> maxCount;
};
}  // namespace datalint::layout
