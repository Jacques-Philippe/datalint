#pragma once

#include <datalint/ApplicationDescriptor/ApplicationDescriptor.h>

#include <string>
#include <vector>

namespace datalint {

/// @brief Result of resolving an application descriptor.
struct ResolveResult {
  /// @brief The resolved application descriptor.
  ApplicationDescriptor Descriptor;
  /// @brief Any errors encountered during resolution.
  std::vector<std::string> Errors;

  /// @brief Whether the resolution was successful.
  /// @return False for any errors encountered, true otherwise.
  bool Success() const noexcept { return Errors.empty(); }
};
}  // namespace datalint
