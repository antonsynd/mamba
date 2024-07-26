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
  EXPECT_FALSE(In(l, 1));
}

TEST(List, InNotActuallyIn) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_FALSE(In(l, 4));
}

TEST(List, InActuallyIn) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_TRUE(In(l, 5));
}

TEST(List, ClearEmpty) {
  // If
  List<Int> l;

  // When
  l.Clear();

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, ClearNonEmpty) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Clear();

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, CopyEmpty) {
  // If
  const List<Int> l;

  // When
  auto copy = l.Copy();
  copy.Append(5);

  // Then
  EXPECT_NE(&l, &copy);
  EXPECT_NE(Len(l), Len(copy));
}

TEST(List, CopyNonEmpty) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  auto copy = l.Copy();
  copy.Append(9);

  // Then
  const auto actual_l_items = as_vector(l);
  const std::vector<Int> expected_l_items = {1, 3, 5, 7};
  EXPECT_EQ(actual_l_items, expected_l_items);

  const auto actual_copy_items = as_vector(copy);
  const std::vector<Int> expected_copy_items = {1, 3, 5, 7, 9};
  EXPECT_EQ(actual_copy_items, expected_copy_items);
}

TEST(List, ExtendEmptyAndEmptyOther) {
  // If
  List<Int> l;
  const List<Int> other;

  // When
  l.Extend(other);

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, ExtendEmptyAndNonEmptyOther) {
  // If
  List<Int> l;
  const List<Int> other = {1, 3, 5, 7};

  // When
  l.Extend(other);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, ExtendNonEmptyAndNonEmptyOther) {
  // If
  List<Int> l = {9, 11, 13};
  const List<Int> other = {1, 3, 5, 7};

  // When
  l.Extend(other);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {9, 11, 13, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, AdditionAssignmentOperator) {
  // If
  List<Int> l = {9, 11, 13};
  const List<Int> other = {1, 3, 5, 7};

  // When
  l += other;

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {9, 11, 13, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, AdditionOperator) {
  // If
  const List<Int> l = {9, 11, 13};
  const List<Int> other = {1, 3, 5, 7};

  // When
  const auto sum = l + other;

  // Then
  const auto actual = as_vector(sum);
  const std::vector<Int> expected = {9, 11, 13, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, MultiplicationOperatorNegative) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto product = l * -1;

  // Then
  EXPECT_EQ(Len(product), 0);
}

TEST(List, MultiplicationOperatorZero) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto product = l * 0;

  // Then
  EXPECT_EQ(Len(product), 0);
}

TEST(List, MultiplicationOperatorOne) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto product = l * 1;

  // Then
  const auto actual = as_vector(product);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, MultiplicationOperatorMoreThanOne) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto product = l * 3;

  // Then
  const auto actual = as_vector(product);
  const std::vector<Int> expected = {1, 3, 5, 7, 1, 3, 5, 7, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, MultiplicationAssignmentOperatorNegative) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l *= -1;

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, MultiplicationAssignmentOperatorZero) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l *= 0;

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, MultiplicationAssignmentOperatorOne) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l *= 1;

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, MultiplicationAssignmentOperatorMoreThanOne) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l *= 3;

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7, 1, 3, 5, 7, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

}  // namespace mamba::builtins::test
