#pragma once

#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/LayoutPatch.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>
#include <datalint/Version/Version.h>

#include <map>
#include <optional>
#include <span>
#include <string>

namespace datalint::layout {

/// @brief Class to contain the definition for a layout specification in which we specify the data
class LayoutSpecificationBuilder {
 public:
  /// @brief Function to build a layout specification for the given version applying the given
  /// patches
  /// @param version the application version
  /// @param patches the patches to apply
  /// @return build LayoutSpecification
  LayoutSpecification Build(Version version, std::span<const LayoutPatch> patches) const;

 private:
  /// @brief Helper function to apply a patch to the given fields map
  /// @param specification the layout specification to modify
  /// @param patch the patch to apply
  void ApplyPatch(LayoutSpecification& specification, const LayoutPatch& patch) const;

  /// @brief Helper function to apply an AddField operation to the given fields map
  /// @param specification the layout specification to modify
  /// @param op the add field operation to apply
  void ApplyOperation(LayoutSpecification& specification, const AddField& op) const;

  /// @brief Helper function to apply a ModifyField operation to the given fields map
  /// @param specification the layout specification to modify
  /// @param op the modify field operation to apply
  void ApplyOperation(LayoutSpecification& specification, const ModifyField& op) const;

  /// @brief Helper function to apply a RemoveField operation to the given fields map
  /// @param specification the layout specification to modify
  /// @param op the remove field operation to apply
  void ApplyOperation(LayoutSpecification& specification, const RemoveField& op) const;

  /// @brief Helper function to apply a AddFieldOrdering operation to the orderings vector
  /// @param specification the layout specification to modify
  /// @param op the add field ordering operation to apply
  void ApplyOperation(LayoutSpecification& specification, const AddFieldOrdering& op) const;

  /// @brief Helper function to apply a RemoveFieldOrdering operation to the orderings vector
  /// @param specification the layout specification to modify
  /// @param op the remove field ordering operation to apply
  void ApplyOperation(LayoutSpecification& specification, const RemoveFieldOrdering& op) const;
};
}  // namespace datalint::layout
