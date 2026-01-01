
#include <datalint/CsvFileParser.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace datalint::input {

datalint::RawData CsvFileParser::Parse(const std::filesystem::path& file) {
  std::vector<RawField> fields;

  std::ifstream input(file);
  if (!input.is_open()) {
    throw std::runtime_error("Cannot open CSV file: " + file.string());
  }

  std::string line;
  int lineNumber = 0;

  while (std::getline(input, line)) {
    ++lineNumber;
    std::stringstream ss(line);
    std::string key, value;

    if (!std::getline(ss, key, ',')) continue;
    if (!std::getline(ss, value, ',')) continue;

    RawField field;
    field.Key = key;
    field.Value = value;
    field.Location.Filename = file.string();
    field.Location.Line = lineNumber;

    fields.push_back(std::move(field));
  }

  // Construct RawData in one shot
  return RawData(std::move(fields));
}
}  // namespace datalint::input
