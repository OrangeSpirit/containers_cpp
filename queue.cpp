#include <gtest/gtest.h>
#include <iostream>
#include <queue>

#include "list.h"

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
  queue() { inner_list = list<value_type>(); }
  queue(std::initializer_list<value_type> const &items) {
    inner_list = list<value_type>(items);
  }
  queue(const queue &q) : inner_list(q.inner_list) {}
  queue(queue &&q) noexcept : inner_list(std::move(q.inner_list)) {}
  ~queue() { this->inner_list.clear(); }
  queue& operator=(queue &&q) noexcept {
    if (this != &q) {
      this->inner_list = std::move(q.inner_list);
    }
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

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    return this->inner_list.insert_many_back(std::forward<Args>(args)...);
  }
  
 private:
  list<value_type> inner_list;
};
}  // namespace s21

// TEST(queue, case1) {
//   s21::queue<int> s21_queue_int;
//   s21::queue<double> s21_queue_double;
//   s21::queue<std::string> s21_queue_string;
//   EXPECT_EQ(s21_queue_int.empty(), true);
//   EXPECT_EQ(s21_queue_double.empty(), true);
//   EXPECT_EQ(s21_queue_string.empty(), true);
// }

// TEST(queue, case2) {
//   s21::queue<int> s21_queue_int{1, 2, 3};
//   s21::queue<double> s21_queue_double{1.1, 1.2, 1.3, 1.4};
//   s21::queue<std::string> s21_queue_string{"aaa", "bbb", "ccc", "ddd", "fff"};
//   EXPECT_EQ(s21_queue_int.size(), 3);
//   EXPECT_EQ(s21_queue_double.size(), 4);
//   EXPECT_EQ(s21_queue_string.size(), 5);
// }

// TEST(queue, case3) {
//   s21::queue<int> s21_queue_int{1};
//   s21::queue<double> s21_queue_double{1.1};
//   s21_queue_int.push(1);
//   s21_queue_double.push(2.2);
//   EXPECT_EQ(s21_queue_int.front(), 1);
//   EXPECT_EQ(s21_queue_double.front(), 1.1);
// }

// TEST(queue, case4) {
//   s21::queue<int> s21_queue_int;
//   s21::queue<double> s21_queue_double;
//   s21::queue<std::string> s21_queue_string;
//   EXPECT_EQ(s21_queue_int.empty(), true);
//   EXPECT_EQ(s21_queue_double.empty(), true);
//   EXPECT_EQ(s21_queue_string.empty(), true);
// }

// TEST(queue, case5) {
//   s21::queue<int> s21_queue_int{100};
//   s21::queue<double> s21_queue_double{99.99};
//   s21::queue<std::string> s21_queue_string{"what"};
//   EXPECT_EQ(s21_queue_int.empty(), false);
//   EXPECT_EQ(s21_queue_double.empty(), false);
//   EXPECT_EQ(s21_queue_string.empty(), false);
//   s21_queue_int.pop();
//   s21_queue_double.pop();
//   s21_queue_string.pop();
//   EXPECT_EQ(s21_queue_int.empty(), true);
//   EXPECT_EQ(s21_queue_double.empty(), true);
//   EXPECT_EQ(s21_queue_string.empty(), true);
// }

// TEST(queue, case6) {
//   s21::queue<int> s21_queue_int1{1, 2, 3};
//   s21::queue<int> s21_queue_int2{7, 8, 9, 10, 11};
//   s21_queue_int1.swap(s21_queue_int2);
//   EXPECT_EQ(s21_queue_int1.size(), 5);
//   EXPECT_EQ(s21_queue_int2.size(), 3);
//   EXPECT_EQ(s21_queue_int1.front(), 7);
//   EXPECT_EQ(s21_queue_int2.front(), 1);
//   EXPECT_EQ(s21_queue_int1.back(), 11);
//   EXPECT_EQ(s21_queue_int2.back(), 3);
// }

// TEST(queue, case7) {
//   s21::queue<int> s21_queue_int{22, 33, 44, 55, 69};
//   s21::queue<int> s21_queue_new{s21_queue_int};
//   EXPECT_EQ(s21_queue_new.size(), 5);
//   EXPECT_EQ(s21_queue_new.front(), 22);
//   EXPECT_EQ(s21_queue_new.back(), 69);
// }

// TEST(queue, case8) {
//   s21::queue<int> s21_queue_int{7, 8, 9, 10, 11};
//   s21::queue<int> s21_queue_new = std::move(s21_queue_int);
//   EXPECT_EQ(s21_queue_new.size(), 5);
//   EXPECT_EQ(s21_queue_new.front(), 7);
//   EXPECT_EQ(s21_queue_new.back(), 11);
// }

// TEST(queue, case9) {
//   s21::queue<int> s21_queue_int{11, 22, 33, 44, 55};
//   s21::queue<int> s21_queue_new;
//   s21_queue_new = std::move(s21_queue_int);
//   EXPECT_EQ(s21_queue_new.size(), 5);
//   EXPECT_EQ(s21_queue_new.front(), 11);
//   EXPECT_EQ(s21_queue_new.back(), 55);
// }

// TEST(Queue, Constructor_Default) {
//     s21::queue<int> our_queue;
//     std::queue<int> std_queue;
//     EXPECT_EQ(our_queue.empty(), std_queue.empty());
// }

// TEST(Queue, Constructor_List) {
//     s21::queue<int> our_queue = {1, 2, 3};
//     std::queue<int> std_queue;
//     std_queue.push(1);
//     std_queue.push(2);
//     std_queue.push(3);
//     EXPECT_EQ(our_queue.front(), std_queue.front());
//     EXPECT_EQ(our_queue.back(), std_queue.back());
// }

// TEST(Queue, Constructor_Copy) {
//     s21::queue<int> our_queue = {1, 2, 3};
//     s21::queue<int> our_copy(our_queue);
//     std::queue<int> std_queue;
//     std_queue.push(1);
//     std_queue.push(2);
//     std_queue.push(3);
//     std::queue<int> std_copy(std_queue);
//     EXPECT_EQ(our_copy.front(), std_copy.front());
//     EXPECT_EQ(our_copy.back(), std_copy.back());
// }



// // TEST(Queue, Operator_Copy) {
// //     std::queue<int> our_queue_int;
// //     our_queue_int.push(1);
// //     our_queue_int.push(2);
// //     our_queue_int.push(3);
// //     std::queue<int> std_queue_int;
// //     std_queue_int.push(1);
// //     std_queue_int.push(2);
// //     std_queue_int.push(3);
// //     std::queue<int> our_queue_empty;
// //     std::queue<int> std_queue_empty;
// //     our_queue_empty = our_queue_int;
// //     std_queue_empty = std_queue_int;
// //     EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
// //     EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
// //     EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
// // }

// TEST(Queue, Constructor_Move) {
//     s21::queue<int> our_queue = {1, 2, 3};
//     s21::queue<int> our_move(std::move(our_queue));
//     std::queue<int> std_queue;
//     std_queue.push(1);
//     std_queue.push(2);
//     std_queue.push(3);
//     std::queue<int> std_move(std::move(std_queue));
//     EXPECT_EQ(our_move.front(), std_move.front());
//     EXPECT_EQ(our_move.back(), std_move.back());
//     EXPECT_EQ(our_queue.empty(), std_queue.empty());
// }

// TEST(Queue, Operator_Move) {
//     s21::queue<int> our_queue_int = {1, 2, 3};
//     std::queue<int> std_queue_int;
//     std_queue_int.push(1);
//     std_queue_int.push(2);
//     std_queue_int.push(3);
//     s21::queue<int> our_queue_empty;
//     std::queue<int> std_queue_empty;
//     our_queue_empty = std::move(our_queue_int);
//     std_queue_empty = std::move(std_queue_int);
//     EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
//     EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
//     EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
// }

// TEST(Queue, FrontAndBack) {
//     s21::queue<int> our_queue_int = {1, 2, 3};
//     std::queue<int> std_queue_int;
//     std_queue_int.push(1);
//     std_queue_int.push(2);
//     std_queue_int.push(3);
//     s21::queue<double> our_queue_double = {1.1f, 2.1f, 3.1f};
//     std::queue<double> std_queue_double;
//     std_queue_double.push(1.1f);
//     std_queue_double.push(2.1f);
//     std_queue_double.push(3.1f);
//     s21::queue<std::string> our_queue_string = {"abc", "def", "ghf"};
//     std::queue<std::string> std_queue_string;
//     std_queue_string.push("abc");
//     std_queue_string.push("def");
//     std_queue_string.push("ghf");
//     EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
//     EXPECT_EQ(our_queue_double.front(), std_queue_double.front());
//     EXPECT_EQ(our_queue_string.front(), std_queue_string.front());
//     EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
//     EXPECT_EQ(our_queue_double.back(), std_queue_double.back());
//     EXPECT_EQ(our_queue_string.back(), std_queue_string.back());
// }

// TEST(Queue, Empty) {
//     s21::queue<int> our_queue_int = {1, 2, 3};
//     std::queue<int> std_queue_int;
//     std_queue_int.push(1);
//     std_queue_int.push(2);
//     std_queue_int.push(3);
//     EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
//     s21::queue<int> our_queue_empty;
//     std::queue<int> std_queue_empty;
//     EXPECT_EQ(our_queue_empty.empty(), std_queue_empty.empty());
// }

// TEST(Queue, Size) {
//     s21::queue<int> our_queue_int = {1, 2, 3};
//     std::queue<int> std_queue_int;
//     std_queue_int.push(1);
//     std_queue_int.push(2);
//     std_queue_int.push(3);
//     EXPECT_EQ(our_queue_int.size(), std_queue_int.size());
//     s21::queue<int> our_queue_empty;
//     std::queue<int> std_queue_empty;
//     EXPECT_EQ(our_queue_empty.size(), std_queue_empty.size());
// }

// TEST(Queue, Push) {
//     s21::queue<int> our_queue_int;
//     our_queue_int.push(1);
//     our_queue_int.push(2);
//     our_queue_int.push(3);
//     std::queue<int> std_queue_int;
//     std_queue_int.push(1);
//     std_queue_int.push(2);
//     std_queue_int.push(3);
//     EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
//     EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
// }

// TEST(Queue, Pop) {
//     s21::queue<int> our_queue_int;
//     our_queue_int.push(1);
//     our_queue_int.push(2);
//     our_queue_int.push(3);
//     our_queue_int.pop();
//     std::queue<int> std_queue_int;
//     std_queue_int.push(1);
//     std_queue_int.push(2);
//     std_queue_int.push(3);
//     std_queue_int.pop();
//     EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
//     EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
//     our_queue_int.pop();
//     our_queue_int.pop();
//     std_queue_int.pop();
//     std_queue_int.pop();
//     EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
// }

// TEST(Queue, Swap) {
//     s21::queue<int> our_queue_int = {1, 2, 3};
//     std::queue<int> std_queue_int;
//     std_queue_int.push(1);
//     std_queue_int.push(2);
//     std_queue_int.push(3);
//     s21::queue<int> our_queue_empty;
//     std::queue<int> std_queue_empty;
//     our_queue_empty.swap(our_queue_int);
//     std_queue_empty.swap(std_queue_int);
//     EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
//     EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
//     EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
// }

// TEST(Queue, InsertManyBack) {
//     s21::queue<int> our_queue_int;
//     our_queue_int.insert_many_back(1, 2, 3);
//     EXPECT_EQ(our_queue_int.front(), 1);
//     EXPECT_EQ(our_queue_int.back(), 3);
// }

TEST(Queue, Operator_Copy) {
    s21::queue<int> our_queue_int = {1, 2, 3};
    std::queue<int> std_queue_int;
    std_queue_int.push(1);
    std_queue_int.push(2);
    std_queue_int.push(3);
    s21::queue<int> our_queue_empty;
    std::queue<int> std_queue_empty;
    our_queue_empty = our_queue_int;
    std_queue_empty = std_queue_int;
    EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
    EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
    EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

// TEST(Queue, Operator_Copy) {
//     s21::queue<int> our_queue_int = {1, 2, 3};
//     std::queue<int> std_queue_int;
//     std_queue_int.push(1);
//     std_queue_int.push(2);
//     std_queue_int.push(3);
//     s21::queue<int> our_queue_empty{5, 7, 8};
//     std::queue<int> std_queue_empty;
//     // our_queue_empty = our_queue_int;
//     std_queue_empty = std_queue_int;
//     EXPECT_EQ(our_queue_empty.front(), 5);
//     std::cout << "our_queue_empty.back() = " << our_queue_empty.back() << std::endl;
//     std::cout << "our_queue_int.empty() = " << our_queue_int.empty() << std::endl;
//     EXPECT_EQ(our_queue_empty.back(), 8);
//     EXPECT_EQ(our_queue_int.empty(), 0);
// }

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
