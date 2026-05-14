#pragma once
#include <string>
#include <vector>

/**
 * @brief Interface cho các bộ xử lý Token.
 * Tuân thủ nguyên tắc Interface Segregation.
 */
class ITokenProcessor {
public:
  virtual ~ITokenProcessor() = default;
  virtual bool can_handle(const std::string &filename) const = 0;
  virtual void process(const std::string &line) = 0;
  virtual std::vector<std::string> get_results() const = 0;
  virtual void clear() = 0;
};
