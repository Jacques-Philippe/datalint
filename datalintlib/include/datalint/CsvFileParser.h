#pragma once

#include <datalint/IFileParser.h>

#include <filesystem>

namespace datalint {
// Forward declaration
class RawData;
}  /**
 * Parse a CSV file and produce a RawData representation.
 *
 * @param file Path to the CSV input file to parse.
 * @return Parsed RawData containing the extracted records and fields.
 */

namespace datalint::input {

/**
 * Interface for CSV file parsers that convert an input file into a datalint::RawData.
 */

/**
 * Parse the CSV file at the specified filesystem path and produce a RawData object.
 * @param file Path to the CSV file to parse.
 * @return A datalint::RawData containing the parsed contents of the file.
 */
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