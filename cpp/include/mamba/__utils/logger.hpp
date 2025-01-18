#pragma once

#include <ostream>  // for ostream

#include "mamba/__utils/string_builder.hpp"  // for NotFlush, StringBuilder

namespace mamba::__utils {
namespace details {

class StringBuilderWrapper {
 public:
  StringBuilderWrapper(std::ostream& stream);
  ~StringBuilderWrapper();

  StringBuilderWrapper(const StringBuilderWrapper&) = delete;
  StringBuilderWrapper(StringBuilderWrapper&&) = delete;

  StringBuilderWrapper& operator=(const StringBuilderWrapper&) = delete;
  StringBuilderWrapper& operator=(StringBuilderWrapper&&) = delete;

  template <details::NotFlush T>
  StringBuilderWrapper& operator<<(const T& t) {
    builder_ << t;
    return *this;
  }

 private:
  std::ostream& stream_;
  details::StringBuilder builder_;
};

}  // namespace details

struct Logger {
 public:
  Logger() = delete;

  static details::StringBuilderWrapper Error();
  static details::StringBuilderWrapper Warning();
  static details::StringBuilderWrapper Debug();
  static details::StringBuilderWrapper Info();
};

}  // namespace mamba::__utils
