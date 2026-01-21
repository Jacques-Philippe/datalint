#include <datalint/Error/ErrorLog.h>
#include <datalint/ErrorProcessor/FileOutputErrorProcessor.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

/// @brief Fixture for FileOutputErrorProcessor tests
class FileOutputErrorProcessorTest : public ::testing::Test {
 protected:
  /// @brief The path to the temporary file
  fs::path TempFile;

  /// @brief setup function executed before each test
  void SetUp() override {
    const auto* info = testing::UnitTest::GetInstance()->current_test_info();

    std::string filename =
        std::string(info->test_suite_name()) + "_" + std::string(info->name()) + ".txt";

    TempFile = fs::temp_directory_path() / filename;
  }

  /// @brief teardown function executed after each test
  void TearDown() override {
    std::error_code ec;
    fs::remove(TempFile, ec);
  }

  /// @brief Helper to read the string contained in the file at the given path
  /// @param path the path to the file
  /// @return the contained string
  static std::string ReadFile(const fs::path& path) {
    std::ifstream in(path);
    return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  }
};

using namespace datalint::error_processor;

/// @brief Tests that we're able to write errors to a file
TEST_F(FileOutputErrorProcessorTest, WritesErrorsToFile) {
  FileOutputErrorProcessor processor(TempFile);

  std::vector<datalint::error::ErrorLog> errors{{"Error A", "Something went wrong"},
                                                {"Error B", "Another failure"}};

  processor.Process(errors);

  const std::string content = ReadFile(TempFile);

  EXPECT_EQ(content,
            "Error A\nSomething went wrong\n"
            "Error B\nAnother failure\n");
}

/// @brief Tests that we're able to overwrite an existing file
TEST_F(FileOutputErrorProcessorTest, OverwritesExistingFile) {
  {
    std::ofstream out(TempFile);
    out << "old content\n";
  }

  FileOutputErrorProcessor processor(TempFile);

  std::vector<datalint::error::ErrorLog> errors{{"New Error", "New body"}};

  processor.Process(errors);

  const std::string content = ReadFile(TempFile);

  EXPECT_EQ(content, "New Error\nNew body\n");
}

/// @brief Tests that an empty error list produces an empty file
TEST_F(FileOutputErrorProcessorTest, EmptyErrorsProducesEmptyFile) {
  FileOutputErrorProcessor processor(TempFile);

  processor.Process({});

  const std::string content = ReadFile(TempFile);
  EXPECT_TRUE(content.empty());
}

/// @brief Tests that we get a runtime error if we get an issue opening the file
TEST(FileOutputErrorProcessorFailureTest, ThrowsIfFileCannotBeOpened) {
  const fs::path directoryPath = fs::temp_directory_path();

  FileOutputErrorProcessor processor(directoryPath);

  std::vector<datalint::error::ErrorLog> errors{{"Error", "Body"}};

  EXPECT_THROW(processor.Process(errors), std::runtime_error);
}
