#pragma once

#include <datalint/RuleSpecification/RulePatch.h>
#include <datalint/RuleSpecification/RuleSpecification.h>
#include <datalint/Version/Version.h>
#include <datalint/Version/VersionRange.h>

namespace datalint::rules {
/// @brief Class responsible for building rule specifications
class RuleSpecificationBuilder {
 public:
  /// @brief Buil function to produce our rule specification given the incoming version and a set of
  /// patches marked by version ranges
  /// @param version the version for which we should build our rule specification
  /// @param patches the set of all patches to apply to our finalized rule specification
  /// @return the final built rule specification
  RuleSpecification Build(const datalint::Version& version,
                          const std::vector<RulePatch>& patches) const {
    std::vector<FieldRule> rules;

    for (const auto& patch : patches) {
      if (!patch.AppliesTo().Contains(version)) {
        continue;
      }

      patch.Apply(rules);
    }

    return RuleSpecification(std::move(rules));
  }
};
}  // namespace datalint::rules
