#include <charconv>
#include <string_view>

namespace datalint::utils {
bool TryParseInt(const std::string_view text, int& out) {
  if (text.empty()) {
    return false;
  }

  const char* begin = text.data();
  const char* end = begin + text.size();

  auto [ptr, ec] = std::from_chars(begin, end, out);

  // Must consume the entire string and succeed
  return ec == std::errc{} && ptr == end;
}
}  // namespace datalint::utils
