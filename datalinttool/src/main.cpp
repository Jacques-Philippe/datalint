#include <datalint/CsvFileParser.h>
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
  const std::string inputFilePath = argv[1];
  const std::filesystem::path inputPath(inputFilePath);
  // it's assumed that in the consuming project, we know the file type
  // and can select the appropriate parser
  auto parser = std::make_unique<datalint::input::CsvFileParser>();
  const auto rawData = parser->Parse(inputPath);

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
