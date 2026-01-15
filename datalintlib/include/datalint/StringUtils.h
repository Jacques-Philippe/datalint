#pragma once
#include <string_view>

namespace datalint::utils {
bool TryParseInt(const std::string_view text, int& out);
}  // namespace datalint::utils
