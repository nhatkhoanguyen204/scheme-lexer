#pragma once
#include "ITokenProcessor.hpp"
#include "Token.hpp"
#include <cstddef>
#include <optional>
#include <regex>
#include <string_view>
namespace scheme::lexer {

class BooleanProcessor : public ITokenProcessor {
public:
  BooleanProcessor();

  // Chỉ override hàm có trong ITokenProcessor
  std::optional<Token> try_process(std::string_view input, size_t line,
                                   size_t col) override;

private:
  std::regex m_bool_regex;
};

} // namespace scheme::lexer
