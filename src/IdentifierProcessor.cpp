#include "../include/IdentifierProcessor.hpp"
#include <regex>
#include <string>

namespace scheme::lexer {

IdentifierProcessor::IdentifierProcessor() {
  m_id_regex = std::regex(
      R"(^(([a-zA-Z!$%&*/:<=>?^_~][a-zA-Z0-9!$%&*\-+./:<=>?@^_~]*)|[+]|[-]|\.\.\.))",
      std::regex::icase);
}

std::optional<Token> IdentifierProcessor::try_process(std::string_view input,
                                                   size_t line, size_t col) {
  std::cmatch match;
  auto str_begin = input.data();
  auto str_end = str_begin + input.size();

  if (std::regex_search(str_begin, str_end, match, m_id_regex)) {
    std::string match_str = match.str();
    for (char& c : match_str) {
      c = std::tolower(c);
    }
    return Token{TokenType::Identifier, match_str, line, col};
  }
  return std::nullopt;
}

} // namespace scheme::lexer
