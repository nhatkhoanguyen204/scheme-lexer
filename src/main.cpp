#include "../src/lexer_engine.cpp"
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
  // 1. Kiểm tra tham số đầu vào (Safety First)
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
    return 1;
  }

  const std::string inputPath = argv[1];

  try {
    // 2. Khởi tạo Engine (Composition Root)
    auto engine = std::make_unique<LexerEngine>();
  } catch (const std::invalid_argument &e) {
    LOG_ERROR("Configuration Error: " + std::string(e.what()));
    return 1;
  } catch (const std::runtime_error &e) {
    LOG_ERROR("Runtime Error: " + std::string(e.what()));
    return 1;
  } catch (const std::exception &e) {
    LOG_ERROR("Unknown System Error: " + std::string(e.what()));
    return 1;
  }

  return 0;
}
