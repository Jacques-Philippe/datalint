#include <datalint/RuleSpecification/AllValuesSelector.h>
#include <gtest/gtest.h>

/// @brief Tests that we can select all values from a parsed field
TEST(AllValuesSelectorTest, CanSelectAllValues) {
  datalint::fieldparser::ParsedField parsedField;
  parsedField.Key = "TestKey";
  parsedField.Values = {
      {"Value1", {"file.txt", 1}},
      {"Value2", {"file.txt", 2}},
      {"Value3", {"file.txt", 3}},
  };
  datalint::rules::AllValuesSelector selector;
  auto selectedValues = selector.Select(parsedField);

  ASSERT_EQ(selectedValues.size(), 3u);
  ASSERT_NE(selectedValues[0], nullptr);
  EXPECT_EQ(selectedValues[0]->Value, "Value1");
  EXPECT_EQ(selectedValues[0]->Location.Filename, "file.txt");
  EXPECT_EQ(selectedValues[0]->Location.Line, 1);
  ASSERT_NE(selectedValues[1], nullptr);
  EXPECT_EQ(selectedValues[1]->Value, "Value2");
  EXPECT_EQ(selectedValues[1]->Location.Filename, "file.txt");
  EXPECT_EQ(selectedValues[1]->Location.Line, 2);
  ASSERT_NE(selectedValues[2], nullptr);
  EXPECT_EQ(selectedValues[2]->Value, "Value3");
  EXPECT_EQ(selectedValues[2]->Location.Filename, "file.txt");
  EXPECT_EQ(selectedValues[2]->Location.Line, 3);
}
