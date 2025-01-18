#include "mamba/__utils/logger.hpp"

#include <iostream>  // for cerr, cout
#include <ostream>   // for ostream
#include <string>    // for basic_string

#include "mamba/__utils/string_builder.hpp"  // for Flush, stringify, String...

namespace mamba::__utils {
namespace details {

StringBuilderWrapper::StringBuilderWrapper(std::ostream& stream)
    : stream_(stream), builder_(stringify()) {}

StringBuilderWrapper::~StringBuilderWrapper() {
  stream_ << (builder_ << "\n" << Flush());
}

}  // namespace details

details::StringBuilderWrapper Logger::Error() {
  return details::StringBuilderWrapper(std::cerr);
}

details::StringBuilderWrapper Logger::Warning() {
  return details::StringBuilderWrapper(std::cerr);
}

details::StringBuilderWrapper Logger::Debug() {
  return details::StringBuilderWrapper(std::cout);
}

details::StringBuilderWrapper Logger::Info() {
  return details::StringBuilderWrapper(std::cout);
}

}  // namespace mamba::__utils
