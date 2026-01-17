#include <datalint/FieldParser/ParsedData.h>
#include <datalint/FieldParser/ParsedDataBuilder.h>
#include <datalint/FieldParser/ParsedField.h>

namespace datalint::fieldparser {
ParsedDataBuilder::ParsedDataBuilder(std::unique_ptr<IFieldParser> fieldparser)
    : FieldParser_(std::move(fieldparser)) {}

ParsedData ParsedDataBuilder::Build(const RawData& rawData) const {
  std::vector<ParsedField> parsedFields;
  parsedFields.reserve(rawData.Fields().size());
  for (const RawField& rawField : rawData.Fields()) {
    ParsedField parsedField = FieldParser_->ParseFieldValue(rawField);
    parsedFields.push_back(std::move(parsedField));
  }
  return ParsedData(std::move(parsedFields));
}

}  // namespace datalint::fieldparser
