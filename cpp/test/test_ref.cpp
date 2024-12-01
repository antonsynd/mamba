#include "gtest/gtest.h"

#include <memory>

#include "mamba/builtins/__memory/ref.hpp"

namespace mamba::builtins::__memory::test {

TEST(Ref, VariousTypes) {
  static_assert(std::same_as<Ref<int>, std::shared_ptr<int>>);

  // Nesting is blocked by other concepts
  static_assert(std::same_as<Ref<std::shared_ptr<int>>,
                             std::shared_ptr<std::shared_ptr<int>>>);
}

TEST(HasElementType, VariousTypes) {
  static_assert(!__concepts::HasElementType<int>);
  static_assert(__concepts::HasElementType<Ref<int>>);
}

TEST(IsRef, VariousTypes) {
  static_assert(!__concepts::IsRef<int>);
  static_assert(__concepts::IsRef<Ref<int>>);
}

TEST(UnwrapRef, VariousTypes) {
  static_assert(std::same_as<UnwrapRef<Ref<int>>, int>);
}

TEST(Unwrap, VariousTypes) {
  static_assert(std::same_as<Unwrap<int>, int>);
  static_assert(std::same_as<Unwrap<Ref<int>>, int>);
}

}  // namespace mamba::builtins::__memory::test
