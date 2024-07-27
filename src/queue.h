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
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q) noexcept;
  ~queue();
  queue operator=(queue &&q);

  // Queue Element access
  const_reference front() { return this->inner_list.front(); }
  const_reference back() { return this->inner_list.back(); }

  // Queue Capacity
  bool empty();
  size_type size();

  // Queue Modifiers
  void push(const_reference value);
  void pop();
  void swap(queue &other);

 private:
  std::list<value_type> inner_list;
};



template <typename T>
  inline queue<T>::queue() { inner_list = std::list<value_type>(); }

template <typename T>
  inline queue<T>::queue(std::initializer_list<value_type> const &items) {
    inner_list = std::list<value_type>(items);
  }

template <typename T>
  inline queue<T>::queue(const queue &q) : inner_list(q.inner_list) {}

template <typename T>
  inline queue<T>::queue(queue &&q) noexcept : inner_list(std::move(q.inner_list)) {}

template <typename T>
  inline queue<T>::~queue() { this->inner_list.clear(); }

// template <typename T>
//   inline queue<T>::queue operator=(queue &&q) {
//     this->inner_list = std::move(q.inner_list);
//     return *this;
//   }

// template <typename T>
//   inline typename queue<T>::const_reference front() { return this->inner_list.front(); }

// template <typename T>
//   inline typename queue<T>::const_reference back() { return this->inner_list.back(); }

template <typename T>
  inline bool queue<T>::empty() { return inner_list.empty(); }

template <typename T>
  inline size_t queue<T>::size() { return inner_list.size(); }

template <typename T>
  inline void queue<T>::push(const_reference value) { this->inner_list.push_back(value); }

template <typename T>
  inline void queue<T>::pop() { inner_list.pop_front(); }

template <typename T>
  inline void queue<T>::swap(queue &other) { this->inner_list.swap(other.inner_list); }

}  // namespace s21
#endif  //  #define CPP_S21_CONTAINERS_QUEUE_H