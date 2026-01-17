#pragma once

#include <datalint/SourceLocation.h>

#include <string>

namespace datalint::fieldparser {
/// @brief Represents a raw value read from a raw field
struct RawValue {
  /// @brief The individual value associated to the raw field.
  std::string Value;
  /// @brief The source location of the value in the input file.
  SourceLocation Location;
};

}  // namespace datalint::fieldparser
