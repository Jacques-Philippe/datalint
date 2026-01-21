#pragma once

#include <datalint/ErrorProcessor/IErrorProcessor.h>

#include <filesystem>

namespace datalint::error_processor {
/// @brief Interface to define a class that receives and handles the errors output by the error
/// collector
class FileOutputErrorProcessor : public IErrorProcessor {
 public:
  /// @brief Constructor
  /// @param path the filepath to output to
  FileOutputErrorProcessor(const std::filesystem::path& path);

  /// @brief Process the incoming errors
  /// @param errors the errors
  /// @throws runtime error if something goes wrong writing to the file
  void Process(const std::vector<datalint::error::ErrorLog>& errors) const override;

 private:
  /// @brief The path to which we output to
  std::filesystem::path OutputPath_;
};
}  // namespace datalint::error_processor
