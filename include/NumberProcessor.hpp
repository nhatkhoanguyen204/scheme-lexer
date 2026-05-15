#pragma once
#include "ITokenProcessor.hpp"
#include "Token.hpp"
#include <cstddef>
#include <optional>
#include <regex>
#include <string_view>
namespace scheme::lexer {

/**
 * @brief Processor xử lý các loại số trong Scheme theo R5RS.
 * Hỗ trợ hệ cơ số (#b, #o, #d, #x), số thực, và ký hiệu khoa học.
 */
class NumberProcessor final : public ITokenProcessor {
public:
  NumberProcessor();

  // Chỉ giữ lại hàm cần thiết từ ITokenProcessor
  // Sử dụng 'final' để tối ưu hóa vtable (devirtualization)
  std::optional<Token> try_process(std::string_view input, size_t line,
                                   size_t col) override;

private:
  std::regex m_num_regex;
};

} // namespace scheme::lexer
