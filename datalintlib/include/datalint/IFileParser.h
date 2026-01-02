#pragma once

#include <filesystem>

namespace datalint {
// Forward declaration
class RawData;
}  // namespace datalint

namespace datalint::input {

/**
 * @brief Interface for parsers that convert input files into RawData.
 *
 * Implementers convert the contents of a filesystem path into a datalint::RawData
 * instance.
 */

/**
 * @brief Default virtual destructor to allow proper cleanup in derived classes.
 */
 
/**
 * @brief Parse the file at the given path and produce a RawData representation.
 * @param file Path to the input file to parse.
 * @return RawData containing the parsed contents of the provided file.
 */
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