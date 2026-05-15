#pragma once
#include "Token.hpp"
#include <optional>
#include <string_view>
namespace scheme::lexer {

class ITokenProcessor {
public:
  virtual ~ITokenProcessor() = default;

  // Trích xuất token từ vị trí hiện tại trong string_view
  // Đảm bảo không copy string để tối ưu hiệu năng
  virtual std::optional<Token> try_process(std::string_view input, size_t line,
                                           size_t col) = 0;
};

} // namespace scheme::lexer
