#pragma once
#include "ITokenProcessor.hpp"
#include "Token.hpp"
#include <memory>
#include <string_view>
#include <vector>
namespace scheme::lexer {

/**
 * @class LexerEngine
 * @brief Thành phần điều phối chính (Orchestrator) chuyển đổi mã nguồn Scheme
 * thành danh sách Token.
 * * Áp dụng nguyên lý Open/Closed: Có thể mở rộng khả năng nhận diện Token mới
 * bằng cách đăng ký thêm ITokenProcessor mà không cần sửa đổi logic cốt lõi.
 */
class LexerEngine {
public:
  // C++20: Sử dụng default constructor
  LexerEngine() = default;

  // Ngăn chặn việc copy Engine để tránh quản lý sai các unique_ptr
  LexerEngine(const LexerEngine &) = delete;
  LexerEngine &operator=(const LexerEngine &) = delete;

  /**
   * @brief Đăng ký một bộ xử lý token mới (ví dụ: NumberProcessor,
   * BooleanProcessor)
   * @param processor Con trỏ unique quản lý vòng đời của processor
   */
  void register_processor(std::unique_ptr<ITokenProcessor> processor);

  /**
   * @brief Thực hiện quá trình phân tích từ vựng
   * @param content Chuỗi mã nguồn cần phân tích (dưới dạng string_view để tối
   * ưu)
   * @return std::vector<Token> Danh sách các token hợp lệ
   * @throws LexerException Nếu gặp ký tự không hợp lệ theo đặc tả Scheme
   */
  std::vector<Token> tokenize(std::string_view content);

private:
  // Danh sách các chiến lược xử lý (Strategy Pattern kết hợp Chain of
  // Responsibility)
  std::vector<std::unique_ptr<ITokenProcessor>> m_processors;
};

} // namespace scheme::lexer
