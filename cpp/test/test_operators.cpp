#include <string>  // for basic_string

#include "gtest/gtest.h"  // for Test, Message, CmpHelperNE

#include "mamba/__test/value_wrapper.hpp"  // for Wrapper
#include "mamba/builtins/int.hpp"          // for IntType

namespace mamba::builtins::test {

using namespace __test;

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
