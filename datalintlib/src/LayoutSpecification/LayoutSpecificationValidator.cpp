
#include <datalint/Error/ErrorLog.h>
#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/LayoutSpecificationValidator.h>
#include <datalint/RawField.h>

namespace datalint::layout {

LayoutSpecificationValidator::LayoutSpecificationValidator(UnexpectedFieldStrictness strictness)
    : Strictness_(strictness) {};

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

    if (matches.size() > expectedField.MaxCount().value_or(SIZE_MAX)) {
      errorCollector.AddErrorLog(datalint::error::ErrorLog(
          "Duplicate Field", "Expected at most " +
                                 std::to_string(expectedField.MaxCount().value_or(SIZE_MAX)) +
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

  return errorCollector.GetErrorLogs().empty();
}

}  // namespace datalint::layout
