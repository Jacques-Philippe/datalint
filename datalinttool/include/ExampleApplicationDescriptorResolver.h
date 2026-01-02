#pragma once

#include <datalint/ApplicationDescriptor/IApplicationDescriptorResolver.h>

/// @brief Example implementation of IApplicationDescriptorResolver.
class ExampleApplicationDescriptorResolver : public datalint::IApplicationDescriptorResolver {
 public:
  /// @brief Resolve the application descriptor (name and version) from the given raw data.
  /// @param rawData The raw data from which to resolve the application descriptor.
  /// @return The resolved ApplicationDescriptor.
  datalint::ResolveResult Resolve(const datalint::RawData& rawData) override;
};
