#pragma once

#include <datalint/ApplicationDescriptor/ApplicationDescriptor.h>

#include <string>
#include <vector>

namespace datalint {

// Forward declaration
class RawData;

/// @brief Result of resolving an application descriptor.
struct ResolveResult {
  /// @brief Whether the resolution was successful.
  bool Success;
  /// @brief The resolved application descriptor.
  ApplicationDescriptor Descriptor;
  /// @brief Any errors encountered during resolution.
  std::vector<std::string> Errors;
};

/// @brief Interface for resolving application descriptors from raw data.
class IApplicationDescriptorResolver {
 public:
  /// @brief Virtual destructor.
  virtual ~IApplicationDescriptorResolver() = default;

  /// @brief Resolve the application descriptor (name and version) from the given raw data.
  /// @param rawData The raw data from which to resolve the application descriptor.
  /// @return The resolved ApplicationDescriptor.
  virtual ResolveResult Resolve(const datalint::RawData& rawData) = 0;
};
}  // namespace datalint
