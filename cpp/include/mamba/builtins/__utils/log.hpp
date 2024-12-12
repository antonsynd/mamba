#pragma once

#include <iostream>
#include <ostream>

#include "mamba/builtins/__utils/string_builder.hpp"

namespace mamba::builtins::details {

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

inline details::StringBuilderWrapper Error() {
  return details::StringBuilderWrapper(std::cerr);
}

inline details::StringBuilderWrapper Warning() {
  return details::StringBuilderWrapper(std::cerr);
}

inline details::StringBuilderWrapper Debug() {
  return details::StringBuilderWrapper(std::cerr);
}

inline details::StringBuilderWrapper Info() {
  return details::StringBuilderWrapper(std::cout);
}

}  // namespace mamba::builtins::details
