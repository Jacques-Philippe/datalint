#include <datalint/LayoutSpecification/ExpectedField.h>
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
  ExpectedFields_.emplace(key, field);
}

void LayoutSpecification::AddOrderingConstraint(FieldOrderingConstraint constraint) {
  OrderingConstraints_.push_back(constraint);
}
}  // namespace datalint::layout
