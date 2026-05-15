#pragma once
#include "ITokenProcessor.hpp"
#include <regex>
namespace scheme::lexer {

/**
 * @brief Processor xử lý các loại số trong Scheme theo R5RS.
 * Hỗ trợ hệ cơ số (#b, #o, #d, #x), số thực, và ký hiệu khoa học.
 */
class OperatorProcessor final : public ITokenProcessor {
public:
  OperatorProcessor();

  // Chỉ giữ lại hàm cần thiết từ ITokenProcessor
  // Sử dụng 'final' để tối ưu hóa vtable (devirtualization)
  std::optional<Token> try_process(std::string_view input, size_t line,
                                   size_t col) override;

private:
  std::regex m_id_regex;
};

} // namespace scheme::lexer
