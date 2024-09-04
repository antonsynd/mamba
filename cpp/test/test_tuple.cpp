#include <string>  // for basic_string

#include "gtest/gtest.h"  // for Test, TEST

#include "mamba/builtins/int.hpp"    // for Int
#include "mamba/builtins/tuple.hpp"  // for Tuple

namespace mamba::builtins::test {

TEST(Tuple, EmptyConstructor) {
  // If/when
  const Tuple<Int> t;

  // Then
  EXPECT_EQ(t.Len(), 0);
}

}  // namespace mamba::builtins::test
