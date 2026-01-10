#include <datalint/LayoutSpecification/ExpectedField.h>
#include <gtest/gtest.h>

/// @brief Tests that we can initialize ExpectedField with valid parameters
TEST(ExpectedFieldTests, CanConstructExpectedField) {
  datalint::layout::ExpectedField field{1, std::nullopt};

  ASSERT_EQ(field.MinCount(), 1);
  ASSERT_FALSE(field.MaxCount().has_value());
}

/// @brief Tests that we throw an exception when constructing an ExpectedField with max count less
/// than min count
TEST(ExpectedFieldTests, ThrowsWhenMaxCountLessThanMinCount) {
  EXPECT_THROW((datalint::layout::ExpectedField{5, 3}), std::invalid_argument);
}
