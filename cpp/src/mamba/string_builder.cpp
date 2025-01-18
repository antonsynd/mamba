#include "mamba/__utils/string_builder.hpp"

#include <sstream>
#include <string>

#include "mamba/builtins/__types/str.hpp"

namespace mamba::__utils {
namespace details {

std::string StringBuilder::operator<<(const Flush&) {
  auto res = oss_.str();

  oss_.clear();

  return res;
}

StringBuilder::operator std::string() const {
  return oss_.str();
}

StringBuilder::operator builtins::details::Str() const {
  return oss_.str();
}

}  // namespace details

details::StringBuilder stringify() {
  return details::StringBuilder();
}

}  // namespace mamba::__utils
