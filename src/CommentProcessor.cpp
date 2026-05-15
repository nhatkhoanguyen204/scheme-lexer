#include "../include/CommentProcessor.hpp"

namespace scheme::lexer{
    std::optional<Token> CommentProcessor::try_process(std::string_view input, size_t line,
                                   size_t col){
    if (input.empty() || input[0] != ';') {
      return std::nullopt;
    }

    size_t length = 0;
    while (length < input.size() && input[length] != '\n') {
      length++;
    }

    return Token{TokenType::Comment, std::string(input.substr(0, length)), line, col};
  }
}