#include <datalint/Error/ErrorLog.h>
#include <gtest/gtest.h>

#include <fstream>
#include <vector>

/// @brief Tests that the error log can be initialized with subject and body.
TEST(ErrorLogTest, CanInitializeWithFields) {
  // Create an error log
  const std::string subject = "Test Error Subject";
  const std::string body = "This is the body of the test error log.";
  datalint::error::ErrorLog errorLog(subject, body);

  // Verify that the subject and body are correctly set
  EXPECT_EQ(errorLog.Subject(), subject);
  EXPECT_EQ(errorLog.Body(), body);
}
