#include <iostream>
#include <list>

template <typename T>
class queue {
 public:
  // QUEUE MEMBER TYPE

  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // QUEUE MAMBER FUNCTIONS

  // default constructor, creates empty queue
  queue() { inner_list = std::list<value_type>(); }

  // initializer list constructor, creates queue initizialized using
  // std::initializer_list
  queue(std::initializer_list<value_type> const &items) {
    inner_list = std::list<value_type>(items);
  }

  // copy constructor
  queue(const queue &temp_queue) : inner_list(temp_queue.inner_list) {}

  // move constructor
  queue(queue &&temp_queue) noexcept
      : inner_list(std::move(temp_queue.inner_list)) {}

  // destructor
  ~queue() { this->inner_list.clear(); }

  // assignment operator overload for moving object
  queue &operator=(queue &&temp_queue) {
    this->inner_list = std::move(temp_queue.inner_list);
    return *this;
  }

  // QUEUE CAPACITY

  // checks whether the container is empty
  bool empty() { return inner_list.empty(); }

  // returns the number of elements
  size_type size() { return inner_list.size(); }

  // QUEUE MODIFIERS

  // inserts element at the top
  void push(value_type value) { this->inner_list.push_back(value); }

  // removes the top element
  void pop() { this->inner_list.pop_front(); }

  // swaps the contents
  void swap(queue &other) { this->inner_list.swap(other.inner_list); }

  // QUEUE ELEMENT ACCESS

  // accesses the top element
  const_reference front() { return this->inner_list.front(); }

  const_reference back() { return this->inner_list.back(); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    return this->inner_list.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  std::list<value_type> inner_list;
};

int main() {
//   std::list<int> A;
//   A.push_back(100);
//   A.push_back(200);
//   A.push_front(300);
//   A.push_front(400);
//   A.push_front(500);
//   std::cout << A.size() << std::endl;
//   for (std::list<int>::iterator it = A.begin(); it != A.end(); ++it) {
//     std::cout << *it << " ";
//   }
//   std::cout << std::endl;
//   A.sort();
//   for (std::list<int>::iterator it = A.begin(); it != A.end(); ++it) {
//     std::cout << *it << " ";
//   }
//   std::cout << std::endl;
//   std::list<int>::iterator IT;
//   for (std::list<int>::iterator it = A.begin(); it != A.end(); ++it) {
//     IT = it;
//     std::cout << *IT << " ";
//   }
//   std::cout << std::endl;
//   std::cout << sizeof(IT) << "   " << sizeof(size_t) << std::endl;
//   A.sort();
  queue<int> A;
  std::cout << A.size() << std::endl;
  A.push(111);
  std::cout << A.size() << std::endl;
  A.push(22);
  A.push(788);
  A.push(555);
  A.push(333);
  std::cout << A.size() << std::endl;

  queue<int> B{5,6,7,8};
  std::cout << B.size() << std::endl;
  A.swap(B);
  std::cout << "A.size = " << A.size() << std::endl;
  std::cout << "B.size = " << B.size() << std::endl;
  A.pop();
  A.pop();
  A.pop();
  std::cout << "A.size = " << A.size() << std::endl;
  A.pop();
  std::cout << "A.size = " << A.size() << std::endl;

  std::cout << "B.front = " << B.front() << std:: endl;
  std::cout << "B.back = " << B.back() << std::endl;
  B.pop();
  B.push(191);
  std::cout << "B.front = " << B.front() << std:: endl;
  std::cout << "B.back = " << B.back() << std::endl;
  B.pop();
  std::cout << "B.front = " << B.front() << std:: endl;
  std::cout << "B.size = " << B.size() << std::endl;
  std::cout << "A.empty() = " << A.empty() << "   true = " << true << std::endl;
  std::cout << "B.empty() = " << B.empty() << "   false = " << false << std::endl;


  return 0;
}