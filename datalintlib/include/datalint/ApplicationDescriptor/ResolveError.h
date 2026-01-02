#pragma once

#include <string>

namespace datalint {
/// @brief Enumeration of possible resolve error codes.
enum class ResolveErrorCode {
  /// @brief Indicates a required field is missing.
  MissingRequiredField,
  /// @brief Indicates a field that should be unique has duplicates.
  DuplicateField,
};

/// @brief Represents an error encountered during the resolution of an application descriptor.
struct ResolveError {
  /// @brief The error code.
  ResolveErrorCode Code;
  /// @brief The field associated with the error.
  std::string Field;
  /// @brief The error message as a string.
  /// @return the stringified error message.
  std::string ToString() const {
    switch (Code) {
      case ResolveErrorCode::MissingRequiredField:
        return "Missing required field: " + Field;
      case ResolveErrorCode::DuplicateField:
        return "Found more than one match for: " + Field + "\nThis should be unique";
      default:
        return "Unknown error";
    }
  }
};

}  // namespace datalint
