#pragma once

#include <datalint/ApplicationDescriptor/ApplicationDescriptor.h>

#include <optional>
#include <string>
#include <vector>

namespace datalint {

/// @brief Result of resolving an application descriptor.
struct ResolveResult {
  /// @brief The resolved application descriptor.
  std::optional<ApplicationDescriptor> Descriptor;
  /// @brief Any errors encountered during resolution.
  std::vector<std::string> Errors;

  /// @brief Whether the resolution was successful.
  /// @return True for no errors encountered and descriptor resolved, false otherwise.
  bool Success() const noexcept { return Errors.empty() && Descriptor.has_value(); }
};
}  // namespace datalint
