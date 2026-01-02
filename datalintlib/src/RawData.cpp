#include <datalint/RawData.h>
#include <datalint/RawField.h>

namespace datalint {

RawData::RawData(std::vector<RawField> fields) {
  this->fields = fields;
}
bool RawData::HasKey(const std::string& key) const {
  for (const auto& field : fields) {
    if (field.Key == key) {
      return true;
    }
  }
  return false;
}
const std::vector<RawField>& RawData::Fields() const noexcept {
  return fields;
}
std::vector<const RawField*> RawData::GetFieldsByKey(const std::string& key) const {
  std::vector<const RawField*> matchingFields;
  for (const auto& field : fields) {
    if (field.Key == key) {
      matchingFields.push_back(&field);
    }
  }
  return matchingFields;
}
}  // namespace datalint
