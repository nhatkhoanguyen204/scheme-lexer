#pragma once
#include <cstddef>
#include <string>

enum class TokenType {
  Identifier,
  Boolean,
  Number,
  Character,
  String,
  OpenParen,
  CloseParen,
  VectorLiteral,
  Quote,
  Quasiquote,
  Unquote,
  UnquoteSplicing,
  Dot,
  Comment,
  Unknown
};

struct Token {
  TokenType type;
  std::string value;
  size_t line;
  size_t column;
};
