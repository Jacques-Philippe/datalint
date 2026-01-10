#include <datalint/LayoutSpecification/ExpectedField.h>
#include <datalint/LayoutSpecification/LayoutSpecification.h>

#include <map>
#include <string>

namespace datalint::layout {

LayoutSpecification::LayoutSpecification(std::map<std::string, ExpectedField> expectedFields)
    : expectedFields(std::move(expectedFields)) {}

const std::optional<ExpectedField> LayoutSpecification::GetField(const std::string& key) const {
  auto it = expectedFields.find(key);
  if (it != expectedFields.end()) {
    return std::cref(it->second);
  }
  return std::nullopt;
}

bool LayoutSpecification::HasField(const std::string& key) const {
  return expectedFields.contains(key);
}

std::map<std::string, ExpectedField> LayoutSpecification::Fields() const {
  return expectedFields;
}
}  // namespace datalint::layout
