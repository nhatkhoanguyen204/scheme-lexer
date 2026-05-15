#pragma once
#include "ITokenProcessor.hpp"
namespace scheme::lexer {

/**
 * @brief Processor xử lý Comment trong Scheme theo R5RS.
 */
class CommentProcessor final : public ITokenProcessor {
public:
  CommentProcessor() = default;

  // Chỉ giữ lại hàm cần thiết từ ITokenProcessor
  // Sử dụng 'final' để tối ưu hóa vtable (devirtualization)
  std::optional<Token> try_process(std::string_view input, size_t line,
                                   size_t col) override;
};

} // namespace scheme::lexer
