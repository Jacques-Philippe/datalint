#include <datalint/Error/ErrorCollector.h>
#include <datalint/Error/ErrorLog.h>
#include <gtest/gtest.h>

/// @brief Tests that the error collector initializes with zero errors.
TEST(ErrorCollectorTest, CanInitializeWithZeroErrors) {
  // Create an error collector
  datalint::error::ErrorCollector errorCollector;
  // Verify that there are no error logs initially
  const auto errorLogs = errorCollector.GetErrorLogs();
  EXPECT_EQ(errorLogs.size(), 0);
}

/// @brief Tests that the error collector can add and retrieve error logs.
TEST(ErrorCollectorTest, CanAddAndRetrieveErrorLogs) {
  // Create an error collector
  datalint::error::ErrorCollector errorCollector;
  // Create some error logs
  datalint::error::ErrorLog errorLog1("Error Subject 1", "This is the body of error log 1.");
  datalint::error::ErrorLog errorLog2("Error Subject 2", "This is the body of error log 2.");
  // Add error logs to the collector
  errorCollector.AddErrorLog(errorLog1);
  errorCollector.AddErrorLog(errorLog2);
  // Retrieve error logs from the collector
  const auto errorLogs = errorCollector.GetErrorLogs();
  // Verify that the error logs are correctly retrieved
  ASSERT_EQ(errorLogs.size(), 2);
  EXPECT_EQ(errorLogs[0].Subject(), "Error Subject 1");
  EXPECT_EQ(errorLogs[0].Body(), "This is the body of error log 1.");
  EXPECT_EQ(errorLogs[1].Subject(), "Error Subject 2");
  EXPECT_EQ(errorLogs[1].Body(), "This is the body of error log 2.");
}
