#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>
#include <gtest/gtest.h>

#include <map>
#include <string>

/// @brief Tests that the layout specification can initialize with valid fields
TEST(LayoutSpecificationTest, CanInitializeWithValidFields) {
  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};
  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification(expectedFields);

  ASSERT_EQ(layoutSpecification.Fields().size(), 2);
}

/// @brief Tests that the layout specification can find values
TEST(LayoutSpecificationTest, CanGetFields) {
  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};
  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification(expectedFields);

  // We should be able to find the field
  EXPECT_TRUE(layoutSpecification.HasField("Field1"));
  EXPECT_TRUE(layoutSpecification.HasField("Field2"));
  EXPECT_FALSE(layoutSpecification.HasField("Field3"));

  // We should be able to get the field
  const auto field1 = layoutSpecification.GetField("Field1");
  EXPECT_TRUE(field1.has_value());
  EXPECT_EQ(field1->MinCount(), 1);
  EXPECT_EQ(field1->MaxCount(), std::nullopt);

  const auto field3 = layoutSpecification.GetField("Field3");
  EXPECT_FALSE(field3.has_value());
}
