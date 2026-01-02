#include <datalint/CsvFileParser.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>

#include <csv2/reader.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace datalint::input {

/**
 * Parse a CSV file into a RawData collection of RawField entries.
 *
 * Each non-empty row produces one RawField: the first column becomes the field Key,
 * the remaining columns are concatenated with commas into the field Value, and
 * Location.Filename is set to the provided file path while Location.Line is set
 * to the row number (1-based). Empty rows are skipped.
 *
 * @param file Path to the CSV file to parse.
 * @return RawData A RawData containing one RawField per non-empty CSV row as described above.
 * @throws std::runtime_error If the CSV file cannot be opened (mmap failure).
 */
datalint::RawData CsvFileParser::Parse(const std::filesystem::path& file) {
  std::vector<RawField> fields;

  csv2::Reader<csv2::delimiter<','>, csv2::quote_character<'"'>, csv2::first_row_is_header<false> >
      reader;

  if (!reader.mmap(file.string())) {
    throw std::runtime_error("Failed to open CSV file: " + file.string());
  }

  std::size_t lineNumber = 0;

  for (const auto& row : reader) {
    ++lineNumber;

    auto it = row.begin();
    if (!(it != row.end())) {
      continue;  // empty row
    }

    // First column → key
    std::string key;
    (*it).read_value(key);
    ++it;

    // Remaining columns → single value string
    std::string value;
    bool first = true;

    for (; it != row.end(); ++it) {
      std::string cell;
      (*it).read_value(cell);

      if (!first) {
        value += ",";
      }
      value += cell;
      first = false;
    }

    RawField field;
    field.Key = std::move(key);
    field.Value = std::move(value);
    field.Location.Filename = file.string();
    field.Location.Line = static_cast<int>(lineNumber);

    fields.push_back(std::move(field));
  }

  return RawData(std::move(fields));
}
}  // namespace datalint::input