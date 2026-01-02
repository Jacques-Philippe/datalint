#include <datalint/RawData.h>
#include <datalint/RawField.h>

namespace datalint {

/**
 * @brief Constructs a RawData instance with the given fields.
 *
 * Initializes the object's internal field storage using the provided vector of RawField.
 *
 * @param fields Vector of RawField objects to store in the RawData instance.
 */
RawData::RawData(std::vector<RawField> fields) {
  this->fields = fields;
}
/**
 * @brief Determines whether any stored RawField has the specified key.
 *
 * @param key The key to search for among stored fields.
 * @return true if a field with the given key exists, false otherwise.
 */
bool RawData::HasKey(const std::string& key) const {
  for (const auto& field : fields) {
    if (field.Key == key) {
      return true;
    }
  }
  return false;
}
/**
 * @brief Provides read-only access to the stored raw fields.
 *
 * @return const std::vector<RawField>& Reference to the internal vector of RawField objects.
 */
const std::vector<RawField>& RawData::Fields() const noexcept {
  return fields;
}
/**
 * @brief Retrieves all stored fields whose Key matches the given key.
 *
 * Returns pointers to the matching elements stored inside this RawData instance.
 *
 * @param key The field key to match.
 * @return std::vector<const RawField*> Vector of pointers to matching `RawField` elements.
 *         Pointers refer to elements owned by this `RawData` and remain valid while this
 *         instance is not modified or destroyed.
 */
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