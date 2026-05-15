#include "../include/ITokenProcessor.hpp"
#include <regex>
#include <string>
#include <vector>

/**
 * @class CharacterProcessor
 * @brief Chuyên biệt xử lý các token ký tự đặc biệt (ví dụ: #\space, #\a).
 */
class CharacterProcessor : public ITokenProcessor {
private:
  std::vector<std::string> m_results;
  const std::regex m_char_regex{R"(#\\(\w+|.))"};

public:
  bool can_handle(const std::string &filename) const override {
    // Kiểm tra xem file có chứa từ khóa character-tokens không
    return filename.find("character-tokens") != std::string::npos;
  }

  void process(const std::string &line) override {
    std::smatch match;
    auto search_start = line.cbegin();
    while (std::regex_search(search_start, line.cend(), match, m_char_regex)) {
      m_results.push_back("(character " + match.str(1) + ")");
      search_start = match.suffix().first;
    }
  }

  std::vector<std::string> get_results() const override { return m_results; }

  void clear() override { m_results.clear(); }
};
