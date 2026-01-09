#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/LayoutPatchOperations.h>
#include <gtest/gtest.h>

#include <map>
#include <string>

/// @brief Tests that the AddField patch operation can initialize with valid fields
TEST(LayoutPatchTest, CanConstructAddFieldOperation) {
  datalint::layout::AddField addFieldOp;
  addFieldOp.Key = "NewField";
  addFieldOp.Field = datalint::layout::ExpectedField{"NewFieldKey"};

  ASSERT_EQ(addFieldOp.Key, "NewField");
  ASSERT_EQ(addFieldOp.Field.Key, "NewFieldKey");
}

/// @brief Tests that the RemoveField patch operation can initialize with valid fields
TEST(LayoutPatchTest, CanConstructRemoveFieldOperation) {
  datalint::layout::RemoveField removeFieldOp;
  removeFieldOp.Key = "NewField";

  ASSERT_EQ(removeFieldOp.Key, "NewField");
}

/// @brief Tests that the ModifyField patch operation can initialize with valid fields
TEST(LayoutPatchTest, CanConstructModifyFieldOperation) {
  datalint::layout::ModifyField modifyFieldOp;
  modifyFieldOp.Key = "NewField";
  modifyFieldOp.Mutator = [](datalint::layout::ExpectedField& field) { field.Required = false; };

  ASSERT_EQ(modifyFieldOp.Key, "NewField");
}
