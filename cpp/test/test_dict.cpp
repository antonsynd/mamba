#include <string>  // for basic_string

#include "gtest/gtest.h"  // for Test, TEST

#include "mamba/dict.hpp"       // for Dict
#include "mamba/types/int.hpp"  // for Int

namespace mamba::builtins::test {

TEST(Dict, EmptyConstructor) {
  // If/when
  Dict<types::Int, types::Int> d;

  // Then
  EXPECT_EQ(d.Len(), 0);
}

}  // namespace mamba::builtins::test
