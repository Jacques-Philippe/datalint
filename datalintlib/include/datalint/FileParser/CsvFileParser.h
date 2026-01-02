#pragma once

#include <datalint/FileParser/IFileParser.h>

#include <filesystem>

namespace datalint {
// Forward declaration
class RawData;
}  // namespace datalint

namespace datalint::input {

/// @brief Concrete implementation of IFileParser for CSV files.
class CsvFileParser : public IFileParser {
 public:
  /// @brief Virtual destructor.
  virtual ~CsvFileParser() = default;
  /// @brief Parse the given CSV file and return the extracted RawData.
  /// @param file The path to the input file to parse.
  /// @return The parsed RawData.
  datalint::RawData Parse(const std::filesystem::path& file) override;
};
}  // namespace datalint::input
