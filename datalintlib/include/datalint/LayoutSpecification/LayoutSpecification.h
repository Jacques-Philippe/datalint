#pragma once

#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/FieldOrderingConstraint.h>

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace datalint::layout {

class LayoutSpecificationBuilder;

/// @brief Class to contain the definition for a layout specification in which we specify the data
/// we expect to find in our input file raw data
class LayoutSpecification {
 public:
  /// @brief Default constructor for the layout specification
  LayoutSpecification();

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

  /// @brief Return the fields making up the ordering constraints of the layout specification
  /// @return the ordering constraints
  const std::vector<FieldOrderingConstraint>& OrderingConstraints() const;

  /// @brief Adds an expected field to the layout specification
  /// @param key the key associated to the field
  /// @param field the field to add
  void AddExpectedField(const std::string& key, const ExpectedField& field);

  /// @brief Adds an ordering constraint between two fields
  /// @param constraint the ordering constraint to add
  void AddOrderingConstraint(FieldOrderingConstraint constraint);

 private:
  friend class LayoutSpecificationBuilder;
  /// @brief the map of all expected fields that make up the layout specification
  std::map<std::string, ExpectedField> ExpectedFields_;
  /// @brief the list of ordering constraints between fields
  std::vector<FieldOrderingConstraint> OrderingConstraints_;
};
}  // namespace datalint::layout
