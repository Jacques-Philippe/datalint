#pragma once

#include <datalint/Error/ErrorCollector.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>
#include <datalint/LayoutSpecification/UnexpectedFieldStrictness.h>
#include <datalint/RawData.h>

namespace datalint::layout {

/// @brief Class to validate a layout specification against raw data
class LayoutSpecificationValidator {
 public:
  /// @brief Constructor
  /// @param strictness Whether to treat unexpected fields strictly or permissively
  LayoutSpecificationValidator(UnexpectedFieldStrictness strictness);

  /// @brief Getter for the strictness level
  /// @return the strictness level
  UnexpectedFieldStrictness Strictness() const;

  /// @brief Validate the layout specification against the raw data
  /// @param layoutSpec The layout specification to validate against
  /// @param rawData The raw data to validate
  /// @param errorCollector The error collector to collect validation errors
  /// @return true if the raw data conforms to the layout specification, false otherwise
  bool Validate(const LayoutSpecification& layoutSpec, const datalint::RawData& rawData,
                datalint::error::ErrorCollector& errorCollector);

 private:
  /// @brief The strictness level for unexpected fields
  UnexpectedFieldStrictness Strictness_;
};

}  // namespace datalint::layout
