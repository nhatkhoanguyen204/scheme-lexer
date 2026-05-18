#include "../include/NumberProcessor.hpp"
#include "../include/Token.hpp"
#include "string_view"
#include <cstddef>
#include <string>
#include <optional>
#include <regex>

namespace scheme::lexer {

NumberProcessor::NumberProcessor() {
// 1. Define the REAL number parts for each base (Sign + Digits/Fractions)
  std::string hex_real = R"([+-]?([0-9a-fA-F]+/[0-9a-fA-F]+|[0-9a-fA-F]+))";
  std::string oct_real = R"([+-]?([0-7]+/[0-7]+|[0-7]+))";
  std::string bin_real = R"([+-]?([01]+/[01]+|[01]+))";
  std::string dec_real = R"([+-]?(\d+/\d+|\d+\.\d*([esfdlESFDL][+-]?\d+)?|\.\d+([esfdlESFDL][+-]?\d+)?|\d+([esfdlESFDL][+-]?\d+)?))";

  // 2. Define the PREFIXES for each base
  std::string hex_prefix = R"((#[eEiI]#[xX]|#[xX]#[eEiI]|#[xX]))";
  std::string oct_prefix = R"((#[eEiI]#[oO]|#[oO]#[eEiI]|#[oO]))";
  std::string bin_prefix = R"((#[eEiI]#[bB]|#[bB]#[eEiI]|#[bB]))";
  std::string dec_prefix = R"((#[eEiI]#[dD]|#[dD]#[eEiI]|#[eEiI]|#[dD])?)"; // Decimal prefix is optional

  // 3. Build the final Regexes!
  // Format: ^ Prefix + Real + (Optionally: @ + Real)
  m_hex_regex = std::regex("^" + hex_prefix + hex_real + "(@" + hex_real + ")?", std::regex::icase);
  m_oct_regex = std::regex("^" + oct_prefix + oct_real + "(@" + oct_real + ")?", std::regex::icase);
  m_bin_regex = std::regex("^" + bin_prefix + bin_real + "(@" + bin_real + ")?", std::regex::icase);
  m_dec_regex = std::regex("^" + dec_prefix + dec_real + "(@" + dec_real + ")?", std::regex::icase);
}

std::optional<Token> NumberProcessor::try_process(std::string_view input,
                                                  size_t line, size_t col) {
  std::cmatch match;
  auto str_begin = input.data();
  auto str_end = str_begin + input.size();

  if (std::regex_search(str_begin, str_end, match, m_hex_regex) || std::regex_search(str_begin, str_end, match, m_oct_regex)
    || std::regex_search(str_begin, str_end, match, m_bin_regex) || std::regex_search(str_begin, str_end, match, m_dec_regex)) {
    std::string match_str = match.str();
    for (char &c: match_str){
      c = std::tolower(c);
    }
    return Token{TokenType::Number, match_str, line, col};
  }
  return std::nullopt;
}

} // namespace scheme::lexer
