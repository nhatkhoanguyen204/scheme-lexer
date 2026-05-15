#include "../include/BooleanProcessor.hpp"
#include "../include/IdentifierProcessor.hpp"
#include "../include/LexerEngine.hpp"
#include "../include/LexerError.hpp"
#include "../include/NumberProcessor.hpp"
#include "../include/CommentProcessor.hpp"
#include "../include/Token.hpp"
#include "CharacterProcessor.cpp"
#include "OperatorProcessor.cpp"
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Hệ thống Log chuyên nghiệp
 */
#define LOG_ERROR(msg) std::cerr << "[ERROR] " << msg << "\n"
#define LOG_INFO(msg) std::cout << "[INFO] " << msg << "\n"

using namespace scheme::lexer;

/**
 * Chuyển đổi TokenType sang chuỗi để hiển thị
 */
std::string to_string(TokenType type) {
  switch (type) {
  case TokenType::Identifier:
    return "Identifier";
  case TokenType::Boolean:
    return "Boolean";
  case TokenType::Number:
    return "Number";
  case TokenType::Character:
    return "Character";
  case TokenType::String:
    return "String";
  case TokenType::OpenParen:
    return "OpenParen";
  case TokenType::CloseParen:
    return "CloseParen";
  case TokenType::VectorLiteral:
    return "VectorLiteral";
  case TokenType::Quote:
    return "Quote";
  case TokenType::Quasiquote:
    return "Quasiquote";
  case TokenType::Unquote:
    return "Unquote";
  case TokenType::UnquoteSplicing:
    return "UnquoteSplicing";
  case TokenType::Dot:
    return "Dot";
  case TokenType::Comment:
    return "Comment";
  default:
    return "Unknown";
  }
}

/**
 * Đọc nội dung file an toàn
 */
std::string read_file(const std::string &path) {
  std::ifstream file(path, std::ios::in | std::ios::binary);
  if (!file) {
    throw std::runtime_error("Cannot open: " + path);
  }

  std::ostringstream contents;
  contents << file.rdbuf();
  return contents.str();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Running: " << argv[0] << " <file_scheme.in>\n";
    return 1;
  }

  const std::string input_path = argv[1];

  try {
    // 1. Khởi tạo Engine
    auto engine = std::make_unique<LexerEngine>();

    // 2. Đăng ký các Processor (Tuân thủ nguyên lý Dependency Injection)
    engine->register_processor(std::make_unique<CommentProcessor>());
    engine->register_processor(std::make_unique<NumberProcessor>());
    engine->register_processor(std::make_unique<IdentifierProcessor>());
    engine->register_processor(std::make_unique<BooleanProcessor>());
    engine->register_processor(std::make_unique<CharacterProcessor>());
    engine->register_processor(std::make_unique<OperatorProcessor>());

    // 3. Xử lý Input
    std::string source_code = read_file(input_path);

    // 4. Phân tích từ pháp
    LOG_INFO("Analyzing file: " << input_path);
    std::vector<Token> tokens = engine->tokenize(source_code);

    // 5. In kết quả theo định dạng chuẩn
    std::cout << "\n" << std::string(30, '=') << "\n";
    std::cout << "   LEXER ANALYSIS RESULT\n";
    std::cout << std::string(30, '=') << "\n";

    for (const auto &token : tokens) {
      printf("[Pos %zu:%zu] %-12s | Value : '%s'\n", token.line, token.column,
        to_string(token.type).c_str(), token.value.c_str());
    }

    std::cout << std::string(30, '=') << "\n";
    LOG_INFO("Completed: Found " << tokens.size() << " tokens.");

  } catch (const LexerError
               &e) { // Giả định class là LexerException theo các log trước
    LOG_ERROR("Lexer Error: " << e.what() << " [Line " << e.line() << ", Col "
                            << e.column() << "]");
    return 1;
  } catch (const std::exception &e) {
    LOG_ERROR("Execution error: " << e.what());
    return 1;
  }

  return 0;
}
