#include "../include/LexerEngine.hpp"
#include "../include/LexerError.hpp"
#include "../include/ITokenProcessor.hpp"
#include "../include/Token.hpp"
#include <cctype>
#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace scheme::lexer {

void LexerEngine::register_processor(
    std::unique_ptr<ITokenProcessor> processor) {
  if (processor) {
    m_processors.push_back(std::move(processor));
  }
}

std::vector<Token> LexerEngine::tokenize(std::string_view content) {
  std::vector<Token> tokens;
  size_t line = 1;
  size_t col = 1;

  while (!content.empty()) {
    // 1. Xử lý khoảng trắng (Whitespace)
    if (std::isspace(static_cast<unsigned char>(content[0]))) {
      if (content[0] == '\n') {
        line++;
        col = 1;
      } else {
        col++;
      }
      content.remove_prefix(1);
      continue;
    }

    // 2. Duyệt qua các Processors đã đăng ký (Chain of Responsibility)
    bool matched = false;
    for (const auto &processor : m_processors) {
      auto token_opt = processor->try_process(content, line, col);

      if (token_opt.has_value()) {
        const auto &token = *token_opt;
        size_t consumed_length = token.value.length();

        // Cập nhật trạng thái Lexer
        content.remove_prefix(consumed_length);
        col += consumed_length;
        if (token.type != TokenType::Comment){
          tokens.push_back(token);
        }

        matched = true;
        break; // Tìm thấy token, chuyển sang ký tự tiếp theo của content
      }
    }

    // 3. Xử lý lỗi nếu không Processor nào nhận diện được chuỗi ký tự
    if (!matched) {
      throw LexerError(LexerError::ErrorType::InvalidCharacter, // Type
                       line,                                    // Line
                       col,                                     // Col
                       "Unexpected character: '" + std::string(1, content[0]) +
                           "'" // Details
      );
    }
  }

  return tokens;
}

} // namespace scheme::lexer
