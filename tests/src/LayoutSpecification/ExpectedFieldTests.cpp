#include <datalint/LayoutSpecification/ExpectedField.h>
#include <gtest/gtest.h>

/// @brief Tests that we can initialize ExpectedField with valid parameters
TEST(ExpectedFieldTests, CanConstructExpectedField) {
  datalint::layout::ExpectedField field{1, std::nullopt};

  ASSERT_EQ(field.MinCount, 1);
  ASSERT_FALSE(field.MaxCount.has_value());
}

/// @brief Tests that we throw an exception when constructing an ExpectedField with max count less
/// than min count
TEST(ExpectedFieldTests, ThrowsWhenMaxCountLessThanMinCount) {
  EXPECT_THROW((datalint::layout::ExpectedField{5, 3}), std::invalid_argument);
}

/// @brief Tests that IsValid returns true for valid ExpectedField
TEST(ExpectedFieldTests, IsValidReturnsTrueForValidField) {
  datalint::layout::ExpectedField field1{2, 5};
  datalint::layout::ExpectedField field2{3, std::nullopt};
  EXPECT_TRUE(field1.IsValid());
  EXPECT_TRUE(field2.IsValid());

  // edge case where minCount == maxCount
  datalint::layout::ExpectedField field3{4, 4};
  EXPECT_TRUE(field3.IsValid());

  // expect false when minCount > maxCount
  datalint::layout::ExpectedField field4;
  field4.MinCount = 6;
  field4.MaxCount = 4;
  EXPECT_FALSE(field4.IsValid());
}
