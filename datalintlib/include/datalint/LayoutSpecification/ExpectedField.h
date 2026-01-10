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

  /// @brief Default constructor
  ExpectedField() = default;

  /// @brief Constructor
  ExpectedField(std::size_t minCount, std::optional<std::size_t> maxCount)
      : MinCount(minCount), MaxCount(maxCount) {
    // Ensure that if maxCount has a value, it is not less than minCount
    if (maxCount.has_value() && maxCount.value() < minCount) {
      throw std::invalid_argument("MaxCount cannot be less than MinCount");
    }
  }
};
}  // namespace datalint::layout
