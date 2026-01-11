#pragma once

#include <datalint/Error/ErrorLog.h>

#include <memory>
#include <vector>

namespace datalint::error {

class ErrorCollector {
 public:
  ErrorCollector() : errorLogs_() {}

  /// @brief Method to add an error log
  /// @param errorLog A shared pointer to the ErrorLog instance to add
  void AddErrorLog(ErrorLog errorLog) { errorLogs_.push_back(errorLog); }

  /// @brief Method to retrieve all error logs
  /// @return A vector of pointers to ErrorLog instances
  std::vector<ErrorLog> GetErrorLogs() const { return errorLogs_; }

 private:
  std::vector<ErrorLog> errorLogs_;
};

}  // namespace datalint::error
