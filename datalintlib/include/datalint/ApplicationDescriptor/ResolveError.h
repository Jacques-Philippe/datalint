#pragma once

#include <string>

namespace datalint {
/// @brief Enumeration of possible resolve error codes.
enum class ResolveErrorCode {
  /// @brief Indicates a required field is missing.
  MissingRequiredField,
  /// @brief Indicates a field that should be unique has duplicates.
  DuplicateField,
  /// @brief Indicates a general parsing error.
  ParsingError,
  /// @brief Indicates an unknown error.
  UnknownError
};

/// @brief Represents an error encountered during the resolution of an application descriptor.
struct ResolveError {
  /// @brief The error code.
  ResolveErrorCode Code;
  /// @brief The field associated with the error.
  std::string Field;
  /// @brief An optional detailed message about the error.
  std::string Message;
  /// @brief The error message as a string.
  /// @return the stringified error message.
  std::string ToString() const {
    switch (Code) {
      case ResolveErrorCode::MissingRequiredField:
        return "Missing required field: " + Field + (Message.empty() ? "" : " (" + Message + ")");
      case ResolveErrorCode::DuplicateField:
        return "Found more than one match for: " + Field + "\nThis should be unique" +
               (Message.empty() ? "" : " (" + Message + ")");
      case ResolveErrorCode::ParsingError:
        return "Failed to parse: " + Field + (Message.empty() ? "" : " (" + Message + ")");
      case ResolveErrorCode::UnknownError:
        return "Unknown error for field: " + Field + (Message.empty() ? "" : " (" + Message + ")");
    }
    return "Unhandled error code.";
  }
};

}  // namespace datalint
