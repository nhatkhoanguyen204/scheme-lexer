#pragma once
#include "../include/ITokenProcessor.hpp"
namespace scheme::lexer {

/**
 * @brief Processor xử lý các Operator và Delimiter trong Scheme theo R5RS.
 */
class OperatorProcessor final : public ITokenProcessor {
public:
  OperatorProcessor() = default;

  // Chỉ giữ lại hàm cần thiết từ ITokenProcessor
  // Sử dụng 'final' để tối ưu hóa vtable (devirtualization)
  std::optional<Token> try_process(std::string_view input, size_t line,
                                   size_t col) override {
    if (input.empty())
      return std::nullopt;

    switch (input[0])
    {
    case '(':
        return Token{TokenType::OpenParen, std::string(input.substr(0, 1)),
                     line, col};
    case ')':
        return Token{TokenType::CloseParen, std::string(input.substr(0, 1)),
                     line, col};
    case '#':
        if (input.length() < 2 || input[1] != '('){
            return std::nullopt;
        }
        return Token{TokenType::VectorLiteral, std::string(input.substr(0, 2)),
                     line, col};
    case '\'':
        return Token{TokenType::Quote, std::string(input.substr(0, 1)),
                     line, col};
    case '\`':
        return Token{TokenType::Quasiquote, std::string(input.substr(0, 1)),
                     line, col};   
    case ',':
        if (input.length() == 1 || input[1] != '@'){
            return Token{TokenType::Unquote, std::string(input.substr(0, 1)),
                     line, col};
        }
        return Token{TokenType::UnquoteSplicing, std::string(input.substr(0, 2)),
                     line, col};
    case '.':
        return Token{TokenType::Dot, std::string(input.substr(0, 1)),
                     line, col};
    };
    return std::nullopt;
  }
};

} // namespace scheme::lexer
