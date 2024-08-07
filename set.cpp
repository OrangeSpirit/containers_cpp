#include <iostream>
#include <set>
using namespace std;

int main() {
  set<int> A{100, 200, 33, 79, 85}, B{3, 4, 1, 8, 5};


  cout << "A.size() = " << A.size() << endl;

  for (auto &temp : A) {
    cout << temp << endl;
  }

  A.erase(111);
  A.erase(200);

  cout << "after remove 111, 200" << endl;
  for (auto temp : A) {
    cout << temp << endl;
    temp = 5;
  }

  A.swap(B);

  cout << "set A = " << endl;
  for (auto &temp : A) {
    cout << temp << endl;
  }

  cout << "set B = " << endl;
  for (auto &temp : B) {
    cout << temp << endl;
  }

  cout << "A.size() = " << A.size() << endl;
  cout << "B.size() = " << B.size() << endl;

  A.merge(B);
  cout << "after merge" << endl;
  cout << "A.size() = " << A.size() << endl;
  cout << "set A = " << endl;
  for (auto &temp : A) {
    cout << temp << endl;
  }

  cout << "B.size() = " << B.size() << endl;
  cout << "set B = " << endl;
  for (auto &temp : B) {
    cout << temp << endl;
  }

  return 0;
}