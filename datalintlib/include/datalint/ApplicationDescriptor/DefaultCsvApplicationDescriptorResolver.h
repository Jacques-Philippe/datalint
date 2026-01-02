#pragma once

#include <datalint/ApplicationDescriptor/IApplicationDescriptorResolver.h>
namespace datalint {

// Forward declarations
struct ResolveResult;
class RawData;

/// @brief Default implementation of IApplicationDescriptorResolver for CSV files. This class exists
/// mostly to demonstrate how this is meant to be used. If you're consuming this library it's likely
/// you want to implement your own resolver.
class DefaultCsvApplicationDescriptorResolver final : public IApplicationDescriptorResolver {
 public:
  /// @brief Resolve the application descriptor (name and version) from the given raw data.
  /// @param rawData The raw data from which to resolve the application descriptor.
  /// @return The resolved ApplicationDescriptor.
  ResolveResult Resolve(const RawData& rawData) override;
};

}  // namespace datalint
