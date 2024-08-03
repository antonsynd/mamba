#include <gtest/gtest.h>

#include <vector>

#include "mamba/conversion.hpp"
#include "mamba/int.hpp"
#include "mamba/list.hpp"
#include "mamba/sequence.hpp"

namespace mamba::builtins::types::test {
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

TEST(List, GetByPositiveIndex) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(l[0], 1);
  EXPECT_EQ(l[1], 3);
  EXPECT_EQ(l[2], 5);
  EXPECT_EQ(l[3], 7);
}

TEST(List, GetByNegativeIndex) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(l[-1], 7);
  EXPECT_EQ(l[-2], 5);
  EXPECT_EQ(l[-3], 3);
  EXPECT_EQ(l[-4], 1);
}

TEST(List, GetByOutOfBounds) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_THROW(l[-5], IndexError);
  EXPECT_THROW(l[4], IndexError);
}

TEST(List, SetByPositiveIndex) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l[2] = 6;

  // Then
  EXPECT_EQ(l[0], 1);
  EXPECT_EQ(l[1], 3);
  EXPECT_EQ(l[2], 6);
  EXPECT_EQ(l[3], 7);
}

TEST(List, SetByNegativeIndex) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l[-3] = 4;

  // Then
  EXPECT_EQ(l[-1], 7);
  EXPECT_EQ(l[-2], 5);
  EXPECT_EQ(l[-3], 4);
  EXPECT_EQ(l[-4], 1);
}

TEST(List, SetByOutOfBounds) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_THROW({ l[-5] = 9; }, IndexError);
  EXPECT_THROW({ l[4] = 11; }, IndexError);
}

TEST(List, LenZero) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, LenNonZero) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(Len(l), 4);
}

TEST(List, MinEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_THROW(Min(l), ValueError);
}

TEST(List, MinNonEmpty) {
  // If
  const List<Int> l = {5, 7, 3, 1};

  // When/then
  EXPECT_EQ(Min(l), 1);
}

TEST(List, MaxEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_THROW(Max(l), ValueError);
}

TEST(List, MaxNonEmpty) {
  // If
  const List<Int> l = {5, 7, 3, 1};

  // When/then
  EXPECT_EQ(Max(l), 7);
}

TEST(List, CountEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_EQ(l.Count(1), 0);
}

TEST(List, CountZero) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(l.Count(9), 0);
}

TEST(List, CountNonZero) {
  // If
  const List<Int> l = {1, 3, 5, 1, 7};

  // When/then
  EXPECT_EQ(l.Count(1), 2);
}

TEST(List, SliceZeroStep) {
  // If
  const List<Int> l = {1, 3, 5, 1, 7};

  // When/then
  EXPECT_THROW(l.Slice(0, 0, 0), ValueError);
}

TEST(List, SliceNegativeStep) {
  // If
  const List<Int> l = {1, 3, 5, 1, 7};

  // When
  const auto actual = l.Slice(0, 1, -1);

  // Then
  EXPECT_EQ(Len(actual), 0);
}

TEST(List, SliceSameStartAndEnd) {
  // If
  const List<Int> l = {1, 3, 5, 1, 7};

  // When
  const auto actual = l.Slice(1, 1);

  // Then
  EXPECT_EQ(Len(actual), 0);
}

TEST(List, SliceSingleStep) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto res = l.Slice(1, 3);

  // Then
  const auto actual = as_vector(res);
  const std::vector<Int> expected = {3, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNotSingleStepNotEnough) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto res = l.Slice(1, 3, 4);

  // Then
  const auto actual = as_vector(res);
  const std::vector<Int> expected = {3};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNotSingleStepEnough) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l.Slice(1, 5, 2);

  // Then
  const auto actual = as_vector(res);
  const std::vector<Int> expected = {3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOutOfBoundsLeft) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l.Slice(-9, 4, 2);

  // Then
  const auto actual = as_vector(res);
  const std::vector<Int> expected = {1, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOutOfBoundsRight) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l.Slice(0, 9, 2);

  // Then
  const auto actual = as_vector(res);
  const std::vector<Int> expected = {1, 5, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNoArgsIsCopy) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l.Slice();

  // Then
  const auto actual = as_vector(res);
  const std::vector<Int> expected = {1, 3, 5, 7, 9};

  EXPECT_EQ(actual, expected);
}

#if __cplusplus >= 202302L
TEST(List, SliceOperator) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l[1, 5, 2];

  // Then
  const auto actual = as_vector(res);
  const std::vector<Int> expected = {3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOperatorWithNoArgsIsCopy) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l[];

  // Then
  const auto actual = as_vector(res);
  const std::vector<Int> expected = {1, 3, 5, 7, 9};

  EXPECT_EQ(actual, expected);
}
#endif  // __cplusplus >= 202302L

TEST(List, ReverseEmpty) {
  // If
  List<Int> l;

  // When
  l.Reverse();

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, ReverseNonEmpty) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Reverse();

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {7, 5, 3, 1};

  EXPECT_EQ(actual, expected);
}

TEST(List, BoolEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_FALSE(conversion::Bool(l));
}

TEST(List, BoolNonEmpty) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_TRUE(conversion::Bool(l));
}

TEST(List, IndexEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_THROW(l.Index(5), ValueError);
}

TEST(List, IndexNonEmpty) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(l.Index(5), 2);
}

TEST(List, RemoveEmpty) {
  // If
  List<Int> l;

  // When/then
  EXPECT_THROW(l.Remove(3), ValueError);
}

TEST(List, RemoveNotPresent) {
  // If
  List<Int> l = {1, 5, 7};

  // When/then
  EXPECT_THROW(l.Remove(3), ValueError);
}

TEST(List, RemovePresentOnce) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Remove(3);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, RemovePresentMoreThanOnce) {
  // If
  List<Int> l = {1, 3, 5, 7, 3};

  // When
  l.Remove(3);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 5, 7, 3};

  EXPECT_EQ(actual, expected);
}

TEST(List, RemoveAtEnd) {
  // If
  List<Int> l = {1, 5, 7, 3};

  // When
  l.Remove(3);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, DeleteSliceZeroStep) {
  // If
  List<Int> l = {1, 3, 5, 1, 7};

  // When/then
  EXPECT_THROW(l.DeleteSlice(0, 0, 0), ValueError);
}

TEST(List, DeleteSliceNegativeStep) {
  // If
  List<Int> l = {1, 3, 5, 1, 7};

  // When
  l.DeleteSlice(0, 1, -1);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 1, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, DeleteSliceSameStartAndEnd) {
  // If
  List<Int> l = {1, 3, 5, 1, 7};

  // When
  l.DeleteSlice(1, 1);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 1, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, DeleteSliceSingleStep) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.DeleteSlice(1, 3);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, DeleteSliceNotSingleStepNotEnough) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.DeleteSlice(1, 3, 4);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, DeleteSliceNotSingleStepEnough) {
  // If
  List<Int> l = {1, 3, 5, 7, 9};

  // When
  l.DeleteSlice(1, 5, 2);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 5, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, DeleteSliceOutOfBoundsLeft) {
  // If
  List<Int> l = {1, 3, 5, 7, 9};

  // When
  l.DeleteSlice(-9, 4, 2);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {3, 7, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, DeleteSliceOutOfBoundsRight) {
  // If
  List<Int> l = {1, 3, 5, 7, 9};

  // When
  l.DeleteSlice(0, 9, 2);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, DeleteSliceNoArgsIsClear) {
  // If
  List<Int> l = {1, 3, 5, 7, 9};

  // When
  l.DeleteSlice();

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, ReplaceSliceZeroStep) {
  // If
  List<Int> l = {1, 3, 5, 1, 7};
  const List<Int> other = {2, 4, 6};

  // When/then
  EXPECT_THROW(l.ReplaceSlice(other, 0, 0, 0), ValueError);
}

TEST(List, ReplaceSliceNegativeStep) {
  // If
  List<Int> l = {1, 3, 5, 1, 7};
  const List<Int> other = {2, 4, 6};

  // When
  l.ReplaceSlice(other, 0, 1, -1);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 1, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, ReplaceSliceSameStartAndEnd) {
  // If
  List<Int> l = {1, 3, 5, 1, 7};
  const List<Int> other = {2, 4, 6};

  // When
  l.ReplaceSlice(other, 1, 1);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 1, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, ReplaceSliceSingleStepMoreNewElems) {
  // If
  List<Int> l = {1, 3, 5, 7};
  const List<Int> other = {2, 4, 6};

  // When
  l.ReplaceSlice(other, 1, 3);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 2, 4, 6, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, ReplaceSliceSingleStepLessNewElems) {
  // If
  List<Int> l = {1, 3, 5, 7};
  const List<Int> other = {2};

  // When
  l.ReplaceSlice(other, 1, 3);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 2, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, ReplaceSliceSingleStepSameNewElems) {
  // If
  List<Int> l = {1, 3, 5, 7};
  const List<Int> other = {2, 4};

  // When
  l.ReplaceSlice(other, 1, 3);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 2, 4, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, ReplaceSliceNotSingleStepNotSameNumElems) {
  // If
  List<Int> l = {1, 3, 5, 7};
  const List<Int> other = {2, 4, 6};

  // When/then
  EXPECT_THROW(l.ReplaceSlice(other, 1, 3, 4), ValueError);
}

TEST(List, ReplaceSliceNotSingleStepSameNumElems) {
  // If
  List<Int> l = {1, 3, 5, 7, 9};
  const List<Int> other = {2, 4};

  // When
  l.ReplaceSlice(other, 1, 4, 2);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 2, 5, 4, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, ReplaceSliceNoArgsIsCompleteReplacement) {
  // If
  List<Int> l = {1, 3, 5, 7, 9};
  const List<Int> other = {2, 4, 6};

  // When
  l.ReplaceSlice(other);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {2, 4, 6};

  EXPECT_EQ(actual, expected);
}

}  // namespace mamba::builtins::types::test
