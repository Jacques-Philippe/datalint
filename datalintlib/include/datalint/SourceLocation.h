#pragma once

#include <string>

namespace datalint {

/// @brief Represents the location of a source element within a file.
struct SourceLocation {
  /// @brief The filename where the source is located.
  std::string Filename;
  /// @brief The line number in the source file.
  int Line;
};

}  // namespace datalint
