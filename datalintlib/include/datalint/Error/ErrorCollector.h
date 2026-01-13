#pragma once

#include <datalint/Error/ErrorLog.h>

#include <vector>

namespace datalint::error {

/// @brief Class to collect error logs during processing
class ErrorCollector {
 public:
  /// @brief Default constructor
  ErrorCollector() : errorLogs_() {}

  /// @brief Method to add an error log
  /// @param errorLog the error log to add
  void AddErrorLog(const ErrorLog& errorLog) { errorLogs_.push_back(errorLog); }

  /// @brief Method to retrieve all error logs
  /// @return A vector of ErrorLog instances
  const std::vector<ErrorLog>& GetErrorLogs() const { return errorLogs_; }

  /// @brief Method to retrieve whether any errors have been collected
  /// @return true if there are any collected errors, false otherwise
  bool HasErrors() const { return !errorLogs_.empty(); }

 private:
  /// @brief The collection of error logs
  std::vector<ErrorLog> errorLogs_;
};

}  // namespace datalint::error
