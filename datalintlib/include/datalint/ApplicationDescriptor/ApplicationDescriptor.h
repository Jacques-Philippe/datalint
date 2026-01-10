#pragma once

#include <datalint/Version/Version.h>

#include <string>

namespace datalint {

/// @brief Descriptor for an application, including its name and version.
class ApplicationDescriptor {
 public:
  /// @brief Getter for the application name.
  /// @return The name of the application.
  const std::string Name() const { return Name_; }
  /// @brief Getter for the application version.
  /// @return The version of the application.
  const datalint::Version Version() const { return Version_; }

  /// @brief Constructor: must provide all members.
  /// @param name The name of the application.
  /// @param version The version of the application.
  ApplicationDescriptor(const std::string& name, datalint::Version version)
      : Name_(name), Version_(version) {}

 private:
  /// @brief The name of the application.
  std::string Name_;
  /// @brief The version of the application.
  datalint::Version Version_;
};
}  // namespace datalint
