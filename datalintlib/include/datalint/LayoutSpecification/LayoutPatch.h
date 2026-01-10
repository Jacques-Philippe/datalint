#pragma once

#include <datalint/LayoutSpecification/LayoutPatchOperations.h>
#include <datalint/Version/VersionRange.h>

#include <string>
#include <vector>

namespace datalint::layout {
/// @brief Class to represent a layout patch, which can modify a layout specification for certain
/// versions
class LayoutPatch {
 public:
  /// @brief Constructor: must provide all members
  /// @param name The name of the layout patch
  /// @param appliesTo The version range to which this patch applies
  /// @param operations The list of operations that this patch performs
  /// @throws std::invalid_argument if name is empty
  LayoutPatch(std::string name, VersionRange appliesTo,
              std::vector<LayoutPatchOperation> operations)
      : Name_(std::move(name)),
        AppliesTo_(std::move(appliesTo)),
        Operations_(std::move(operations)) {
    if (Name_.empty()) {
      throw std::invalid_argument("LayoutPatch name cannot be empty");
    }
  }

  /// @brief Name getter
  /// @return The patch name
  const std::string& Name() const { return Name_; }
  /// @brief AppliesTo getter
  /// @return The version range to which this patch applies
  const VersionRange& AppliesTo() const { return AppliesTo_; }
  /// @brief Operations getter
  /// @return The list of operations that this patch performs
  const std::vector<LayoutPatchOperation>& Operations() const { return Operations_; }

 private:
  /// @brief The name of the layout patch
  const std::string Name_;
  /// @brief The version range to which this patch applies
  const VersionRange AppliesTo_;
  /// @brief The list of operations that this patch performs
  const std::vector<LayoutPatchOperation> Operations_;
};

}  // namespace datalint::layout
