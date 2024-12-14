#pragma once

#include <iostream>
#include <ostream>

#include "mamba/__utils/string_builder.hpp"

namespace mamba::__utils {
namespace details {

class StringBuilderWrapper {
 public:
  StringBuilderWrapper(std::ostream& stream)
      : stream_(stream), builder_(stringify()) {}

  ~StringBuilderWrapper() { stream_ << (builder_ << "\n" << Flush()); }

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

  inline static details::StringBuilderWrapper Error() {
    return details::StringBuilderWrapper(std::cerr);
  }

  inline static details::StringBuilderWrapper Warning() {
    return details::StringBuilderWrapper(std::cerr);
  }

  inline static details::StringBuilderWrapper Debug() {
    return details::StringBuilderWrapper(std::cout);
  }

  inline static details::StringBuilderWrapper Info() {
    return details::StringBuilderWrapper(std::cout);
  }
};

}  // namespace mamba::__utils
