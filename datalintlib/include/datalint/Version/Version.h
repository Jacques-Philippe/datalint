#pragma once

#include <charconv>
#include <stdexcept>
#include <string>
#include <string_view>

namespace datalint {
/// @brief Struct to contain a version definition
struct Version {
  /// @brief Major version number. The first of the numbers, i.e. HERE.x.x
  int Major;
  /// @brief Minor version number. The second of the numbers, i.e. x.HERE.x
  int Minor;
  /// @brief Patch version number. The third of the numbers, i.e. x.x.HERE
  int Patch;

  friend auto operator<=>(const Version&, const Version&) = default;

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

    return Version{major, minor, patch};
  }
};
}  // namespace datalint
