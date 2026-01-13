#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/FieldOrderingConstraint.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>

#include <algorithm>
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
  auto [it, inserted] = ExpectedFields_.emplace(key, field);
  if (!inserted) {
    throw std::logic_error("AddExpectedField failed: field already exists: " + key);
  }
}

void LayoutSpecification::ModifyExpectedField(const std::string& key,
                                              const std::function<void(ExpectedField&)> mutator) {
  auto it = ExpectedFields_.find(key);
  if (it == ExpectedFields_.end()) {
    throw std::logic_error("ModifyExpectedField failed: field does not exist: " + key);
  }

  mutator(it->second);
}

void LayoutSpecification::RemoveExpectedField(const std::string& key) {
  if (ExpectedFields_.erase(key) == 0) {
    throw std::logic_error("RemoveExpectedField failed: field does not exist: " + key);
  }
}

void LayoutSpecification::AddOrderingConstraint(FieldOrderingConstraint constraint) {
  auto& constraints = OrderingConstraints_;
  bool exists =
      std::any_of(constraints.begin(), constraints.end(), [&](const FieldOrderingConstraint& c) {
        return c.BeforeKey == constraint.BeforeKey && c.AfterKey == constraint.AfterKey;
      });
  if (exists) {
    throw std::logic_error("AddOrderingConstraint failed: constraint already exists: " +
                           constraint.BeforeKey + " -> " + constraint.AfterKey);
  }

  OrderingConstraints_.push_back(std::move(constraint));
}

void LayoutSpecification::RemoveOrderingConstraint(const std::string& beforeKey,
                                                   const std::string& afterKey) {
  auto& constraints = OrderingConstraints_;

  auto it =
      std::find_if(constraints.begin(), constraints.end(), [&](const FieldOrderingConstraint& c) {
        return c.BeforeKey == beforeKey && c.AfterKey == afterKey;
      });

  if (it == constraints.end()) {
    throw std::logic_error("RemoveOrderingConstraint failed: constraint does not exist: " +
                           beforeKey + " -> " + afterKey);
  }

  constraints.erase(it);
}
}  // namespace datalint::layout
