#include <string>  // for basic_string

#include "gtest/gtest.h"  // for Test, Message, CmpHelperNE

#include "mamba/builtins/types.hpp"  // for IntType
#include "value_wrapper.hpp"         // for Wrapper

namespace mamba::builtins::test {

using namespace mamba::test;

TEST(Operators, ValueEqualityAndInequality) {
  // If
  const IntType i = 1;
  const IntType j = 2;
  const IntType k = 1;

  // When/then
  EXPECT_NE(i, j);
  EXPECT_EQ(i, k);
}

TEST(Operators, ObjectEqualityAndInequality) {
  // If
  const Wrapper<IntType> i(1);
  const Wrapper<IntType> j(2);
  const Wrapper<IntType> k(1);

  // When/then
  EXPECT_NE(i, j);
  EXPECT_EQ(i, k);
}

}  // namespace mamba::builtins::test
