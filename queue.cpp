#include <iostream>
#include <list>

int main() {
  std::list<int> A;
  A.push_back(100);
  A.push_back(200);
  A.push_front(300);
  A.push_front(400);
  A.push_front(500);

  std::cout << A.size() << std::endl;
  for (std::list<int>::iterator it = A.begin(); it != A.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  A.sort();

  for (std::list<int>::iterator it = A.begin(); it != A.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  for (std::list<int>::iterator it = A.begin(); it != A.end(); ++it) {
    std::cout << &it << " ";
  }
  std::cout << std::endl;

  return 0;
}