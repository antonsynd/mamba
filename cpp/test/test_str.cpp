#include <string>  // for basic_string

#include "gtest/gtest.h"  // for Test, TEST

#include "mamba/builtins/__concepts/object_like.hpp"  // for ObjectLike
#include "mamba/builtins/str.hpp"                     // for Int

namespace mamba::builtins::test {

TEST(Str, IsObjectLike) {
  // If/when/then
  static_assert(__concepts::ObjectLike<StrType>);
}

}  // namespace mamba::builtins::test
