#pragma once
#include <string_view>

namespace datalint::utils {
/// @brief Helper to try parsing an int from a string
/// @param text the text to parse
/// @param out the outgoing int value
/// @return true for the parse operation was successful
bool TryParseInt(const std::string_view text, int& out);
}  // namespace datalint::utils
