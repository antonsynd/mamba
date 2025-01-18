#pragma once

#include <memory>  // for shared_ptr

#include "mamba/__utils/string_builder.hpp"    // for stringify, StringB...
#include "mamba/builtins/__meta/optional.hpp"  // for Optional
#include "mamba/builtins/__types/none.hpp"     // for kNone
#include "mamba/builtins/types.hpp"            // for StrType, ObjectType

namespace mamba::builtins {

StrType Repr(const BoolType b);
StrType Repr(const ByteType b);
// StrType Repr(const ComplexType& c);
StrType Repr(const DecimalType d);
StrType Repr(const DoubleType d);
StrType Repr(const FloatType f);
StrType Repr(const IntType i);
StrType Repr(const LongType l);
StrType Repr(const NoneType);
StrType Repr(const ObjectType& t);
StrType Repr(const std::shared_ptr<ObjectType>& t);
StrType Repr(const SByteType s);
StrType Repr(const ShortType s);
StrType Repr(const SizeType s);
StrType Repr(const UIntType u);
StrType Repr(const ULongType u);
StrType Repr(const UShortType u);

/// @brief Optional<T> returns the representation of the payload or "None".
template <details::Optional T>
StrType Repr(const T& o) {
  if (o.has_value()) {
    return __utils::stringify() << "Optional[" << Repr(o.value()) << "]";
  } else {
    return details::kNone;
  }
}

}  // namespace mamba::builtins
