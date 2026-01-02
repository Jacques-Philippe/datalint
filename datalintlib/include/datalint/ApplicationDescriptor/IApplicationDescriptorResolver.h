#pragma once

#include <string>

namespace datalint {

// Forward declaration
struct ApplicationDescriptor;
class RawData;

class IApplicationDescriptorResolver {
 public:
  /// @brief Virtual destructor.
  virtual ~IApplicationDescriptorResolver() = default;

  /// @brief Resolve the application descriptor (name and version) from the given raw data.
  /// @param rawData The raw data from which to resolve the application descriptor.
  /// @return The resolved ApplicationDescriptor.
  virtual ApplicationDescriptor Resolve(const datalint::RawData& rawData) = 0;
};
}  // namespace datalint
