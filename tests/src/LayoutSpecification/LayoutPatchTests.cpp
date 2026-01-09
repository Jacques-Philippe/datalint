#include <datalint/LayoutSpecification/LayoutPatch.h>
#include <gtest/gtest.h>

#include <map>
#include <string>

/// @brief Tests that the layout patch can initialize with valid fields
TEST(LayoutPatchTest, CanInitializeWithValidFields) {
  // Initialize the layout patch
  datalint::layout::LayoutPatch layoutPatch{
      .Name = "TestPatch",
      .AppliesTo =
          datalint::VersionRange::Between(datalint::Version{1, 0, 0}, datalint::Version{2, 0, 0}),
      .Operations = {datalint::layout::AddField{
          .Key = "Field1", .Field = datalint::layout::ExpectedField{1, std::nullopt}}}};

  ASSERT_EQ(layoutPatch.Name, "TestPatch");
  ASSERT_TRUE(layoutPatch.AppliesTo.Min.has_value());
  ASSERT_TRUE(layoutPatch.AppliesTo.Min->Major == 1);
  ASSERT_TRUE(layoutPatch.AppliesTo.Min->Minor == 0);
  ASSERT_TRUE(layoutPatch.AppliesTo.Min->Patch == 0);
  ASSERT_TRUE(layoutPatch.AppliesTo.Max.has_value());
  ASSERT_TRUE(layoutPatch.AppliesTo.Max->Major == 2);
  ASSERT_TRUE(layoutPatch.AppliesTo.Max->Minor == 0);
  ASSERT_TRUE(layoutPatch.AppliesTo.Max->Patch == 0);
  ASSERT_EQ(layoutPatch.Operations.size(), 1);
  const auto& addFieldOp = std::get<datalint::layout::AddField>(layoutPatch.Operations[0]);
  ASSERT_EQ(addFieldOp.Key, "Field1");
  ASSERT_EQ(addFieldOp.Field.MinCount, 1);
  ASSERT_FALSE(addFieldOp.Field.MaxCount.has_value());
}

/// @brief Tests that the layout patch can initialize with multiple valid patch operations
TEST(LayoutPatchTest, CanInitializeWithMultiplePatchOperations) {
  // Initialize the layout patch
  datalint::layout::LayoutPatch layoutPatch{
      .Name = "TestPatch",
      .AppliesTo =
          datalint::VersionRange::Between(datalint::Version{1, 0, 0}, datalint::Version{2, 0, 0}),
      .Operations = {
          datalint::layout::AddField{.Key = "Field1",
                                     .Field = datalint::layout::ExpectedField{1, std::nullopt}},
          datalint::layout::RemoveField{.Key = "Field2"},
          datalint::layout::ModifyField{
              .Key = "Field1",
              .Mutator = [](datalint::layout::ExpectedField& field) { field.MinCount = 2; }}}};

  ASSERT_EQ(layoutPatch.Operations.size(), 3);
  const auto& addFieldOp = std::get<datalint::layout::AddField>(layoutPatch.Operations[0]);
  ASSERT_EQ(addFieldOp.Key, "Field1");
  ASSERT_EQ(addFieldOp.Field.MinCount, 1);
  ASSERT_FALSE(addFieldOp.Field.MaxCount.has_value());
  const auto& removeFieldOp = std::get<datalint::layout::RemoveField>(layoutPatch.Operations[1]);
  ASSERT_EQ(removeFieldOp.Key, "Field2");
  const auto& modifyFieldOp = std::get<datalint::layout::ModifyField>(layoutPatch.Operations[2]);
  ASSERT_EQ(modifyFieldOp.Key, "Field1");
}
