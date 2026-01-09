#pragma once

#include <datalint/Version/Version.h>

#include <string>

namespace datalint {

/// @brief Descriptor for an application, including its name and version.
struct ApplicationDescriptor {
  /// @brief The name of the application.
  std::string Name;
  /// @brief The version of the application.
  Version Version;
};
}  // namespace datalint
