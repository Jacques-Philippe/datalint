#include <datalint/Error/ErrorCollector.h>
#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>
#include <datalint/LayoutSpecification/LayoutSpecificationValidator.h>
#include <datalint/LayoutSpecification/UnexpectedFieldStrictness.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>
#include <gtest/gtest.h>

#include <map>
#include <string>

/// @brief Tests that the layout specification validator can initialize with strictness
TEST(LayoutSpecificationValidatorTest, CanInitializeWithStrictness) {
  datalint::layout::LayoutSpecificationValidator validator{
      datalint::layout::UnexpectedFieldStrictness::Strict};
  ASSERT_EQ(validator.Strictness(), datalint::layout::UnexpectedFieldStrictness::Strict);
}

/// @brief Tests that the layout specification validator can validate a layout specification against
/// raw data.
TEST(LayoutSpecificationValidatorTest, CanInitializeWithValidFields) {
  datalint::error::ErrorCollector errorCollector;
  datalint::layout::LayoutSpecificationValidator validator{
      datalint::layout::UnexpectedFieldStrictness::Strict};

  // Create some raw data with fields
  const datalint::RawData rawData({
      datalint::RawField{"Field1", "Value1, Value2, Value3"},
      datalint::RawField{"Field2", "ValueA, ValueB, ValueC"},
      datalint::RawField{"Field3", "ValueX, ValueY, ValueZ"},
  });

  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field3", datalint::layout::ExpectedField{1, std::nullopt}}};

  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification(expectedFields);

  // Validate the layout specification against the raw data
  const bool isValid = validator.Validate(layoutSpecification, rawData, errorCollector);
  ASSERT_TRUE(isValid);
  ASSERT_TRUE(errorCollector.GetErrorLogs().empty());
}
