#pragma once

#include <string>
#include <vector>

/**
 * Represents raw data parsed from an input file.
 */

/**
 * Construct a RawData instance initialized with the provided fields.
 * @param fields Vector of RawField objects used to initialize the instance.
 */
 
/**
 * Access the stored raw fields.
 * @return A const reference to the vector of stored RawField objects.
 */
 
/**
 * Check whether any stored field has the given key.
 * @param key The key to search for among stored fields.
 * @return `true` if a field with `key` exists, `false` otherwise.
 */
 
/**
 * Retrieve pointers to all fields whose key equals the provided key.
 * @param key The key used to match fields.
 * @return A vector of pointers to matching RawField objects; empty if no matches are found.
 */
namespace datalint {

// Forward declaration
struct RawField;

/// @brief Represents raw data parsed from an input file.
class RawData {
 private:
  std::vector<RawField> fields;

 public:
  /// @brief Constructor that initializes RawData with a vector of RawField.
  /// @param fields The vector of RawField to initialize with.
  RawData(std::vector<RawField> fields);

  /// @brief Returns a reference to the vector of raw fields.
  /// @return A const reference to the vector of raw fields.
  const std::vector<RawField>& Fields() const noexcept;
  /// @brief Whether a field with the given key exists.
  /// @param key The key to search for.
  bool HasKey(const std::string& key) const;
  /// @brief Get all fields matching the given key.
  /// @param key the key by which we search for the fields
  /// @return a vector of pointers to the matching fields
  std::vector<const RawField*> GetFieldsByKey(const std::string& key) const;
};
}  // namespace datalint