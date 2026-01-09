#pragma once

#include <datalint/LayoutSpecification/LayoutPatchOperations.h>
#include <datalint/Version/VersionRange.h>

#include <string>
#include <vector>

namespace datalint::layout {
/// @brief Struct to contain a patch to be applied to a layout specification
struct LayoutPatch {
  /// @brief The name of the patch
  std::string Name;
  /// @brief The version range in which this patch applies
  VersionRange AppliesTo;
  /// @brief The operations that make up this patch
  std::vector<LayoutPatchOperation> Operations;
};
}  // namespace datalint::layout
