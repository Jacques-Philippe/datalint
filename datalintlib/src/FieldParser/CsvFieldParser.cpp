#include <datalint/FieldParser/CsvFieldParser.h>

namespace datalint::fieldparser {
ParsedField CsvFieldParser::ParseFieldValue(const RawField& rawFieldValue) const {
  ParsedField parsedField;
  parsedField.Key = rawFieldValue.Key;

  std::string currentValue;
  for (size_t i = 0; i < rawFieldValue.Value.size(); ++i) {
    char c = rawFieldValue.Value[i];
    if (c == ',') {
      // Found a delimiter, store the current value
      parsedField.Values.push_back(RawValue{currentValue, rawFieldValue.Location});
      currentValue.clear();
    } else {
      currentValue += c;
    }
  }
  // Add the last value if any
  if (!currentValue.empty()) {
    parsedField.Values.push_back(RawValue{currentValue, rawFieldValue.Location});
  }

  // Always add the last value (may be empty after trailing comma)
  parsedField.Values.push_back(RawValue{currentValue, rawFieldValue.Location});

  return parsedField;
}
}  // namespace datalint::fieldparser
