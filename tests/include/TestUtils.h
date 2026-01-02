#pragma once

#include <atomic>
#include <string>

namespace datalint::test {

/// @brief Generates a unique temporary CSV filename for testing purposes.
/// @param testName The name of the test requesting the temporary filename.
/// @return A unique temporary CSV filename.
inline std::string MakeTempCsvFilename(std::string_view testName) {
  static std::atomic<int> counter{0};
  return std::string(testName) + "_" + std::to_string(counter++) + ".csv";
}

}  // namespace datalint::test
