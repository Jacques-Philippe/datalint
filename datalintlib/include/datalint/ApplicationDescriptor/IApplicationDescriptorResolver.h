#pragma once

#include <string>
#include <vector>

namespace datalint {

// Forward declaration
class RawData;
struct ResolveResult;

/// @brief Interface for resolving application descriptors from raw data.
class IApplicationDescriptorResolver {
 public:
  /// @brief Virtual destructor.
  virtual ~IApplicationDescriptorResolver() = default;

  /// @brief Resolve the application descriptor (name and version) from the given raw data.
  /// @param rawData The raw data from which to resolve the application descriptor.
  /// @return The result of the resolution, including any errors encountered.
  virtual ResolveResult Resolve(const datalint::RawData& rawData) = 0;
};
}  // namespace datalint
