#pragma once

#include <datalint/Error/ErrorLog.h>

#include <vector>

namespace datalint::error {

/// @brief Class to collect error logs during processing
class ErrorCollector {
 public:
  /// @brief Default constructor
  ErrorCollector() : Logs_() {}

  /// @brief Method to add an error log
  /// @param errorLog the error log to add
  void AddErrorLog(const ErrorLog& errorLog) { Logs_.push_back(errorLog); }

  /// @brief Method to retrieve all error logs
  /// @return A vector of ErrorLog instances
  const std::vector<ErrorLog>& GetErrorLogs() const { return Logs_; }

  /// @brief Method to retrieve whether any errors have been collected
  /// @return true if there are any collected errors, false otherwise
  bool HasErrors() const { return !Logs_.empty(); }

  /// @brief Retrieve the number of collected error logs
  /// @return the number of error logs
  std::size_t ErrorCount() const { return Logs_.size(); }

 private:
  /// @brief The collection of error logs
  std::vector<ErrorLog> Logs_;
};

}  // namespace datalint::error
