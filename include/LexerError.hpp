#pragma once
#include <cstddef>
#include <exception>
#include <format>
#include <string>

namespace scheme::lexer {

class LexerError : public std::exception {
public:
  enum class ErrorType {
    InvalidCharacter,
    UnterminatedString,
    InvalidNumberFormat,
    UnexpectedEndOfInput
  };

  LexerError(ErrorType type, size_t line, size_t col,
             const std::string &details)
      : m_line(line), m_col(col),
        m_msg(std::format("Lexer Error [Line {}:{}]: {} ({})", line, col,
                          details, as_string(type))) {}

  const char *what() const noexcept override { return m_msg.c_str(); }

  size_t line() const { return m_line; }
  size_t column() const { return m_col; }

private:
  size_t m_line;
  size_t m_col;
  std::string m_msg;

  static std::string as_string(ErrorType type) {
    switch (type) {
    case ErrorType::InvalidCharacter:
      return "Invalid Character";
    case ErrorType::UnterminatedString:
      return "Unterminated String";
    case ErrorType::InvalidNumberFormat:
      return "Invalid Number Format";
    case ErrorType::UnexpectedEndOfInput:
      return "Unexpected End of Input";
    default:
      return "Unknown Error";
    }
  }
};

} // namespace scheme::lexer
