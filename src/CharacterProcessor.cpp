#include "../include/ITokenProcessor.hpp"
#include <regex>

/**
 * @class CharacterProcessor
 * @brief Xử lý các token dạng #\char.
 * Áp dụng Single Responsibility: Chỉ tập trung vào việc trích xuất ký tự.
 */
class CharacterProcessor : public ITokenProcessor {
private:
  std::vector<std::string> results;
  const std::regex char_regex{R"(#\\(\w+|.))"};

public:
  bool can_handle(const std::string &filename) const override {
    return filename.find("character-tokens") != std::string::npos;
  }

  void process(const std::string &line) override {
    std::smatch match;
    std::string::const_iterator search_start(line.cbegin());
    while (std::regex_search(search_start, line.cend(), match, char_regex)) {
      results.push_back("(character " + match.str(0) + ")");
      search_start = match.suffix().first;
    }
  }

  std::vector<std::string> get_results() const override { return results; }
  void clear() override { results.clear(); }
};
