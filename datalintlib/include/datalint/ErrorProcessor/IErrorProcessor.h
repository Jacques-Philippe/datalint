#pragma once

#include <datalint/Error/ErrorLog.h>

#include <vector>

namespace datalint::error_processor {
/// @brief Error processor that writes validation errors to a file
class IErrorProcessor {
 public:
  /// @brief Virtual destructor
  virtual ~IErrorProcessor() = default;

  /// @brief Process the incoming errors
  /// @param errors the errors
  virtual void Process(const std::vector<datalint::error::ErrorLog>& errors) const = 0;
};
}  // namespace datalint::error_processor
