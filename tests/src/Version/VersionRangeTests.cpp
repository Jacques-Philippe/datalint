#include <datalint/Version/Version.h>
#include <datalint/Version/VersionRange.h>
#include <gtest/gtest.h>

#include <map>
#include <string>
#include <vector>

/// @brief Tests that the version range can be created properly
TEST(VersionRangeTest, CanInitializeWithValidFields) {
  const datalint::Version v1{1, 0, 0};
  const datalint::Version v2{2, 0, 0};
  const datalint::VersionRange range{v1, v2};

  EXPECT_TRUE(range.Min.has_value());
  EXPECT_TRUE(range.Max.has_value());
  EXPECT_EQ(range.Min->Major, 1);
  EXPECT_EQ(range.Min->Minor, 0);
  EXPECT_EQ(range.Min->Patch, 0);
  EXPECT_EQ(range.Max->Major, 2);
  EXPECT_EQ(range.Max->Minor, 0);
  EXPECT_EQ(range.Max->Patch, 0);
}

/// @brief Tests that the static All method works as expected
TEST(VersionRangeTest, AllWorksAsExpected) {
  // All should return a range with no min and no max
  EXPECT_TRUE(datalint::VersionRange::All().Min == std::nullopt);
  EXPECT_TRUE(datalint::VersionRange::All().Max == std::nullopt);

  // Any version should be contained within the range defined by All
  const datalint::Version v1{1, 0, 0};

  EXPECT_TRUE(datalint::VersionRange::All().Contains(v1));
}

/// @brief Tests that the static From method works as expected
TEST(VersionRangeTest, FromWorksAsExpected) {
  // From should return a range with min set to the input and max set to nullopt
  const datalint::Version v1{2, 3, 4};
  EXPECT_TRUE(datalint::VersionRange::From(v1).Min == v1);
  EXPECT_TRUE(datalint::VersionRange::From(v1).Max == std::nullopt);

  // Any version after or equal to min should be contained within the range
  EXPECT_TRUE(datalint::VersionRange::From(v1).Contains(v1));
  EXPECT_TRUE(datalint::VersionRange::From(v1).Contains(datalint::Version{2, 3, 5}));  // bump patch
  EXPECT_TRUE(datalint::VersionRange::From(v1).Contains(datalint::Version{2, 4, 0}));  // bump minor
  EXPECT_TRUE(datalint::VersionRange::From(v1).Contains(datalint::Version{3, 0, 0}));  // bump major

  // Any version before min should not be contained within the range
  EXPECT_FALSE(
      datalint::VersionRange::From(v1).Contains(datalint::Version{1, 0, 0}));  // bump major
  EXPECT_FALSE(
      datalint::VersionRange::From(v1).Contains(datalint::Version{2, 2, 0}));  // bump minor
  EXPECT_FALSE(
      datalint::VersionRange::From(v1).Contains(datalint::Version{2, 3, 3}));  // bump patch
}

/// @brief Tests that the static Until method works as expected
TEST(VersionRangeTest, UntilWorksAsExpected) {
  // Until should return a range with min set to nullopt and max set to the input
  const datalint::Version v2{2, 3, 4};
  EXPECT_TRUE(datalint::VersionRange::Until(v2).Min == std::nullopt);
  EXPECT_TRUE(datalint::VersionRange::Until(v2).Max == v2);

  // Any version before or equal to max should be contained within the range
  EXPECT_TRUE(datalint::VersionRange::Until(v2).Contains(v2));
  EXPECT_TRUE(
      datalint::VersionRange::Until(v2).Contains(datalint::Version{1, 3, 4}));  // bump major
  EXPECT_TRUE(
      datalint::VersionRange::Until(v2).Contains(datalint::Version{2, 2, 0}));  // bump minor
  EXPECT_TRUE(
      datalint::VersionRange::Until(v2).Contains(datalint::Version{2, 3, 3}));  // bump patch

  // Any version greater than max should be excluded from the range
  EXPECT_FALSE(
      datalint::VersionRange::Until(v2).Contains(datalint::Version{3, 0, 0}));  // bump major
  EXPECT_FALSE(
      datalint::VersionRange::Until(v2).Contains(datalint::Version{2, 4, 0}));  // bump minor
  EXPECT_FALSE(
      datalint::VersionRange::Until(v2).Contains(datalint::Version{2, 3, 5}));  // bump patch
}

/// @brief Tests that the static Between method works as expected
TEST(VersionRangeTest, BetweenWorksAsExpected) {
  // Between should return a range with min and max set to the inputs
  const datalint::Version v1{1, 2, 3};
  const datalint::Version v2{4, 5, 6};
  EXPECT_TRUE(datalint::VersionRange::Between(v1, v2).Min == v1);
  EXPECT_TRUE(datalint::VersionRange::Between(v1, v2).Max == v2);

  // Any version between min and max should be contained within the range, inclusive
  EXPECT_TRUE(datalint::VersionRange::Between(v1, v2).Contains(v1));
  EXPECT_TRUE(datalint::VersionRange::Between(v1, v2).Contains(v2));
  // A version right after min should be accepted in the range
  EXPECT_TRUE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{1, 2, 4}));  // patch
  EXPECT_TRUE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{1, 3, 0}));  // minor
  EXPECT_TRUE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{2, 0, 0}));  // major

  EXPECT_TRUE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{4, 5, 6}));  // patch
  EXPECT_TRUE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{4, 4, 0}));  // minor
  EXPECT_TRUE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{3, 0, 0}));  // major

  // Any version before min should be excluded from the range
  EXPECT_FALSE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{1, 2, 2}));  // patch
  EXPECT_FALSE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{1, 1, 0}));  // minor
  EXPECT_FALSE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{0, 0, 1}));  // major
  // Any version after max should be excluded from the range
  EXPECT_FALSE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{4, 5, 7}));  // patch
  EXPECT_FALSE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{4, 6, 0}));  // minor
  EXPECT_FALSE(
      datalint::VersionRange::Between(v1, v2).Contains(datalint::Version{5, 0, 0}));  // major
}
