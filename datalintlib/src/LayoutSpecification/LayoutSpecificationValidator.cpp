
#include <datalint/Error/ErrorLog.h>
#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/FieldOrderingConstraint.h>
#include <datalint/LayoutSpecification/LayoutSpecificationValidator.h>
#include <datalint/RawField.h>

namespace datalint::layout {

LayoutSpecificationValidator::LayoutSpecificationValidator(UnexpectedFieldStrictness strictness)
    : Strictness_(strictness) {}

UnexpectedFieldStrictness LayoutSpecificationValidator::Strictness() const {
  return Strictness_;
}

bool LayoutSpecificationValidator::Validate(const LayoutSpecification& layoutSpec,
                                            const datalint::RawData& rawData,
                                            datalint::error::ErrorCollector& errorCollector) {
  // 1. Validate expected fields
  for (const auto& [key, expectedField] : layoutSpec.Fields()) {
    auto matches = rawData.GetFieldsByKey(key);

    if (matches.empty()) {
      if (expectedField.MinCount() > 0) {
        errorCollector.AddErrorLog(datalint::error::ErrorLog(
            "Missing Required Field", "Expected at least " +
                                          std::to_string(expectedField.MinCount()) +
                                          " occurrence(s) of field: " + key));
      }
      continue;
    }

    if (expectedField.MaxCount() && matches.size() > *expectedField.MaxCount()) {
      errorCollector.AddErrorLog(datalint::error::ErrorLog(
          "Duplicate Field", "Expected at most " + std::to_string(*expectedField.MaxCount()) +
                                 " occurrence(s) of field: " + key));
    }
  }

  // 2. Detect unexpected fields (strictness-dependent)
  if (Strictness_ == UnexpectedFieldStrictness::Strict) {
    for (const auto& field : rawData.Fields()) {
      const std::string& key = field.Key;

      if (!layoutSpec.HasField(key)) {
        errorCollector.AddErrorLog(datalint::error::ErrorLog(
            "Unexpected Field", "Field is not defined in layout specification: " + key));
      }
    }
  }

  // 3. Validate ordering constraints
  for (const auto& constraint : layoutSpec.OrderingConstraints()) {
    const auto& beforeKey = constraint.BeforeKey;
    const auto& afterKey = constraint.AfterKey;

    std::optional<std::size_t> lastBeforeIndex;
    std::optional<std::size_t> firstAfterIndex;

    const auto& fields = rawData.Fields();

    for (std::size_t i = 0; i < fields.size(); ++i) {
      if (fields[i].Key == beforeKey) {
        lastBeforeIndex = i;
      }
      if (fields[i].Key == afterKey && !firstAfterIndex) {
        firstAfterIndex = i;
      }
    }

    // If one or both fields don't exist, skip — presence rules handle that
    if (!lastBeforeIndex || !firstAfterIndex) {
      continue;
    }

    if (*lastBeforeIndex > *firstAfterIndex) {
      errorCollector.AddErrorLog(datalint::error::ErrorLog(
          "Field Ordering Violation", "All occurrences of field '" + beforeKey +
                                          "' must precede any occurrence of field '" + afterKey +
                                          "'"));
    }
  }

  return !errorCollector.HasErrors();
}

}  // namespace datalint::layout
