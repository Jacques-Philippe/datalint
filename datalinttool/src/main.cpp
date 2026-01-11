#include <datalint/ApplicationDescriptor/ApplicationDescriptor.h>
#include <datalint/ApplicationDescriptor/DefaultCsvApplicationDescriptorResolver.h>
#include <datalint/ApplicationDescriptor/ResolveResult.h>
#include <datalint/Error/ErrorCollector.h>
#include <datalint/Error/ErrorLog.h>
#include <datalint/FileParser/CsvFileParser.h>
#include <datalint/LayoutSpecification/LayoutPatch.h>
#include <datalint/LayoutSpecification/LayoutSpecificationBuilder.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>

#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
  // 1. Parse the command line arguments for the input file path
  if (argc < 2) {
    std::cerr << "Usage: datalinttool <input_file_path>\n";
    return 1;
  }
  datalint::error::ErrorCollector errorCollector;
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
    // Print collected errors
    for (const auto& errorLog : errorCollector.GetErrorLogs()) {
      std::cerr << "Error: " << errorLog.Subject() << "\n" << errorLog.Body() << "\n";
    }
    return 1;
  }

  using namespace datalint::layout;

  // 3. Build expected layout patches
  const LayoutPatch patch("patch1", datalint::VersionRange::All(),
                          std::vector<LayoutPatchOperation>{
                              AddField{"key1", ExpectedField{1, std::nullopt}},
                              AddField{"key2", ExpectedField{1, std::nullopt}},
                              AddField{"ApplicationName", ExpectedField{1, std::nullopt}},
                              AddField{"ApplicationVersion", ExpectedField{1, std::nullopt}},
                          });

  std::vector<LayoutPatch> patches = {patch};
  LayoutSpecificationBuilder builder;
  const auto descriptor = result.Descriptor.value();
  // 4. Build layout specification for the resolved application descriptor version
  const LayoutSpecification layoutSpec = builder.Build(descriptor.Version(), patches);

  // 5. Validate the layout specification against the raw data

  // 1. The consuming application is responsible for providing
  // - the manner in which we conclude which name and version number to use from
  // the input file
  // - the manner in which we parse the input file to a dictionary of key value
  // pairs
  // 2. Parse the input file, gathering
  // - name
  // - version number
  // - dictionary of key value pairs
  // 3. Given name and version number, build layout expectation
  // 4. Given layout expectation and dictionary of key value pairs, observe that
  // expected keys are present
  // 5. Given name and version number, build validation rules
  // 6. Given validation rules and dictionary of key value pairs, observe that
  // expected keys have valid values
  // 7. Report results of observations to user
  std::cout << "datalinttool executed successfully!\n";
  return 0;
}
