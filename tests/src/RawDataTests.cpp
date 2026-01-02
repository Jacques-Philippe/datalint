#include <datalint/RawData.h>
#include <datalint/RawField.h>
#include <gtest/gtest.h>

#include <vector>

/// @brief Tests that RawData can be initialized with a vector of RawField objects.
TEST(RawDataTest, CanInitializeWithFields) {
  const auto fields = std::vector<datalint::RawField>{
      {"key1", "value1"},
      {"key2", "value2"},
      {"key1", "value3"},
  };

  const datalint::RawData rawData(fields);

  ASSERT_EQ(rawData.Fields().size(), fields.size());

  for (size_t i = 0; i < fields.size(); ++i) {
    EXPECT_EQ(rawData.Fields()[i].Key, fields[i].Key);
    EXPECT_EQ(rawData.Fields()[i].Value, fields[i].Value);
  }
}

/// @brief Tests that RawData can find keys correctly given existing fields.
TEST(RawDataTest, CanFindKeys) {
  const auto fields = std::vector<datalint::RawField>{
      {"key1", "value1"},
      {"key2", "value2"},
      {"key1", "value3"},
  };

  const datalint::RawData rawData(fields);

  EXPECT_TRUE(rawData.HasKey("key1"));
  EXPECT_TRUE(rawData.HasKey("key2"));
}

/// @brief Tests that RawData can return all values for a given key.
TEST(RawDataTest, CanReturnAllValuesByKey) {
  const auto fields = std::vector<datalint::RawField>{
      {"key1", "value1"},
      {"key2", "value2"},
      {"key1", "value3"},
  };

  const datalint::RawData rawData(fields);

  const auto key1Fields = rawData.GetFieldsByKey("key1");
  ASSERT_EQ(key1Fields.size(), 2);
  EXPECT_EQ(key1Fields[0]->Value, "value1");
  EXPECT_EQ(key1Fields[1]->Value, "value3");
}
