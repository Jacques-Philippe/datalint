#include <datalint/LayoutSpecification/LayoutPatch.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>
#include <datalint/LayoutSpecification/LayoutSpecificationBuilder.h>
#include <datalint/Version/Version.h>
#include <gtest/gtest.h>

#include <array>
#include <map>
#include <span>
#include <string>

/// @brief Tests that the layout specification builder can build a layout specification
TEST(LayoutSpecificationBuilderTest, CanInitializeWithValidFields) {
  // Initialize the layout patch
  const datalint::layout::LayoutPatch layoutPatch{
      .Name = "TestPatch",
      .AppliesTo = datalint::VersionRange::All(),
      .Operations = {datalint::layout::AddField{
          .Key = "Field1", .Field = datalint::layout::ExpectedField{"Field1Key"}}}};

  datalint::layout::LayoutSpecificationBuilder builder;
  datalint::layout::LayoutSpecification spec =
      builder.Build(datalint::Version{1, 0, 0}, std::span(&layoutPatch, 1));

  ASSERT_EQ(spec.Fields().size(), 1);
  ASSERT_TRUE(spec.HasField("Field1"));
  const auto fieldOpt = spec.GetField("Field1");
  ASSERT_TRUE(fieldOpt.has_value());
  ASSERT_EQ(fieldOpt->Key, "Field1Key");
}

/// @brief Tests that the layout specification builder can add and remove a field using patches
TEST(LayoutSpecificationBuilderTest, CanAddAndRemoveFieldUsingPatches) {
  // Initialize the layout patch
  const datalint::layout::LayoutPatch patch1{
      .Name = "patch1",
      .AppliesTo = datalint::VersionRange::All(),
      .Operations = {datalint::layout::AddField{
          .Key = "Field1", .Field = datalint::layout::ExpectedField{"Field1Key"}}}};

  const datalint::layout::LayoutPatch patch2{
      .Name = "patch2",
      .AppliesTo = datalint::VersionRange::All(),
      .Operations = {datalint::layout::RemoveField{.Key = "Field1"}}};

  const std::array<datalint::layout::LayoutPatch, 2> patches{patch1, patch2};

  datalint::layout::LayoutSpecificationBuilder builder;
  datalint::layout::LayoutSpecification spec =
      builder.Build(datalint::Version{1, 0, 0}, std::span(patches));

  ASSERT_EQ(spec.Fields().size(), 0);
  ASSERT_FALSE(spec.HasField("Field1"));
}

/// @brief Tests that the layout specification builder can add and modify a field using patches
TEST(LayoutSpecificationBuilderTest, CanAddAndModifyFieldUsingPatches) {
  // Initialize the layout patch
  const datalint::layout::LayoutPatch patch1{
      .Name = "patch1",
      .AppliesTo = datalint::VersionRange::All(),
      .Operations = {datalint::layout::AddField{
          .Key = "Field1", .Field = datalint::layout::ExpectedField{"Field1Key"}}}};

  const datalint::layout::LayoutPatch patch2{
      .Name = "patch2",
      .AppliesTo = datalint::VersionRange::All(),
      .Operations = {datalint::layout::ModifyField{
          .Key = "Field1",
          .Mutator = [](datalint::layout::ExpectedField& field) { field.Key = "Field2Key"; }}}};

  const std::array<datalint::layout::LayoutPatch, 2> patches{patch1, patch2};

  datalint::layout::LayoutSpecificationBuilder builder;
  datalint::layout::LayoutSpecification spec =
      builder.Build(datalint::Version{1, 0, 0}, std::span(patches));

  ASSERT_EQ(spec.Fields().size(), 1);
  ASSERT_TRUE(spec.HasField("Field1"));
  const auto fieldOpt = spec.GetField("Field1");
  ASSERT_TRUE(fieldOpt.has_value());
  ASSERT_EQ(fieldOpt->Key, "Field2Key");  // the modified key
}

/// @brief Tests that the layout specification builder applies patches only within the version range
TEST(LayoutSpecificationBuilderTest, AppliesPatchesOnlyWithinVersionRange) {
  // Initialize the layout patch
  const datalint::layout::LayoutPatch patch{
      .Name = "patch1",
      .AppliesTo =
          datalint::VersionRange::Between(datalint::Version{2, 0, 0}, datalint::Version{3, 0, 0}),
      .Operations = {datalint::layout::AddField{
          .Key = "Field1", .Field = datalint::layout::ExpectedField{"Field1Key"}}}};

  datalint::layout::LayoutSpecificationBuilder builder;

  // Build for a version outside the range
  datalint::layout::LayoutSpecification spec1 =
      builder.Build(datalint::Version{1, 5, 0}, std::span(&patch, 1));

  ASSERT_EQ(spec1.Fields().size(), 0);
  ASSERT_FALSE(spec1.HasField("Field1"));

  // Build for a version inside the range
  datalint::layout::LayoutSpecification spec2 =
      builder.Build(datalint::Version{2, 5, 0}, std::span(&patch, 1));

  ASSERT_EQ(spec2.Fields().size(), 1);
  ASSERT_TRUE(spec2.HasField("Field1"));
  const auto fieldOpt = spec2.GetField("Field1");
  ASSERT_TRUE(fieldOpt.has_value());
  ASSERT_EQ(fieldOpt->Key, "Field1Key");
}
