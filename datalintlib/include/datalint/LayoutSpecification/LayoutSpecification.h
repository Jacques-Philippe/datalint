#pragma once

#include <datalint/LayoutSpecification/ExpectedField.h>

#include <map>
#include <optional>
#include <string>

namespace datalint::layout {

/// @brief Class to contain the definition for a layout specification in which we specify the data
/// we expect to find in our input file raw data
class LayoutSpecification {
 public:
  /// @brief Constructor for the layout specification
  /// @param expectedFields the expected fields
  LayoutSpecification(std::map<std::string, ExpectedField> expectedFields);

  /// @brief Return the given expected field, if any
  /// @param key the key associated to the field
  /// @return the match
  const std::optional<ExpectedField> GetField(const std::string& key) const;

  /// @brief Return true for the field exists in the layout specification
  /// @param key the key associated to the field
  /// @return true for field exists
  bool HasField(const std::string& key) const;

  /// @brief Return the fields making up the layout specification
  /// @return the fields
  const std::map<std::string, ExpectedField>& Fields() const;

 private:
  /// @brief the map of all expected fields that make up the layout specification
  std::map<std::string, ExpectedField> expectedFields;
};
}  // namespace datalint::layout
