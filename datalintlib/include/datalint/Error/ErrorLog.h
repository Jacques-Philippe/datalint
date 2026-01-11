#pragma once

#include <memory>
#include <vector>

namespace datalint::error {
class ErrorLog {
 public:
  /// @brief Virtual destructor
  virtual ~ErrorLog() = default;

  ErrorLog(const std::string& subject, const std::string& body) : Subject_(subject), Body_(body) {}

  /// @brief Getter for the subject of the error log
  const std::string& Subject() const { return Subject_; }
  /// @brief Getter for the body of the error log
  const std::string& Body() const { return Body_; }

 private:
  std::string Subject_;
  std::string Body_;
};

}  // namespace datalint::error
