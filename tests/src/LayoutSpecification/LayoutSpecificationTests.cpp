#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/FieldOrderingConstraint.h>
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
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }

  ASSERT_EQ(layoutSpecification.Fields().size(), 2);
}

/// @brief Tests that the layout specification can find values
TEST(LayoutSpecificationTest, CanGetFields) {
  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field2", datalint::layout::ExpectedField{1, std::nullopt}}};
  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;
  for (const auto& [key, field] : expectedFields) {
    layoutSpecification.AddExpectedField(key, field);
  }

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

/// @brief Tests that the layout specification throws logic error when adding duplicate expected
/// fields
TEST(LayoutSpecificationTest, ThrowsLogicErrorWhenAddingDuplicateExpectedFields) {
  // Create some expected fields
  const std::map<std::string, datalint::layout::ExpectedField> expectedFields = {
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}},
      {"Field1", datalint::layout::ExpectedField{1, std::nullopt}}};
  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;

  // Adding the first field should succeed
  layoutSpecification.AddExpectedField("Field1", expectedFields.at("Field1"));
  // Adding the duplicate field should throw a logic error
  EXPECT_THROW(layoutSpecification.AddExpectedField("Field1", expectedFields.at("Field1")),
               std::logic_error);
}

/// @brief Tests that the layout specification throws logic error when adding duplicate ordering
/// constraints
TEST(LayoutSpecificationTest, ThrowsLogicErrorWhenAddingDuplicateOrderingConstraints) {
  // Create some expected fields
  const datalint::layout::FieldOrderingConstraint constraint1{"FieldA", "FieldB"};
  const datalint::layout::FieldOrderingConstraint constraint2{"FieldA", "FieldB"};
  // Initialize the layout specification
  datalint::layout::LayoutSpecification layoutSpecification;

  // Adding the first ordering constraint should succeed
  layoutSpecification.AddOrderingConstraint(constraint1);
  // Adding the duplicate constraint should throw a logic error
  EXPECT_THROW(layoutSpecification.AddOrderingConstraint(constraint2), std::logic_error);
}
