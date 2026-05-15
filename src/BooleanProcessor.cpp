#include "../include/BooleanProcessor.hpp"
#include <regex>

namespace scheme::lexer {

std::optional<Token> BooleanProcessor::try_process(std::string_view input,
                                                   size_t line, size_t col) {
  // Theo R5RS: boolean là #t hoặc #f (không phân biệt hoa thường)
  static const std::regex bool_regex{R"(^#[tfTF])", std::regex::nosubs};

  std::cmatch match;
  auto str_ptr = input.data();

  if (std::regex_search(str_ptr, str_ptr + input.size(), match, bool_regex)) {
    std::string value(match[0].first, match[0].second);
    return Token{TokenType::Boolean, value, line, col};
  }

  return std::nullopt; // Đã sửa lỗi chuyển đổi nullopt_t
}

} // namespace scheme::lexer
