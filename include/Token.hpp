#pragma once
#include <string>

enum class TokenType {
  Identifier,
  Boolean,
  Number,
  Character,
  String,
  OpenParen,
  CloseParen,
  Dot,
  Quote,
  Comment,
  Unknown
};

struct Token {
  TokenType type;
  std::string value;
  size_t line;
  size_t column;
};
