#pragma once
#include <string>

#include "mamba/types.hpp"

namespace mamba {

class String final
    : public internal::ValueType<std::string,
                                 internal::GetValueReturnType::kReference> {
 public:
  String(std::string v = "") : internal::ValueType<std::string>(std::move(v)) {}
};

}  // namespace mamba
