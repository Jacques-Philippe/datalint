#pragma once

#include <datalint/RuleSpecification/RulePatch.h>
#include <datalint/RuleSpecification/RuleSpecification.h>
#include <datalint/Version/Version.h>
#include <datalint/Version/VersionRange.h>

namespace datalint::rules {
class RuleSpecificationBuilder {
 public:
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
