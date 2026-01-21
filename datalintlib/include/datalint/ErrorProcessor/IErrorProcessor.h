#pragma once

#include <datalint/Error/ErrorLog.h>

#include <vector>

namespace datalint::error_processor {
/// @brief Interface to define a class that receives and handles the errors output by the error
/// collector
class IErrorProcessor {
 public:
  /// @brief Process the incoming errors
  /// @param errors the errors
  virtual void Process(const std::vector<datalint::error::ErrorLog>& errors) const = 0;
};
}  // namespace datalint::error_processor
