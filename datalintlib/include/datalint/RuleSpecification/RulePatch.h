#pragma once

#include <datalint/RuleSpecification/IRulePatchOperation.h>
#include <datalint/Version/VersionRange.h>

#include <memory>
#include <string>
#include <vector>

namespace datalint::rules {
/// @brief Class defining the structure for a versioned patch to our rules structure
class RulePatch {
 public:
  /// @brief Constructor
  /// @param name the name of the patch
  /// @param appliesTo the range of versions the patch applies to
  /// @param operations the patch operations to perform on the rules
  RulePatch(std::string name, VersionRange appliesTo,
            std::vector<std::unique_ptr<IRulePatchOperation>> operations)
      : Name_(std::move(name)),
        AppliesTo_(std::move(appliesTo)),
        Operations_(std::move(operations)) {}

  // Delete copy constructor/assignment explicitly to avoid confusion
  RulePatch(const RulePatch&) = delete;
  RulePatch& operator=(const RulePatch&) = delete;

  // Default move constructor/assignment
  RulePatch(RulePatch&&) = default;
  RulePatch& operator=(RulePatch&&) = default;

  /// @brief Getter for the patch name
  /// @return the name of the patch
  const std::string& Name() const { return Name_; }
  /// @brief Getter for the version range the patch applies to
  /// @return the version range the patch applies to
  VersionRange AppliesTo() const { return AppliesTo_; }
  /// @brief Getter for the operations contained in the patch
  /// @return the operations contained in the patch
  const std::vector<std::unique_ptr<IRulePatchOperation>>& Operations() const {
    return Operations_;
  }

  /// @brief Apply the rule patch operations associated to this patch to the rules
  /// @param rules the rules to modify
  void Apply(std::vector<FieldRule>& rules) const {
    for (const auto& op : Operations_) {
      op->Apply(rules);
    }
  }

 private:
  /// @brief The patch's name
  std::string Name_;
  /// @brief The version range the patch applies to
  VersionRange AppliesTo_;
  /// @brief the operations contained in the patch
  std::vector<std::unique_ptr<IRulePatchOperation>> Operations_;
};
}  // namespace datalint::rules
