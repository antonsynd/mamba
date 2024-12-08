#pragma once

#include <iostream>
#include <ostream>

#include "mamba/builtins/__utils/string_builder.hpp"

namespace mamba::builtins::log {

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

  template <builtins::details::NotFlush T>
  StringBuilderWrapper& operator<<(const T& t) {
    builder_ << t;
    return *this;
  }

 private:
  std::ostream& stream_;
  builtins::details::StringBuilder builder_;
};

}  // namespace details

details::StringBuilderWrapper Error() {
  return details::StringBuilderWrapper(std::cerr);
}

details::StringBuilderWrapper Warning() {
  return details::StringBuilderWrapper(std::cerr);
}

details::StringBuilderWrapper Debug() {
  return details::StringBuilderWrapper(std::cerr);
}

details::StringBuilderWrapper Info() {
  return details::StringBuilderWrapper(std::cout);
}

}  // namespace mamba::builtins::log
