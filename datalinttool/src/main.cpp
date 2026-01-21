#include <datalint/ApplicationDescriptor/ApplicationDescriptor.h>
#include <datalint/ApplicationDescriptor/DefaultCsvApplicationDescriptorResolver.h>
#include <datalint/ApplicationDescriptor/ResolveResult.h>
#include <datalint/Error/ErrorCollector.h>
#include <datalint/Error/ErrorLog.h>
#include <datalint/FieldParser/CsvFieldParser.h>
#include <datalint/FieldParser/IFieldParser.h>
#include <datalint/FieldParser/ParsedDataBuilder.h>
#include <datalint/FileParser/CsvFileParser.h>
#include <datalint/LayoutSpecification/FieldOrderingConstraint.h>
#include <datalint/LayoutSpecification/LayoutPatch.h>
#include <datalint/LayoutSpecification/LayoutSpecificationBuilder.h>
#include <datalint/LayoutSpecification/LayoutSpecificationValidator.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>
#include <datalint/RuleSpecification/AddFieldRulePatchOperation.h>
#include <datalint/RuleSpecification/IRulePatchOperation.h>
#include <datalint/RuleSpecification/IntegerInRangeRule.h>
#include <datalint/RuleSpecification/RulePatch.h>
#include <datalint/RuleSpecification/RuleSpecification.h>
#include <datalint/RuleSpecification/RuleSpecificationBuilder.h>
#include <datalint/RuleSpecification/RuleValidator.h>
#include <datalint/RuleSpecification/ValueAtIndexSelector.h>

#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
  // 1. Parse the command line arguments for the input file path
  if (argc < 2) {
    std::cerr << "Usage: datalinttool <input_file_path>\n";
    return 1;
  }
  datalint::error::ErrorCollector errorCollector;
  auto printErrors = [&errorCollector]() {
    for (const auto& errorLog : errorCollector.GetErrorLogs()) {
      std::cerr << "Error: " << errorLog.Subject() << "\n" << errorLog.Body() << "\n\n";
    }
  };

  const std::string inputFilePath = argv[1];
  const std::filesystem::path inputPath(inputFilePath);
  // it's assumed that in the consuming project, we know the file type
  // and can select the appropriate parser

  // 1. Parse the input file to raw data
  auto parser = std::make_unique<datalint::input::CsvFileParser>();
  const auto rawData = parser->Parse(inputPath);

  datalint::DefaultCsvApplicationDescriptorResolver resolver;
  // 2. Resolve the application descriptor from the raw data
  const auto result = resolver.Resolve(rawData);

  if (!result.Success()) {
    std::cerr << "Failed to resolve application descriptor:\n";
    for (const auto& error : result.Errors) {
      errorCollector.AddErrorLog(
          datalint::error::ErrorLog("Application Descriptor Resolution Error", error.ToString()));
    }
    printErrors();
    return 1;
  }

  using namespace datalint::layout;

  // 3. Build expected layout patches

  const LayoutPatch layoutPatch1("patch1", datalint::VersionRange::All(),
                                 std::vector<LayoutPatchOperation>{
                                     AddField{"key1", ExpectedField{1, std::nullopt}},
                                     AddField{"key2", ExpectedField{1, std::nullopt}},
                                     AddField{"key10", ExpectedField{1, std::nullopt}},
                                     AddField{"ApplicationName", ExpectedField{1, std::nullopt}},
                                     AddField{"ApplicationVersion", ExpectedField{1, std::nullopt}},
                                 });

  std::vector<LayoutPatch> layoutPatches = {layoutPatch1};
  LayoutSpecificationBuilder layoutSpecificationBuilder;
  const auto descriptor = result.Descriptor.value();
  // 4. Build layout specification for the resolved application descriptor version
  LayoutSpecification layoutSpec =
      layoutSpecificationBuilder.Build(descriptor.Version(), layoutPatches);
  layoutSpec.AddOrderingConstraint(FieldOrderingConstraint{
      "ApplicationName",
      "ApplicationVersion"});  // ApplicationName must come before ApplicationVersion

  // 5. Validate the layout specification against the raw data
  LayoutSpecificationValidator layoutSpecValidator{UnexpectedFieldStrictness::Permissive};
  const bool isValid = layoutSpecValidator.Validate(layoutSpec, rawData, errorCollector);

  if (!isValid) {
    std::cerr << "Validation failed:\n";
    printErrors();
    return 1;
  }

  // 6. Build the rule specification
  using namespace datalint::rules;

  FieldRule key1Rule{"key10", std::make_unique<IntegerInRangeRule>(0, 10),
                     std::make_unique<ValueAtIndexSelector>(0)};

  auto addKey1Operation = std::make_unique<AddFieldRulePatchOperation>(std::move(key1Rule));

  std::vector<std::unique_ptr<IRulePatchOperation>> ops;
  ops.push_back(std::move(addKey1Operation));

  RulePatch patch("example-rule-patch", datalint::VersionRange::All(), std::move(ops));

  std::vector<RulePatch> rulePatches;
  rulePatches.push_back(std::move(patch));

  RuleSpecificationBuilder ruleSpecBuilder;
  RuleSpecification ruleSpec = ruleSpecBuilder.Build(descriptor.Version(), rulePatches);

  using namespace datalint::fieldparser;
  // 7. Parse the raw data
  std::unique_ptr<CsvFieldParser> csvFieldParser = std::make_unique<CsvFieldParser>();
  ParsedDataBuilder parsedDataBuilder(std::move(csvFieldParser));
  const ParsedData parsedData = parsedDataBuilder.Build(rawData);
  // 8. Validate the built rule specification
  RuleValidator ruleValidator;
  if (!ruleValidator.Validate(ruleSpec, parsedData, errorCollector)) {
    // output errors to file
    std::cerr << "Validation failed:\n";
    printErrors();
    return 1;
  } else {
    // output success message to file
  }

  std::cout << "datalinttool executed successfully!\n";
  return 0;
}
