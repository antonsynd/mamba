#include "dummy_object.hpp"

namespace mamba::test {

void DummyObject::ResetId() {
  global_id_ = 0;
}

std::size_t DummyObject::GetNextId() {
  return global_id_++;
}

DummyObject::DummyObject() {
  // Not thread-safe
  data_.id_ = GetNextId();
}

std::size_t DummyObject::Id() const {
  return data_.id_;
}

}  // namespace mamba::test
