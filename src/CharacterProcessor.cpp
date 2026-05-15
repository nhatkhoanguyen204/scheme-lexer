#include "../include/ITokenProcessor.hpp"
#include "../include/Token.hpp"
#include <array>
#include <cstddef>
#include <optional>
#include <string>
#include <string_view>

namespace scheme::lexer {

/**
 * @class CharacterProcessor
 * @brief Xử lý Character Tokens (#\...) và String Tokens ("...") theo chuẩn
 * Scheme. Đã tối ưu hóa bằng cách duyệt thủ công (Manual Scanning) thay vì
 * Regex.
 */
class CharacterProcessor : public ITokenProcessor {
public:
  std::optional<Token> try_process(std::string_view input, size_t line,
                                   size_t col) override {
    if (input.empty())
      return std::nullopt;

    // 1. Xử lý Character Token: #\<char> hoặc #\<name>
    if (input.starts_with("#\\")) {
      return handle_character(input, line, col);
    }

    // 2. Xử lý String Token: "..."
    if (input.front() == '"') {
      return handle_string(input, line, col);
    }

    return std::nullopt;
  }

private:
  // Xử lý logic cho Character (#\space, #\newline, #\a)
  std::optional<Token> handle_character(std::string_view input, size_t line,
                                        size_t col) {
    // Độ dài tối thiểu của một character token là 3 (ví dụ: #\a)
    if (input.length() < 3)
      return std::nullopt;

    std::string_view remaining = input.substr(2); // Bỏ qua #\

    // Kiểm tra các tên ký tự đặc biệt (ưu tiên tên dài trước)
    static constexpr std::array<std::string_view, 2> named_chars = {"newline",
                                                                    "space"};
    for (auto name : named_chars) {
      if (remaining.starts_with(name)) {
        return Token{TokenType::Character,
                     std::string(input.substr(0, 2 + name.length())), line,
                     col};
      }
    }

    // Nếu không phải tên đặc biệt, nó là một ký tự đơn đơn lẻ
    return Token{TokenType::Character, std::string(input.substr(0, 3)), line,
                 col};
  }

  // Xử lý logic cho String với hỗ trợ Escape Sequence
  std::optional<Token> handle_string(std::string_view input, size_t line,
                                     size_t col) {
    size_t pos = 1; // Bắt đầu sau dấu " đầu tiên
    bool escaped = false;

    while (pos < input.length()) {
      char current = input[pos];

      if (escaped) {
        escaped = false; // Ký tự sau \ luôn được chấp nhận
      } else if (current == '\\') {
        escaped = true;
      } else if (current == '"') {
        // Kết thúc chuỗi hợp lệ
        return Token{TokenType::String, std::string(input.substr(0, pos + 1)),
                     line, col};
      }
      pos++;
    }

    // Lỗi: Chuỗi không có dấu đóng ngoặc (Unterminated string)
    return Token{TokenType::Unknown, std::string(input), line, col};
  }
};

} // namespace scheme::lexer
