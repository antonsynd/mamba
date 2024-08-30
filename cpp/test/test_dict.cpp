#include "gtest/gtest.h"  // for Test, TEST

#include "mamba/builtins/dict.hpp"  // for Dict
#include "mamba/builtins/int.hpp"   // for Int

namespace mamba::builtins::test {

TEST(Dict, EmptyConstructor) {
  // If/when
  const Dict<Int, Int> d;

  // Then
  EXPECT_EQ(d.Len(), 0);
}

}  // namespace mamba::builtins::test
