#include "../include/ITokenProcessor.hpp"
#include <fstream>
#include <memory>
#include <stdexcept>

class LexerEngine {
private:
  std::vector<std::unique_ptr<ITokenProcessor>> processors;

public:
  void register_processor(std::unique_ptr<ITokenProcessor> processor) {
    processors.push_back(std::move(processor));
  }

  void run(const std::string &input_path) {
    std::ifstream file(input_path);
    if (!file.is_open()) {
      throw std::runtime_error("Could not open file: " + input_path);
    }

    ITokenProcessor *handler = nullptr;
    for (auto &p : processors) {
      if (p->can_handle(input_path)) {
        handler = p.get();
        break;
      }
    }

    if (!handler)
      throw std::invalid_argument("No processor found for this file type.");

    std::string line;
    while (std::getline(file, line)) {
      handler->process(line);
    }

    for (const auto &res : handler->get_results()) {
      printf("%s\n", res.c_str());
    }
  }
};
