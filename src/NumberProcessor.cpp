#include "../include/NumberProcessor.hpp"

namespace scheme::lexer {

NumberProcessor::NumberProcessor() {
  // Regex hỗ trợ: Radix (#b, #o, #d, #x), Dấu (+, -), Số thực (1.2), Exponent
  // (1e10) Dựa trên Formal Syntax Section 7.1.1
  m_num_regex = std::regex(
      R"(^((#[bodx][ei]?|#[ei]?[bodx]?)?[+-]?(\d+(\.\d*)?|\.\d+)([esfdl][+-]?\d+)?))",
      std::regex::icase);
}

std::optional<Token> NumberProcessor::try_process(std::string_view input,
                                                  size_t line, size_t col) {
  std::cmatch match;
  auto str_begin = input.data();
  auto str_end = str_begin + input.size();

  if (std::regex_search(str_begin, str_end, match, m_num_regex)) {
    return Token{TokenType::Number, match.str(), line, col};
  }
  return std::nullopt;
}

} // namespace scheme::lexer
