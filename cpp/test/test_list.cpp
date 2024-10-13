#include <stddef.h>  // for size_t

#include <__fwd/sstream.h>  // for ostringstream
#include <memory>           // for shared_ptr, enable_shared_from_this
#include <sstream>          // for basic_ostream, basic_ostringstream
#include <string>           // for basic_string
#include <utility>          // for forward
#include <vector>           // for vector

#include "gtest/gtest.h"  // for Test, Message, TestPartResult, TEST

#include "mamba/__concepts/object.hpp"        // for Object
#include "mamba/__concepts/value.hpp"         // for Value
#include "mamba/__memory/handle.hpp"          // for handle_t, Init
#include "mamba/__memory/read_only.hpp"       // for ReadOnly
#include "mamba/builtins/__as_bool/bool.hpp"  // for AsBool
#include "mamba/builtins/as_str.hpp"          // for AsStr
#include "mamba/builtins/bool.hpp"            // for Bool
#include "mamba/builtins/comparators.hpp"     // for Lt, Eq
#include "mamba/builtins/error.hpp"           // for ValueError, IndexError
#include "mamba/builtins/float.hpp"           // for Float
#include "mamba/builtins/int.hpp"             // for Int
#include "mamba/builtins/iteration.hpp"       // for Iter, Iterator
#include "mamba/builtins/list.hpp"            // for List
#include "mamba/builtins/object.hpp"          // for Str
#include "mamba/builtins/repr.hpp"            // for Repr
#include "mamba/builtins/sequence.hpp"        // for Len, Contains, Max, Min
#include "mamba/builtins/str.hpp"             // for Str

namespace mamba::builtins::test {
namespace {

template <__concepts::Value T>
struct Wrapper : public Object,
                 public std::enable_shared_from_this<Wrapper<T>> {
 public:
  using self = Wrapper;
  using handle = __memory::handle_t<self>;

  static void ResetId() { global_id_ = 0; }
  static size_t GetNextId() { return global_id_++; }

  Wrapper(T value) : v_(value), id_(GetNextId()) {}

  template <typename... Args>
  static handle Init(Args&&... args) {
    return __memory::Init<self>(std::forward<Args>(args)...);
  }

  size_t Id() const { return id_; }
  T Value() const { return v_; }

  Str AsStr() const {
    std::ostringstream oss;
    oss << "[Wrapper(value=" << v_ << ", id=" << id_ << ")]";
    return oss.str();
  }

  operator T() const { return v_; }

  Str Repr() const override { return AsStr(); }

  Bool Eq(const self& other) const { return v_ == other.v_; }
  Bool Eq(const handle& other) const { return v_ == other->v_; }
  Bool Lt(const self& other) const { return v_ < other.v_; }
  Bool Lt(const handle& other) const { return v_ < other.v_; }

 private:
  inline static size_t global_id_ = 0;

  T v_;
  size_t id_;
};

using IntWrapper = Wrapper<Int>;
using FloatWrapper = Wrapper<Float>;

template <typename T, typename U = T>
std::vector<U> as_vector(const List<T>& l) {
  std::vector<U> res;

  for (size_t i = 0; i < Len(l); ++i) {
    if constexpr (__concepts::Object<T>) {
      res.emplace_back(static_cast<const U>(*l[i]));
    } else {
      res.emplace_back(static_cast<const U>(l[i]));
    }
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

TEST(List, EmptyConstructorObject) {
  // If/when
  const List<IntWrapper> l;

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

TEST(List, VariadicConstructorObject) {
  // If/when
  const List<IntWrapper> l(IntWrapper::Init(1), IntWrapper::Init(3),
                           IntWrapper::Init(5), IntWrapper::Init(7));

  // Then
  ASSERT_EQ(Len(l), 4);

  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, InitializerListConstructorObject) {
  // If/when
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // Then
  ASSERT_EQ(Len(l), 4);

  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, IterableConstructor) {
  // If/when
  List<Int> source = {1, 3, 5, 7};
  const List<Int> l{*source.Iter()};

  // Then
  ASSERT_EQ(Len(l), 4);

  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, IterableConstructorObject) {
  // If/when
  List<IntWrapper> source = {IntWrapper::Init(1), IntWrapper::Init(3),
                             IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<IntWrapper> l{*source.Iter()};

  // Then
  ASSERT_EQ(Len(l), 4);

  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, AppendOneElementObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Append(IntWrapper::Init(9));

  // Then
  ASSERT_EQ(Len(l), 5);

  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, AppendVariadicElementsObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Append(IntWrapper::Init(9), IntWrapper::Init(11), IntWrapper::Init(13));

  // Then
  ASSERT_EQ(Len(l), 7);

  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 3, 5, 7, 9, 11, 13};

  EXPECT_EQ(actual, expected);
}

TEST(List, ContainsEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_FALSE(Contains(l, 1));
}

TEST(List, ContainsEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_FALSE(Contains(l, IntWrapper::Init(1)));
}

TEST(List, ContainsNotActuallyIn) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_FALSE(Contains(l, 4));
}

TEST(List, ContainsNotActuallyInObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_FALSE(Contains(l, IntWrapper::Init(4)));
}

TEST(List, ContainsActuallyIn) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_TRUE(Contains(l, 5));
}

TEST(List, ContainsActuallyInObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_FALSE(Contains(l, IntWrapper::Init(5)));
}

TEST(List, ClearEmpty) {
  // If
  List<Int> l;

  // When
  l.Clear();

  // Then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, ClearEmptyObject) {
  // If
  List<IntWrapper> l;

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

TEST(List, ClearNonEmptyObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

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
  copy->Append(5);

  // Then
  EXPECT_NE(&l, copy.get());
  EXPECT_NE(Len(l), Len(*copy));
}

TEST(List, CopyEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When
  auto copy = l.Copy();
  copy->Append(IntWrapper::Init(5));

  // Then
  EXPECT_NE(&l, copy.get());
  EXPECT_NE(Len(l), Len(*copy));
}

TEST(List, CopyNonEmpty) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  auto copy = l.Copy();
  copy->Append(9);

  // Then
  const auto actual_l_items = as_vector(l);
  const std::vector<Int> expected_l_items = {1, 3, 5, 7};
  EXPECT_EQ(actual_l_items, expected_l_items);

  const auto actual_copy_items = as_vector(*copy);
  const std::vector<Int> expected_copy_items = {1, 3, 5, 7, 9};
  EXPECT_EQ(actual_copy_items, expected_copy_items);
}

TEST(List, CopyNonEmptyObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  auto copy = l.Copy();
  copy->Append(IntWrapper::Init(9));

  // Then
  const auto actual_l_items = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected_l_items = {1, 3, 5, 7};
  EXPECT_EQ(actual_l_items, expected_l_items);

  const auto actual_copy_items = as_vector<IntWrapper, Int>(*copy);
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

TEST(List, ExtendEmptyAndEmptyOtherObject) {
  // If
  List<IntWrapper> l;
  const List<IntWrapper> other;

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

TEST(List, ExtendEmptyAndNonEmptyOtherObject) {
  // If
  List<IntWrapper> l;
  const List<IntWrapper> other = {IntWrapper::Init(1), IntWrapper::Init(3),
                                  IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Extend(other);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, ExtendNonEmptyAndNonEmptyOtherObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(9), IntWrapper::Init(11),
                        IntWrapper::Init(13)};
  const List<IntWrapper> other = {IntWrapper::Init(1), IntWrapper::Init(3),
                                  IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Extend(other);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, AdditionAssignmentOperatorObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(9), IntWrapper::Init(11),
                        IntWrapper::Init(13)};
  const List<IntWrapper> other = {IntWrapper::Init(1), IntWrapper::Init(3),
                                  IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l += other;

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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
  const auto actual = as_vector(*sum);
  const std::vector<Int> expected = {9, 11, 13, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, AdditionOperatorObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(9), IntWrapper::Init(11),
                              IntWrapper::Init(13)};
  const List<IntWrapper> other = {IntWrapper::Init(1), IntWrapper::Init(3),
                                  IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  const auto sum = l + other;

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*sum);
  const std::vector<Int> expected = {9, 11, 13, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, MultiplicationOperatorNegative) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto product = l * -1;

  // Then
  EXPECT_EQ(Len(*product), 0);
}

TEST(List, MultiplicationOperatorNegativeObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  const auto product = l * -1;

  // Then
  EXPECT_EQ(Len(*product), 0);
}

TEST(List, MultiplicationOperatorZero) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto product = l * 0;

  // Then
  EXPECT_EQ(Len(*product), 0);
}

TEST(List, MultiplicationOperatorZeroObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  const auto product = l * 0;

  // Then
  EXPECT_EQ(Len(*product), 0);
}

TEST(List, MultiplicationOperatorOne) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto product = l * 1;

  // Then
  const auto actual = as_vector(*product);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, MultiplicationOperatorOneObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  const auto product = l * 1;

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*product);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, MultiplicationOperatorMoreThanOne) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto product = l * 3;

  // Then
  const auto actual = as_vector(*product);
  const std::vector<Int> expected = {1, 3, 5, 7, 1, 3, 5, 7, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, MultiplicationOperatorMoreThanOneObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  const auto product = l * 3;

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*product);
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

TEST(List, MultiplicationAssignmentOperatorNegativeObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

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

TEST(List, MultiplicationAssignmentOperatorZeroObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

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

TEST(List, MultiplicationAssignmentOperatorOneObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l *= 1;

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, MultiplicationAssignmentOperatorMoreThanOneObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l *= 3;

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, GetByPositiveIndexObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_EQ(l[0]->Value(), 1);
  EXPECT_EQ(l[1]->Value(), 3);
  EXPECT_EQ(l[2]->Value(), 5);
  EXPECT_EQ(l[3]->Value(), 7);
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

TEST(List, GetByNegativeIndexObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_EQ(l[-1]->Value(), 7);
  EXPECT_EQ(l[-2]->Value(), 5);
  EXPECT_EQ(l[-3]->Value(), 3);
  EXPECT_EQ(l[-4]->Value(), 1);
}

TEST(List, GetByOutOfBounds) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_THROW(l[-5], IndexError);
  EXPECT_THROW(l[4], IndexError);
}

TEST(List, GetByOutOfBoundsObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

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

TEST(List, SetByPositiveIndexObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l[2] = IntWrapper::Init(6);

  // Then
  EXPECT_EQ(l[0]->Value(), 1);
  EXPECT_EQ(l[1]->Value(), 3);
  EXPECT_EQ(l[2]->Value(), 6);
  EXPECT_EQ(l[3]->Value(), 7);
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

TEST(List, SetByNegativeIndexObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l[-3] = IntWrapper::Init(4);

  // Then
  EXPECT_EQ(l[-1]->Value(), 7);
  EXPECT_EQ(l[-2]->Value(), 5);
  EXPECT_EQ(l[-3]->Value(), 4);
  EXPECT_EQ(l[-4]->Value(), 1);
}

TEST(List, SetByOutOfBounds) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_THROW({ l[-5] = 9; }, IndexError);
  EXPECT_THROW({ l[4] = 11; }, IndexError);
}

TEST(List, SetByOutOfBoundsObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_THROW({ l[-5] = IntWrapper::Init(9); }, IndexError);
  EXPECT_THROW({ l[4] = IntWrapper::Init(11); }, IndexError);
}

TEST(List, LenZero) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, LenZeroObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_EQ(Len(l), 0);
}

TEST(List, LenNonZero) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(Len(l), 4);
}

TEST(List, LenNonZeroObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_EQ(Len(l), 4);
}

TEST(List, MinEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_THROW(Min(l), ValueError);
}

TEST(List, MinEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_THROW(Min(l), ValueError);
}

TEST(List, MinNonEmpty) {
  // If
  const List<Int> l = {5, 7, 3, 1};

  // When/then
  EXPECT_EQ(Min(l), 1);
}

TEST(List, MinNonEmptyObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(5), IntWrapper::Init(7),
                              IntWrapper::Init(3), IntWrapper::Init(1)};

  // When/then
  EXPECT_EQ(Min(l)->Value(), 1);
}

TEST(List, MaxEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_THROW(Max(l), ValueError);
}

TEST(List, MaxEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_THROW(Max(l), ValueError);
}

TEST(List, MaxNonEmpty) {
  // If
  const List<Int> l = {5, 7, 3, 1};

  // When/then
  EXPECT_EQ(Max(l), 7);
}

TEST(List, MaxNonEmptyObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(5), IntWrapper::Init(7),
                              IntWrapper::Init(3), IntWrapper::Init(1)};

  // When/then
  EXPECT_EQ(Max(l)->Value(), 7);
}

TEST(List, CountEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_EQ(l.Count(1), 0);
}

TEST(List, CountEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_EQ(l.Count(IntWrapper::Init(1)), 0);
}

TEST(List, CountZero) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(l.Count(9), 0);
}

TEST(List, CountZeroObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_EQ(l.Count(IntWrapper::Init(9)), 0);
}

TEST(List, CountNonZero) {
  // If
  const List<Int> l = {1, 3, 5, 1, 7};

  // When/then
  EXPECT_EQ(l.Count(1), 2);
}

TEST(List, CountNonZeroObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(1),
                              IntWrapper::Init(7)};

  // When/then
  EXPECT_EQ(l.Count(IntWrapper::Init(1)), 2);
}

TEST(List, SliceZeroStep) {
  // If
  const List<Int> l = {1, 3, 5, 1, 7};

  // When/then
  EXPECT_THROW(l.Slice(0, 0, 0), ValueError);
}

TEST(List, SliceZeroStepObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(1),
                              IntWrapper::Init(7)};

  // When/then
  EXPECT_THROW(l.Slice(0, 0, 0), ValueError);
}

TEST(List, SliceNegativeStep) {
  // If
  const List<Int> l = {1, 3, 5, 1, 7};

  // When
  const auto actual = l.Slice(0, 1, -1);

  // Then
  EXPECT_EQ(Len(*actual), 0);
}

TEST(List, SliceNegativeStepObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(1),
                              IntWrapper::Init(7)};

  // When
  const auto actual = l.Slice(0, 1, -1);

  // Then
  EXPECT_EQ(Len(*actual), 0);
}

TEST(List, SliceSameStartAndEnd) {
  // If
  const List<Int> l = {1, 3, 5, 1, 7};

  // When
  const auto actual = l.Slice(1, 1);

  // Then
  EXPECT_EQ(Len(*actual), 0);
}

TEST(List, SliceSameStartAndEndObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(1),
                              IntWrapper::Init(7)};

  // When
  const auto actual = l.Slice(1, 1);

  // Then
  EXPECT_EQ(Len(*actual), 0);
}

TEST(List, SliceSingleStep) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto res = l.Slice(1, 3);

  // Then
  const auto actual = as_vector(*res);
  const std::vector<Int> expected = {3, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceSingleStepObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  const auto res = l.Slice(1, 3);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*res);
  const std::vector<Int> expected = {3, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNotSingleStepNotEnough) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When
  const auto res = l.Slice(1, 3, 4);

  // Then
  const auto actual = as_vector(*res);
  const std::vector<Int> expected = {3};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNotSingleStepNotEnoughObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  const auto res = l.Slice(1, 3, 4);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*res);
  const std::vector<Int> expected = {3};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNotSingleStepEnough) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l.Slice(1, 5, 2);

  // Then
  const auto actual = as_vector(*res);
  const std::vector<Int> expected = {3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNotSingleStepEnoughObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7),
                              IntWrapper::Init(9)};

  // When
  const auto res = l.Slice(1, 5, 2);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*res);
  const std::vector<Int> expected = {3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOutOfBoundsLeft) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l.Slice(-9, 4, 2);

  // Then
  const auto actual = as_vector(*res);
  const std::vector<Int> expected = {1, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOutOfBoundsLeftObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7),
                              IntWrapper::Init(9)};

  // When
  const auto res = l.Slice(-9, 4, 2);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*res);
  const std::vector<Int> expected = {1, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOutOfBoundsRight) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l.Slice(0, 9, 2);

  // Then
  const auto actual = as_vector(*res);
  const std::vector<Int> expected = {1, 5, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOutOfBoundsRightObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7),
                              IntWrapper::Init(9)};

  // When
  const auto res = l.Slice(0, 9, 2);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*res);
  const std::vector<Int> expected = {1, 5, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNoArgsIsCopy) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l.Slice();

  // Then
  const auto actual = as_vector(*res);
  const std::vector<Int> expected = {1, 3, 5, 7, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceNoArgsIsCopyObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7),
                              IntWrapper::Init(9)};

  // When
  const auto res = l.Slice();

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*res);
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
  const auto actual = as_vector(*res);
  const std::vector<Int> expected = {3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOperatorObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7),
                              IntWrapper::Init(9)};

  // When
  const auto res = l[1, 5, 2];

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*res);
  const std::vector<Int> expected = {3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOperatorWithNoArgsIsCopy) {
  // If
  const List<Int> l = {1, 3, 5, 7, 9};

  // When
  const auto res = l[];

  // Then
  const auto actual = as_vector(*res);
  const std::vector<Int> expected = {1, 3, 5, 7, 9};

  EXPECT_EQ(actual, expected);
}

TEST(List, SliceOperatorWithNoArgsIsCopyObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7),
                              IntWrapper::Init(9)};

  // When
  const auto res = l[];

  // Then
  const auto actual = as_vector<IntWrapper, Int>(*res);
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

TEST(List, ReverseEmptyObject) {
  // If
  List<IntWrapper> l;

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

TEST(List, ReverseNonEmptyObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Reverse();

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {7, 5, 3, 1};

  EXPECT_EQ(actual, expected);
}

TEST(List, BoolEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_FALSE(AsBool(l));
}

TEST(List, BoolEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_FALSE(AsBool(l));
}

TEST(List, BoolNonEmpty) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_TRUE(AsBool(l));
}

TEST(List, BoolNonEmptyObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_TRUE(AsBool(l));
}

TEST(List, IndexEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_THROW(l.Index(5), ValueError);
}

TEST(List, IndexEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_THROW(l.Index(IntWrapper::Init(5)), ValueError);
}

TEST(List, IndexNonEmpty) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(l.Index(5), 2);
}

TEST(List, IndexNonEmptyObjectSame) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  const auto third_elem = l[2];
  EXPECT_EQ(l.Index(third_elem), 2);
}

TEST(List, IndexNonEmptyObjectNotSame) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_THROW(l.Index(IntWrapper::Init(5)), ValueError);
}

TEST(List, RemoveEmpty) {
  // If
  List<Int> l;

  // When/then
  EXPECT_THROW(l.Remove(3), ValueError);
}

TEST(List, RemoveEmptyObject) {
  // If
  List<IntWrapper> l;

  // When/then
  EXPECT_THROW(l.Remove(IntWrapper::Init(3)), ValueError);
}

TEST(List, RemoveNotPresent) {
  // If
  List<Int> l = {1, 5, 7};

  // When/then
  EXPECT_THROW(l.Remove(3), ValueError);
}

TEST(List, RemoveNotPresentObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(5),
                        IntWrapper::Init(7)};

  // When/then
  EXPECT_THROW(l.Remove(IntWrapper::Init(3)), ValueError);
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

TEST(List, RemovePresentOnceObjectSame) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  const auto second_elem = l[1];
  l.Remove(second_elem);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, RemovePresentOnceObjectNotSame) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_THROW(l.Remove(IntWrapper::Init(3)), ValueError);
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

TEST(List, RemovePresentMoreThanOnceObjectSame) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(3)};

  // When
  const auto second_elem = l[1];
  l.Remove(second_elem);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 5, 7, 3};

  EXPECT_EQ(actual, expected);
}

TEST(List, RemovePresentMoreThanOnceObjectSameLast) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(3)};

  // When
  const auto last_elem = l[-1];
  l.Remove(last_elem);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, RemovePresentMoreThanOnceObjectNotSame) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(3)};

  // When
  EXPECT_THROW(l.Remove(IntWrapper::Init(3)), ValueError);
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

TEST(List, RemoveAtEndObjectSame) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(5),
                        IntWrapper::Init(7), IntWrapper::Init(3)};

  // When
  const auto last_elem = l[-1];
  l.Remove(last_elem);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, RemoveAtEndObjectNotSame) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(5),
                        IntWrapper::Init(7), IntWrapper::Init(3)};

  // When/then
  EXPECT_THROW(l.Remove(IntWrapper::Init(3)), ValueError);
}

TEST(List, DeleteSliceZeroStep) {
  // If
  List<Int> l = {1, 3, 5, 1, 7};

  // When/then
  EXPECT_THROW(l.DeleteSlice(0, 0, 0), ValueError);
}

TEST(List, DeleteSliceZeroStepObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(1),
                        IntWrapper::Init(7)};

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

TEST(List, DeleteSliceNegativeStepObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(1),
                        IntWrapper::Init(7)};

  // When
  l.DeleteSlice(0, 1, -1);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, DeleteSliceSameStartAndEndObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(1),
                        IntWrapper::Init(7)};

  // When
  l.DeleteSlice(1, 1);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, DeleteSliceSingleStepObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.DeleteSlice(1, 3);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, DeleteSliceNotSingleStepNotEnoughObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.DeleteSlice(1, 3, 4);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, DeleteSliceNotSingleStepEnoughObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(9)};

  // When
  l.DeleteSlice(1, 5, 2);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, DeleteSliceOutOfBoundsLeftObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(9)};

  // When
  l.DeleteSlice(-9, 4, 2);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, DeleteSliceOutOfBoundsRightObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(9)};

  // When
  l.DeleteSlice(0, 9, 2);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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
TEST(List, DeleteSliceNoArgsIsClearObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(9)};

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

TEST(List, ReplaceSliceZeroStepObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(1),
                        IntWrapper::Init(7)};
  const List<IntWrapper> other = {IntWrapper::Init(2), IntWrapper::Init(4),
                                  IntWrapper::Init(6)};

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

TEST(List, ReplaceSliceNegativeStepObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(1),
                        IntWrapper::Init(7)};
  const List<IntWrapper> other = {IntWrapper::Init(2), IntWrapper::Init(4),
                                  IntWrapper::Init(6)};

  // When
  l.ReplaceSlice(other, 0, 1, -1);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, ReplaceSliceSameStartAndEndObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(1),
                        IntWrapper::Init(7)};
  const List<IntWrapper> other = {IntWrapper::Init(2), IntWrapper::Init(4),
                                  IntWrapper::Init(6)};

  // When
  l.ReplaceSlice(other, 1, 1);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, ReplaceSliceSingleStepMoreNewElemsObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<IntWrapper> other = {IntWrapper::Init(2), IntWrapper::Init(4),
                                  IntWrapper::Init(6)};

  // When
  l.ReplaceSlice(other, 1, 3);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, ReplaceSliceSingleStepLessNewElemsObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<IntWrapper> other = {IntWrapper::Init(2)};

  // When
  l.ReplaceSlice(other, 1, 3);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, ReplaceSliceSingleStepSameNewElemsObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<IntWrapper> other = {IntWrapper::Init(2), IntWrapper::Init(4)};

  // When
  l.ReplaceSlice(other, 1, 3);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, ReplaceSliceNotSingleStepNotSameNumElemsObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<IntWrapper> other = {IntWrapper::Init(2), IntWrapper::Init(4),
                                  IntWrapper::Init(6)};

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

TEST(List, ReplaceSliceNotSingleStepSameNumElemsObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(9)};
  const List<IntWrapper> other = {IntWrapper::Init(2), IntWrapper::Init(4)};

  // When
  l.ReplaceSlice(other, 1, 4, 2);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
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

TEST(List, ReplaceSliceNoArgsIsCompleteReplacementObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(9)};
  const List<IntWrapper> other = {IntWrapper::Init(2), IntWrapper::Init(4),
                                  IntWrapper::Init(6)};

  // When
  l.ReplaceSlice(other);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {2, 4, 6};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoEmpty) {
  // If
  List<Int> l;

  // When
  l.Insert(0, 5);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {5};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoEmptyObject) {
  // If
  List<IntWrapper> l;

  // When
  l.Insert(0, IntWrapper::Init(5));

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {5};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmpty) {
  // If
  List<Int> l = {1, 3, 7};

  // When
  l.Insert(1, 5);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 5, 3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(7)};

  // When
  l.Insert(1, IntWrapper::Init(5));

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 5, 3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyBeyondLeftBound) {
  // If
  List<Int> l = {1, 3, 7};

  // When
  l.Insert(-100, 5);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {5, 1, 3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyBeyondLeftBoundObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(7)};

  // When
  l.Insert(-100, IntWrapper::Init(5));

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {5, 1, 3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyBeyondRightBound) {
  // If
  List<Int> l = {1, 3, 7};

  // When
  l.Insert(100, 5);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 7, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyBeyondRightBoundObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(7)};

  // When
  l.Insert(100, IntWrapper::Init(5));

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 3, 7, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyAtLeftBound) {
  // If
  List<Int> l = {1, 3, 7};

  // When
  l.Insert(0, 5);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {5, 1, 3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyAtLeftBoundObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(7)};

  // When
  l.Insert(0, IntWrapper::Init(5));

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {5, 1, 3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyBeforeRightBound) {
  // If
  List<Int> l = {1, 3, 7};

  // When
  l.Insert(-1, 5);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyBeforeRightBoundObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(7)};

  // When
  l.Insert(-1, IntWrapper::Init(5));

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyAtRightBound) {
  // If
  List<Int> l = {1, 3, 7};

  // When
  l.Insert(3, 5);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 7, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, InsertIntoNonEmptyAtRightBoundObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(7)};

  // When
  l.Insert(3, IntWrapper::Init(5));

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 3, 7, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopEmpty) {
  // If
  List<Int> l;

  // When/then
  EXPECT_THROW(l.Pop(), IndexError);
}

TEST(List, PopEmptyObject) {
  // If
  List<IntWrapper> l;

  // When/then
  EXPECT_THROW(l.Pop(), IndexError);
}

TEST(List, PopLast) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Pop();

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopLastObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Pop();

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 3, 5};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopFront) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Pop(0);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopFrontObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Pop(0);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopMiddle) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Pop(1);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopMiddleObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Pop(1);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopNegative) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When
  l.Pop(-2);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopNegativeObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When
  l.Pop(-2);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 3, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, PopOutOfBoundsLeft) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_THROW(l.Pop(-100), IndexError);
}

TEST(List, PopOutOfBoundsLeftObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_THROW(l.Pop(-100), IndexError);
}

TEST(List, PopOutOfBoundsRight) {
  // If
  List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_THROW(l.Pop(100), IndexError);
}

TEST(List, PopOutOfBoundsRightObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_THROW(l.Pop(100), IndexError);
}

TEST(List, NativeIteration) {
  // If
  const List<Int> l = {1, 3, 5, 7};
  const auto expected = as_vector(l);

  // When
  std::vector<Int> actual;

  for (const auto elem : l) {
    actual.emplace_back(elem);
  }

  // Then
  EXPECT_EQ(actual, expected);
}

TEST(List, NativeIterationObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};
  const auto expected = as_vector<IntWrapper, Int>(l);

  // When
  std::vector<Int> actual;

  for (const auto elem : l) {
    actual.emplace_back(elem->Value());
  }

  // Then
  EXPECT_EQ(actual, expected);
}

TEST(List, IteratorIteration) {
  // If
  List<Int> l = {1, 3, 5, 7};
  const auto expected = as_vector(l);
  const auto it = Iter(l);

  // When
  std::vector<Int> actual;

  for (const auto elem : l) {
    actual.emplace_back(elem);
  }

  // Then
  EXPECT_EQ(actual, expected);
}

TEST(List, IteratorIterationObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7)};
  const auto expected = as_vector<IntWrapper, Int>(l);
  const auto it = Iter(l);

  // When
  std::vector<Int> actual;

  for (const auto elem : l) {
    actual.emplace_back(elem->Value());
  }

  // Then
  EXPECT_EQ(actual, expected);
}

TEST(List, EqualitySameObject) {
  // If
  const List<Int> l = {1, 3, 5, 7};
  const auto copy = l;
  ASSERT_NE(&l, &copy);

  // When/then
  EXPECT_TRUE(l.Eq(copy));
}

TEST(List, EqualitySameObjectObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<IntWrapper> copy = {IntWrapper::Init(1), IntWrapper::Init(3),
                                 IntWrapper::Init(5), IntWrapper::Init(7)};
  ASSERT_NE(&l, &copy);

  // When/then
  EXPECT_TRUE(l.Eq(copy));
}

TEST(List, NativeEqualitySameObject) {
  // If
  const List<Int> l = {1, 3, 5, 7};
  const auto copy = l;
  ASSERT_NE(&l, &copy);

  // When/then
  EXPECT_EQ(l, copy);
}

TEST(List, NativeEqualitySameObjectObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<IntWrapper> copy = {IntWrapper::Init(1), IntWrapper::Init(3),
                                 IntWrapper::Init(5), IntWrapper::Init(7)};
  ASSERT_NE(&l, &copy);

  // When/then
  EXPECT_EQ(l, copy);
}

TEST(List, NativeInEqualitySameObject) {
  // If
  const List<Int> l = {1, 3, 5, 7};
  const auto copy = l;
  ASSERT_NE(&l, &copy);

  // When/then
  EXPECT_FALSE(l != copy);
}

TEST(List, NativeInEqualitySameObjectObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<IntWrapper> copy = {IntWrapper::Init(1), IntWrapper::Init(3),
                                 IntWrapper::Init(5), IntWrapper::Init(7)};
  ASSERT_NE(&l, &copy);

  // When/then
  EXPECT_FALSE(l != copy);
}

TEST(List, EqualityDifferentObject) {
  // If
  const List<Int> l = {1, 3, 5, 7};
  List<Int> m = {1, 3, 5, 7, 9};
  ASSERT_NE(&l, &m);

  // When/then
  EXPECT_FALSE(l.Eq(m));

  // When
  m.Pop();

  // Then
  EXPECT_TRUE(l.Eq(m));
}

TEST(List, EqualityDifferentObjectObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};
  List<IntWrapper> m = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(9)};
  ASSERT_NE(&l, &m);

  // When/then
  EXPECT_FALSE(l.Eq(m));

  // When
  m.Pop();

  // Then
  EXPECT_TRUE(l.Eq(m));
}

TEST(List, NativeEqualityAndInequalityDifferentObject) {
  // If
  const List<Int> l = {1, 3, 5, 7};
  List<Int> m = {1, 3, 5, 7, 9};
  ASSERT_NE(&l, &m);

  // When/then
  EXPECT_NE(l, m);

  // When
  m.Pop();

  // Then
  EXPECT_EQ(l, m);
}

TEST(List, NativeEqualityAndInequalityDifferentObjectObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};
  List<IntWrapper> m = {IntWrapper::Init(1), IntWrapper::Init(3),
                        IntWrapper::Init(5), IntWrapper::Init(7),
                        IntWrapper::Init(9)};
  ASSERT_NE(&l, &m);

  // When/then
  EXPECT_NE(l, m);

  // When
  m.Pop();

  // Then
  EXPECT_EQ(l, m);
}

TEST(List, EqualityDifferentType) {
  // If
  const List<Int> l = {1, 3, 5, 7};
  const List<Float> m = {1.0, 3.0, 5.0, 7.0};

  // When/then
  EXPECT_FALSE(l.Eq(m));
}

TEST(List, EqualityDifferentTypeObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<FloatWrapper> m = {
      FloatWrapper::Init(1.0), FloatWrapper::Init(3.0), FloatWrapper::Init(5.0),
      FloatWrapper::Init(7.0)};

  // When/then
  EXPECT_FALSE(l.Eq(m));
}

TEST(List, NativeEqualityDifferentType) {
  // If
  const List<Int> l = {1, 3, 5, 7};
  const List<Float> m = {1.0, 3.0, 5.0, 7.0};

  // When/then
  ASSERT_NE(l, m);
}

TEST(List, NativeEqualityDifferentTypeObject) {
  // If
  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};
  const List<FloatWrapper> m = {
      FloatWrapper::Init(1.0), FloatWrapper::Init(3.0), FloatWrapper::Init(5.0),
      FloatWrapper::Init(7.0)};

  // When/then
  ASSERT_NE(l, m);
}

TEST(List, AsStrEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_EQ(AsStr(l), "[]");
}

TEST(List, AsStrEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_EQ(AsStr(l), "[]");
}

TEST(List, AsStrNotEmpty) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(AsStr(l), "[1, 3, 5, 7]");
}

TEST(List, AsStrNotEmptyObject) {
  // If
  IntWrapper::ResetId();

  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_EQ(AsStr(l),
            "["
            "[Wrapper(value=1, id=0)], "
            "[Wrapper(value=3, id=1)], "
            "[Wrapper(value=5, id=2)], "
            "[Wrapper(value=7, id=3)]"
            "]");
}

TEST(List, ReprEmpty) {
  // If
  const List<Int> l;

  // When/then
  EXPECT_EQ(Repr(l), "[]");
}

TEST(List, ReprEmptyObject) {
  // If
  const List<IntWrapper> l;

  // When/then
  EXPECT_EQ(Repr(l), "[]");
}

TEST(List, ReprNotEmpty) {
  // If
  const List<Int> l = {1, 3, 5, 7};

  // When/then
  EXPECT_EQ(Repr(l), "[1, 3, 5, 7]");
}

TEST(List, ReprNotEmptyObject) {
  // If
  IntWrapper::ResetId();

  const List<IntWrapper> l = {IntWrapper::Init(1), IntWrapper::Init(3),
                              IntWrapper::Init(5), IntWrapper::Init(7)};

  // When/then
  EXPECT_EQ(Repr(l),
            "["
            "[Wrapper(value=1, id=0)], "
            "[Wrapper(value=3, id=1)], "
            "[Wrapper(value=5, id=2)], "
            "[Wrapper(value=7, id=3)]"
            "]");
}

TEST(List, Sort) {
  // If
  List<Int> l = {7, 3, 1, 1, 5};

  // When
  l.Sort();

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, SortStableObject) {
  // If
  IntWrapper::ResetId();

  List<IntWrapper> l = {IntWrapper::Init(7), IntWrapper::Init(3),
                        IntWrapper::Init(1), IntWrapper::Init(1),
                        IntWrapper::Init(5)};

  // When
  l.Sort();

  // Then
  const std::vector<Int> expected_values = {1, 1, 3, 5, 7};
  const std::vector<size_t> expected_ids = {2, 3, 1, 4, 0};

  const auto actual_values = as_vector<IntWrapper, Int>(l);
  std::vector<size_t> actual_ids;

  for (const auto& elem : l) {
    actual_ids.emplace_back(elem->Id());
  }

  EXPECT_EQ(actual_values, expected_values);
  EXPECT_EQ(actual_ids, expected_ids);
}

TEST(List, SortReverse) {
  // If
  List<Int> l = {7, 3, 1, 1, 5};

  // When
  l.Sort(true);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {7, 5, 3, 1, 1};

  EXPECT_EQ(actual, expected);
}

TEST(List, SortReverseStableObject) {
  // If
  IntWrapper::ResetId();

  List<IntWrapper> l = {IntWrapper::Init(7), IntWrapper::Init(3),
                        IntWrapper::Init(1), IntWrapper::Init(1),
                        IntWrapper::Init(5)};

  // When
  l.Sort(true);

  // Then
  const std::vector<Int> expected_values = {7, 5, 3, 1, 1};
  const std::vector<size_t> expected_ids = {0, 4, 1, 2, 3};

  const auto actual_values = as_vector<IntWrapper, Int>(l);
  std::vector<size_t> actual_ids;

  for (const auto& elem : l) {
    actual_ids.emplace_back(elem->Id());
  }

  EXPECT_EQ(actual_values, expected_values);
  EXPECT_EQ(actual_ids, expected_ids);
}

TEST(List, SortWithKey) {
  // If
  List<Int> l = {7, 3, 1, 1, 5};

  // This effectively inverts the sort
  const auto key = [](const Int i) -> Float {
    return 1.0 / static_cast<Float>(i);
  };

  // When
  l.Sort(key);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {7, 5, 3, 1, 1};

  EXPECT_EQ(actual, expected);
}

TEST(List, SortWithKeyObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(7), IntWrapper::Init(3),
                        IntWrapper::Init(1), IntWrapper::Init(1),
                        IntWrapper::Init(5)};

  // This effectively inverts the sort
  const auto key = [](__memory::ReadOnly<IntWrapper> i) -> Float {
    return 1.0 / static_cast<Float>(i->Value());
  };

  // When
  l.Sort(key);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {7, 5, 3, 1, 1};

  EXPECT_EQ(actual, expected);
}

TEST(List, SortWithKeyAndReverse) {
  // If
  List<Int> l = {7, 3, 1, 1, 5};

  // This effectively inverts the sort, but the reverse reverses it again
  const auto key = [](const Int i) -> Float {
    return 1.0 / static_cast<Float>(i);
  };

  // When
  l.Sort(key, true);

  // Then
  const auto actual = as_vector(l);
  const std::vector<Int> expected = {1, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

TEST(List, SortWithKeyAndReverseObject) {
  // If
  List<IntWrapper> l = {IntWrapper::Init(7), IntWrapper::Init(3),
                        IntWrapper::Init(1), IntWrapper::Init(1),
                        IntWrapper::Init(5)};

  // This effectively inverts the sort, but the reverse reverses it again
  const auto key = [](__memory::ReadOnly<IntWrapper> i) -> Float {
    return 1.0 / static_cast<Float>(i->Value());
  };

  // When
  l.Sort(key, true);

  // Then
  const auto actual = as_vector<IntWrapper, Int>(l);
  const std::vector<Int> expected = {1, 1, 3, 5, 7};

  EXPECT_EQ(actual, expected);
}

}  // namespace mamba::builtins::test
