#pragma once

#include <datalint/FileParser/IFileParser.h>

#include <filesystem>

namespace datalint {
// Forward declaration
class RawData;
}  // namespace datalint

namespace datalint::input {

/// @brief Interface for file parsers that convert input files into RawData.
class CsvFileParser : public IFileParser {
 public:
  /// @brief Virtual destructor.
  virtual ~CsvFileParser() = default;
  /// @brief Parse the given file and return the extracted RawData.
  /// @param file The path to the input file to parse.
  /// @return The parsed RawData.
  datalint::RawData Parse(const std::filesystem::path& file) override;
};
}  // namespace datalint::input
