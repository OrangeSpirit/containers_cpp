#ifndef CPP_S21_CONTAINERS_QUEUE_H
#define CPP_S21_CONTAINERS_QUEUE_H

#include <initializer_list>
#include <list>

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;   // the template parameter T
  using reference = T &;  // defines the type of the reference to an element
  using const_reference =
      const T &;             // defines the type of the constant reference
  using size_type = size_t;  // defines the type of the container size (standard
                             // type is size_t)

  // Queue Member functions
  queue() { inner_list = std::list<value_type>(); }
  queue(std::initializer_list<value_type> const &items) {
    inner_list = std::list<value_type>(items);
  }
  queue(const queue &q) : inner_list(q.inner_list) {}
  queue(queue &&q) noexcept : inner_list(std::move(q.inner_list)) {}
  ~queue() { this->inner_list.clear(); }
  queue operator=(queue &&q) {
    this->inner_list = std::move(q.inner_list);
    return *this;
  }

  // Queue Element access
  const_reference front() { return this->inner_list.front(); }
  const_reference back() { return this->inner_list.back(); }

  // Queue Capacity
  bool empty() { return inner_list.empty(); }
  size_type size() { return inner_list.size(); }

  // Queue Modifiers
  void push(const_reference value) { this->inner_list.push_back(value); }
  void pop() { inner_list.pop_front(); }
  void swap(queue &other) { this->inner_list.swap(other.inner_list); }

 private:
  std::list<value_type> inner_list;
};
}  // namespace s21

#endif  //  #define CPP_S21_CONTAINERS_QUEUE_H