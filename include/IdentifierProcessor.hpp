#pragma once
#include "ITokenProcessor.hpp"
#include <regex>
namespace scheme::lexer {

/**
 * @brief Processor xử lý Identifier trong Scheme theo R5RS.
 */
class IdentifierProcessor final : public ITokenProcessor {
public:
  IdentifierProcessor();

  // Chỉ giữ lại hàm cần thiết từ ITokenProcessor
  // Sử dụng 'final' để tối ưu hóa vtable (devirtualization)
  std::optional<Token> try_process(std::string_view input, size_t line,
                                   size_t col) override;

private:
  std::regex m_id_regex;
};

} // namespace scheme::lexer
