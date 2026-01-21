#include <datalint/Error/ErrorLog.h>
#include <datalint/ErrorProcessor/FileOutputErrorProcessor.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

class FileOutputErrorProcessorTest : public ::testing::Test {
 protected:
  fs::path TempFile;

  void SetUp() override { TempFile = fs::temp_directory_path() / "datalint_error_output_test.txt"; }

  void TearDown() override {
    std::error_code ec;
    fs::remove(TempFile, ec);
  }

  static std::string ReadFile(const fs::path& path) {
    std::ifstream in(path);
    return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  }
};

using namespace datalint::error_processor;

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

TEST_F(FileOutputErrorProcessorTest, EmptyErrorsProducesEmptyFile) {
  FileOutputErrorProcessor processor(TempFile);

  processor.Process({});

  const std::string content = ReadFile(TempFile);
  EXPECT_TRUE(content.empty());
}

TEST(FileOutputErrorProcessorFailureTest, ThrowsIfFileCannotBeOpened) {
  const fs::path directoryPath = fs::temp_directory_path();

  FileOutputErrorProcessor processor(directoryPath);

  std::vector<datalint::error::ErrorLog> errors{{"Error", "Body"}};

  EXPECT_THROW(processor.Process(errors), std::runtime_error);
}
