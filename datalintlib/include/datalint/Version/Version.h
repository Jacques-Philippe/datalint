#pragma once

#include <charconv>
#include <stdexcept>
#include <string>
#include <string_view>

namespace datalint {
/// @brief Class to contain a version definition
class Version {
 public:
  /// @brief Constructor: must provide all members
  /// @param major The major version number
  /// @param minor The minor version number
  /// @param patch The patch version number
  /// @throws std::invalid_argument if any of the version components are negative
  Version(int major, int minor, int patch) {
    if (major < 0 || minor < 0 || patch < 0) {
      throw std::invalid_argument("Version components must be non-negative");
    }
    Major_ = major;
    Minor_ = minor;
    Patch_ = patch;
  }

  /// @brief Major version number. The first of the numbers, i.e. HERE.x.x
  /// @return The major version number
  int Major() const { return Major_; }
  /// @brief Minor version number. The second of the numbers, i.e. x.HERE.x
  /// @return The minor version number
  int Minor() const { return Minor_; }
  /// @brief Patch version number. The third of the numbers, i.e. x.x.HERE
  /// @return The patch version number
  int Patch() const { return Patch_; }

  friend auto operator<=>(const Version&, const Version&) = default;

  /// @brief Parse a version string into a Version object
  /// @param str The version string to parse (format: "major.minor.patch")
  /// @return The parsed Version object
  /// @throws std::invalid_argument if the string is not in the correct format or contains invalid
  /// (negative) numbers
  static Version Parse(std::string_view str) {
    int major = 0;
    int minor = 0;
    int patch = 0;

    auto parseInt = [](std::string_view token) -> int {
      if (token.empty()) {
        throw std::invalid_argument("Empty version component");
      }

      int value = 0;
      auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);

      if (ec != std::errc{} || ptr != token.data() + token.size()) {
        throw std::invalid_argument("Invalid version component");
      }
      if (value < 0) {
        throw std::invalid_argument("Negative version component");
      }

      return value;
    };

    // Parse major
    std::size_t pos1 = str.find('.');
    if (pos1 == std::string_view::npos) {
      throw std::invalid_argument("Invalid version format");
    }

    major = parseInt(str.substr(0, pos1));
    str.remove_prefix(pos1 + 1);

    // Parse minor
    std::size_t pos2 = str.find('.');
    if (pos2 == std::string_view::npos) {
      throw std::invalid_argument("Invalid version format");
    }

    minor = parseInt(str.substr(0, pos2));
    str.remove_prefix(pos2 + 1);

    // Parse patch (must consume entire remainder)
    patch = parseInt(str);

    return Version(major, minor, patch);
  }

 private:
  /// @brief Major version number. The first of the numbers, i.e. HERE.x.x
  int Major_;
  /// @brief Minor version number. The second of the numbers, i.e. x.HERE.x
  int Minor_;
  /// @brief Patch version number. The third of the numbers, i.e. x.x.HERE
  int Patch_;
};
}  // namespace datalint
