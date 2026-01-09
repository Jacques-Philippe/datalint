#pragma once

#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/LayoutPatch.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>

#include <map>
#include <optional>
#include <span>
#include <string>

namespace datalint::layout {

/// @brief Class to contain the definition for a layout specification in which we specify the data
class LayoutSpecificationBuilder {
  LayoutSpecification Build(Version version, std::span<const LayoutPatch> patches) const;

 private:
  void ApplyPatch(std::map<std::string, ExpectedField>& fields, const LayoutPatch& patch) const;

  void ApplyOperation(std::map<std::string, ExpectedField>& fields, const AddField& op) const;

  void ApplyOperation(std::map<std::string, ExpectedField>& fields, const ModifyField& op) const;

  void ApplyOperation(std::map<std::string, ExpectedField>& fields, const RemoveField& op) const;
};
}  // namespace datalint::layout
