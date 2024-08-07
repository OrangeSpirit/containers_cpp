#include <iostream>

class MyClass {
  public:
    int data;

    MyClass(int data) {
      this->data = data;
      std::cout << "call constructor   " << this << std::endl;
    }

    // MyClass(const MyClass &other) {
    //   std::cout << "Call copy constructor   " << std::endl;
    //   if (this != &other) {
    //     this->data = other.data;
    //   }
    //   return *this;
    // }

    ~MyClass() {
      std::cout << "call DESTRUCTOR   " << this << std::endl;
    };
};

void Foo(MyClass value) {
  std::cout << "call Foo   " << std::endl;
  std::cout << value.data << std::endl;
}

MyClass Foo2() {
  std::cout << "Call Foo2   " << std::endl;
  MyClass temp(2);

  return temp;
}


int main() {
  MyClass a(1);
  MyClass b(a);

  // Foo(a);
  // Foo2();

  return 0;
}