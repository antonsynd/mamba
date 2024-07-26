#include <gtest/gtest.h>

#include <vector>

#include "mamba/int.hpp"
#include "mamba/list.hpp"

namespace mamba::builtins::test {
namespace {

template <typename T>
std::vector<T> as_vector(const List<T>& l) {
  std::vector<T> res;

  for (size_t i = 0; i < Len(l); ++i) {
    res.emplace_back(l[i]);
  }

  return res;
}

}  // anonymous namespace

TEST(List, EmptyConstructor) {
  // If/when
  const List<Int> l;

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, VariadicConstructor) {
  // If/when
  const List<Int> l(1, 3, 5, 7);

  // Then
  ASSERT_EQ(Len(l), 4);

  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InitializerListConstructor) {
  // If/when
  const List<Int> l = {1, 3, 5, 7};

  // Then
  ASSERT_EQ(Len(l), 4);

  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, AppendOneElement) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Append(9);

  // Then
  ASSERT_EQ(Len(l), 5);

  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, AppendVariadicElements) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Append(9, 11, 13);

  // Then
  ASSERT_EQ(Len(l), 7);

  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7, 9, 11, 13};

  EXPECT_EQ(actual, expected);
}

TEST(List, InEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_FALSE(l.In(1));
}

TEST(List, InNotActuallyIn) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_FALSE(l.In(4));
}

TEST(List, InActuallyIn) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_TRUE(l.In(5));
}

}  // namespace mamba::builtins::test
