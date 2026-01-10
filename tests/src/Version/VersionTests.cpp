#include <datalint/Version/Version.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

/// @brief Tests that the version can be created properly
TEST(VersionTest, CanInitializeWithValidFields) {
  const datalint::Version v{1, 2, 3};

  EXPECT_EQ(v.Major(), 1);
  EXPECT_EQ(v.Minor(), 2);
  EXPECT_EQ(v.Patch(), 3);
}

/// @brief Tests that versions with the same components are equal
TEST(VersionTest, VersionsWithSameComponentsAreEqual) {
  datalint::Version a{1, 2, 3};
  datalint::Version b{1, 2, 3};

  EXPECT_EQ(a, b);
  EXPECT_FALSE(a < b);
  EXPECT_FALSE(a > b);
}

/// @brief Tests that major version takes precedence when performing comparison
TEST(VersionTest, MajorVersionDominatesComparison) {
  datalint::Version lower{1, 9, 9};
  datalint::Version higher{2, 0, 0};

  EXPECT_LT(lower, higher);
  EXPECT_GT(higher, lower);
}

/// @brief Tests that minor version is compared when the major versions are equal
TEST(VersionTest, MinorVersionComparedWhenMajorEqual) {
  datalint::Version lower{1, 1, 9};
  datalint::Version higher{1, 2, 0};

  EXPECT_LT(lower, higher);
  EXPECT_GT(higher, lower);
}

/// @brief Tests that for major and minor version equal the patch version is compared
TEST(VersionTest, PatchVersionComparedWhenMajorAndMinorEqual) {
  datalint::Version lower{1, 2, 3};
  datalint::Version higher{1, 2, 4};

  EXPECT_LT(lower, higher);
  EXPECT_GT(higher, lower);
}

/// Ensures zero is the lowest possible version
TEST(VersionTest, ZeroVersionIsLowestPossibleVersion) {
  datalint::Version zero{0, 0, 0};
  datalint::Version nonZero{0, 0, 1};

  EXPECT_LT(zero, nonZero);
}

/// @brief Ensures that for mixed components of major and minor versions, comparison still works as
/// expected
TEST(VersionTest, MixedComponentComparisonWorksCorrectly) {
  EXPECT_LT((datalint::Version{1, 9, 9}), (datalint::Version{2, 0, 0}));
  EXPECT_LT((datalint::Version{1, 2, 9}), (datalint::Version{1, 3, 0}));
  EXPECT_LT((datalint::Version{1, 2, 3}), (datalint::Version{1, 2, 10}));
}

/// @brief Tests that reflexive and symmetric comparison work as expected
TEST(VersionTest, ComparisonIsReflexiveAndSymmetric) {
  datalint::Version v{3, 4, 5};

  EXPECT_EQ(v, v);
  EXPECT_LE(v, v);
  EXPECT_GE(v, v);
}

/// @brief Test that sort works properly
TEST(VersionTest, VersionsSortCorrectly) {
  std::vector<datalint::Version> versions = {
      {2, 0, 0}, {1, 10, 0}, {1, 2, 3}, {1, 2, 10}, {1, 2, 0}};

  std::sort(versions.begin(), versions.end());

  EXPECT_EQ(versions[0], (datalint::Version{1, 2, 0}));
  EXPECT_EQ(versions[1], (datalint::Version{1, 2, 3}));
  EXPECT_EQ(versions[2], (datalint::Version{1, 2, 10}));
  EXPECT_EQ(versions[3], (datalint::Version{1, 10, 0}));
  EXPECT_EQ(versions[4], (datalint::Version{2, 0, 0}));
}

/// @brief Test that parse works properly
TEST(VersionTest, ParseWorksCorrectly) {
  datalint::Version v = datalint::Version::Parse("1.2.3");

  EXPECT_EQ(v, (datalint::Version{1, 2, 3}));
}

/// @brief Tests that parsing a version with two components throws an exception
TEST(VersionTest, ParseThrowsForTwoComponentVersion) {
  EXPECT_THROW(datalint::Version::Parse("1.2"), std::invalid_argument);
}

/// @brief Tests that parsing an invalid version format throws an exception
TEST(VersionTest, ParseThrowsForInvalidFormat) {
  EXPECT_THROW(datalint::Version::Parse("1.2.3.4"), std::invalid_argument);
  EXPECT_THROW(datalint::Version::Parse("abc"), std::invalid_argument);
  EXPECT_THROW(datalint::Version::Parse(""), std::invalid_argument);
}

/// @brief Tests that parsing leading zeros works correctly
TEST(VersionTest, ParseHandlesLeadingZerosCorrectly) {
  datalint::Version v = datalint::Version::Parse("01.02.03");
  EXPECT_EQ(v, (datalint::Version{1, 2, 3}));
}

/// @brief Tests that parsing whitespace throws an exception
TEST(VersionTest, ParseThrowsForWhitespace) {
  EXPECT_THROW(datalint::Version::Parse(" 1.2.3 "), std::invalid_argument);
}

/// @brief Tests that parsing negative version components throws an exception
TEST(VersionTest, ConstructorThrowsForNegativeComponents) {
  EXPECT_THROW(datalint::Version(-1, 2, 3), std::invalid_argument);
  EXPECT_THROW(datalint::Version(1, -2, 3), std::invalid_argument);
  EXPECT_THROW(datalint::Version(1, 2, -3), std::invalid_argument);
}

/// @brief Tests that parsing negative version components throws an exception
TEST(VersionTest, ParseThrowsForNegativeComponents) {
  EXPECT_THROW(datalint::Version::Parse("-1.2.3"), std::invalid_argument);
  EXPECT_THROW(datalint::Version::Parse("1.-2.3"), std::invalid_argument);
  EXPECT_THROW(datalint::Version::Parse("1.2.-3"), std::invalid_argument);
}
