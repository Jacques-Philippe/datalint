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
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }

  // Validate the layout specification against the raw data
  const bool isValid = validator.Validate(layoutSpecification, rawData, errorCollector);
  ASSERT_TRUE(isValid);
  ASSERT_TRUE(errorCollector.GetErrorLogs().empty());
}

/// @brief Tests that the layout specification validator detects missing required fields
TEST(LayoutSpecificationValidatorTest, DetectsMissingRequiredFields) {
  datalint::error::ErrorCollector errorCollector;
  datalint::layout::LayoutSpecificationValidator validator{
      datalint::layout::UnexpectedFieldStrictness::Strict};

  // Create some raw data with fields
  const datalint::RawData rawData({
      datalint::RawField{"Field1", "Value1, Value2, Value3"},
  });

  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};

  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }

  // Validate the layout specification against the raw data
  const bool isValid = validator.Validate(layoutSpecification, rawData, errorCollector);
  ASSERT_FALSE(isValid);
  const auto errorLogs = errorCollector.GetErrorLogs();
  ASSERT_EQ(errorLogs.size(), 1);
  ASSERT_EQ(errorLogs[0].Subject(), "Missing Required Field");
  ASSERT_NE(errorLogs[0].Body().find("Field2"), std::string::npos);
}

/// @brief Tests that the layout specification validator detects extra (too many) occurrences of
/// fields
TEST(LayoutSpecificationValidatorTest, DetectsTooManyFieldOccurrences) {
  datalint::error::ErrorCollector errorCollector;
  datalint::layout::LayoutSpecificationValidator validator{
      datalint::layout::UnexpectedFieldStrictness::Strict};

  // Create some raw data with fields
  const datalint::RawData rawData({
      datalint::RawField{"Field1", "Value1"},
      datalint::RawField{"Field1", "Value2"},
      datalint::RawField{"Field2", "ValueA"},
  });

  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, 1}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};

  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }

  // Validate the layout specification against the raw data
  const bool isValid = validator.Validate(layoutSpecification, rawData, errorCollector);
  ASSERT_FALSE(isValid);
  const auto errorLogs = errorCollector.GetErrorLogs();
  ASSERT_EQ(errorLogs.size(), 1);
  ASSERT_EQ(errorLogs[0].Subject(), "Duplicate Field");
  ASSERT_NE(errorLogs[0].Body().find("Field1"), std::string::npos);
}

/// @brief Tests that the layout specification validator detects unexpected fields when in strict
/// mode
TEST(LayoutSpecificationValidatorTest, DetectsUnexpectedFieldsInStrictMode) {
  datalint::error::ErrorCollector errorCollector;
  datalint::layout::LayoutSpecificationValidator validator{
      datalint::layout::UnexpectedFieldStrictness::Strict};

  // Create some raw data with fields
  const datalint::RawData rawData({
      datalint::RawField{"Field1", "Value1"},
      datalint::RawField{"Field2", "ValueA"},
      datalint::RawField{"UnexpectedField", "Surprise!"},
  });

  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};

  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }

  // Validate the layout specification against the raw data
  const bool isValid = validator.Validate(layoutSpecification, rawData, errorCollector);
  ASSERT_FALSE(isValid);
  const auto errorLogs = errorCollector.GetErrorLogs();
  ASSERT_EQ(errorLogs.size(), 1);
  ASSERT_EQ(errorLogs[0].Subject(), "Unexpected Field");
  ASSERT_NE(errorLogs[0].Body().find("UnexpectedField"), std::string::npos);
}

/// @brief Tests that the layout specification validator will not detect unexpected fields when in
/// permissive mode
TEST(LayoutSpecificationValidatorTest, IgnoresUnexpectedFieldsInPermissiveMode) {
  datalint::error::ErrorCollector errorCollector;
  datalint::layout::LayoutSpecificationValidator validator{
      datalint::layout::UnexpectedFieldStrictness::Permissive};

  // Create some raw data with fields
  const datalint::RawData rawData({
      datalint::RawField{"Field1", "Value1"},
      datalint::RawField{"Field2", "ValueA"},
      datalint::RawField{"UnexpectedField", "Surprise!"},
  });

  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};

  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }

  // Validate the layout specification against the raw data
  const bool isValid = validator.Validate(layoutSpecification, rawData, errorCollector);
  ASSERT_TRUE(isValid);
  ASSERT_TRUE(errorCollector.GetErrorLogs().empty());
}

/// @brief Tests that the layout specification validator detects ordering violations
TEST(LayoutSpecificationValidatorTest, DetectsOrderingViolations) {
  datalint::error::ErrorCollector errorCollector;
  datalint::layout::LayoutSpecificationValidator validator{
      datalint::layout::UnexpectedFieldStrictness::Strict};
  // Create some raw data with fields
  const datalint::RawData rawData({
      datalint::RawField{"Field2", "ValueA"},
      datalint::RawField{"Field1", "Value1"},
  });
  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};
  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }
  // Add ordering constraint: All occurrences of Field1 must come before any occurrence of Field2
  layoutSpecification.AddOrderingConstraint(
      datalint::layout::FieldOrderingConstraint{"Field1", "Field2"});
  // Validate the layout specification against the raw data
  const bool isValid = validator.Validate(layoutSpecification, rawData, errorCollector);
  ASSERT_FALSE(isValid);
  const auto errorLogs = errorCollector.GetErrorLogs();
  ASSERT_EQ(errorLogs.size(), 1);
  ASSERT_EQ(errorLogs[0].Subject(), "Field Ordering Violation");
  ASSERT_NE(errorLogs[0].Body().find("Field1"), std::string::npos);
  ASSERT_NE(errorLogs[0].Body().find("Field2"), std::string::npos);
}

/// @brief Tests that the layout specification validator detects ordering violations for multiple
/// occurrences of fields
TEST(LayoutSpecificationValidatorTest, DetectsMultipleOrderingViolations) {
  datalint::error::ErrorCollector errorCollector;
  datalint::layout::LayoutSpecificationValidator validator{
      datalint::layout::UnexpectedFieldStrictness::Strict};
  // Create some raw data with fields
  const datalint::RawData rawData({
      datalint::RawField{"Field2", "ValueA"},
      datalint::RawField{"Field1", "Value1"},
      datalint::RawField{"Field2", "ValueB"},
  });
  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};
  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }
  // Add ordering constraint: All occurrences of Field2 must come before any occurrence of Field1
  layoutSpecification.AddOrderingConstraint(
      datalint::layout::FieldOrderingConstraint{"Field2", "Field1"});
  // Validate the layout specification against the raw data
  const bool isValid = validator.Validate(layoutSpecification, rawData, errorCollector);
  ASSERT_FALSE(isValid);
  const auto errorLogs = errorCollector.GetErrorLogs();
  ASSERT_EQ(errorLogs.size(), 1);
  ASSERT_EQ(errorLogs[0].Subject(), "Field Ordering Violation");
  ASSERT_NE(errorLogs[0].Body().find("Field1"), std::string::npos);
  ASSERT_NE(errorLogs[0].Body().find("Field2"), std::string::npos);
}
