#include <datalint/ErrorProcessor/FileOutputErrorProcessor.h>

#include <fstream>
#include <stdexcept>

namespace datalint::error_processor {
FileOutputErrorProcessor::FileOutputErrorProcessor(const std::filesystem::path& path)
    : OutputPath_(path) {}

void FileOutputErrorProcessor::Process(const std::vector<datalint::error::ErrorLog>& errors) const {
  // Write the errors to the output file
  std::ofstream out(OutputPath_, std::ios::out | std::ios::trunc);
  if (!out.is_open()) {
    throw std::runtime_error("Failed to open error output file: " + OutputPath_.string());
  }

  for (const auto& error : errors) {
    out << error.Subject() << '\n' << error.Body() << '\n';
  }

  if (!out.good()) {
    throw std::runtime_error("Failed while writing error output file: " + OutputPath_.string());
  }
}
}  // namespace datalint::error_processor
