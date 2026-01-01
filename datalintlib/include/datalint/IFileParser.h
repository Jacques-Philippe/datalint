#pragma once

#include <filesystem>

namespace datalint::input {
// Forward declaration
struct RawData;

/// @brief Interface for file parsers that convert input files into RawData.
class IFileParser {
 public:
  /// @brief Virtual destructor.
  virtual ~IFileParser() = default;
  /// @brief Parse the given file and return the extracted RawData.
  /// @param file The path to the input file to parse.
  /// @return The parsed RawData.
  virtual RawData Parse(const std::filesystem::path& file) = 0;
};
}  // namespace datalint::input
