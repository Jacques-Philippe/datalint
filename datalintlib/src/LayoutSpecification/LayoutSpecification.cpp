#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/FieldOrderingConstraint.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>

#include <map>
#include <optional>
#include <string>
#include <utility>

namespace datalint::layout {

LayoutSpecification::LayoutSpecification() : ExpectedFields_(), OrderingConstraints_() {}

const std::optional<ExpectedField> LayoutSpecification::GetField(const std::string& key) const {
  auto it = ExpectedFields_.find(key);
  if (it != ExpectedFields_.end()) {
    return it->second;
  }
  return std::nullopt;
}

bool LayoutSpecification::HasField(const std::string& key) const {
  return ExpectedFields_.contains(key);
}

const std::map<std::string, ExpectedField>& LayoutSpecification::Fields() const {
  return ExpectedFields_;
}

const std::vector<FieldOrderingConstraint>& LayoutSpecification::OrderingConstraints() const {
  return OrderingConstraints_;
}

void LayoutSpecification::AddExpectedField(const std::string& key, const ExpectedField& field) {
  // check if the field already exists
  if (ExpectedFields_.contains(key)) {
    throw std::logic_error("AddExpectedField failed: field already exists: " + key);
  }
  ExpectedFields_.emplace(key, field);
}

void LayoutSpecification::AddOrderingConstraint(FieldOrderingConstraint constraint) {
  // check if the constraint already exists
  for (const auto& existingConstraint : OrderingConstraints_) {
    if (existingConstraint == constraint) {
      throw std::logic_error("AddOrderingConstraint failed: constraint already exists: " +
                             constraint.BeforeKey + " -> " + constraint.AfterKey);
    }
  }

  OrderingConstraints_.push_back(std::move(constraint));
}
}  // namespace datalint::layout
