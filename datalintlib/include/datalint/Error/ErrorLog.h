#pragma once

#include <memory>
#include <vector>

namespace datalint::error {
/// @brief Class to represent an error log entry
class ErrorLog {
 public:
  /// @brief Virtual destructor
  virtual ~ErrorLog() = default;

  /// @brief Constructor: must provide subject and body
  /// @param subject The subject of the error log
  /// @param body The body of the error log
  ErrorLog(const std::string& subject, const std::string& body) : Subject_(subject), Body_(body) {}

  /// @brief Getter for the subject of the error log
  /// @return The subject of the error log
  const std::string& Subject() const { return Subject_; }
  /// @brief Getter for the body of the error log
  /// @return The body of the error log
  const std::string& Body() const { return Body_; }

 private:
  /// @brief The subject of the error log
  std::string Subject_;
  /// @brief The body of the error log
  std::string Body_;
};

}  // namespace datalint::error
